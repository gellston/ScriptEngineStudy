
#include "core/collection/memoryBlock.h"
#include "core/collection/memoryPool.h"

#include <stdexcept>
#include <mutex>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <algorithm>


#pragma region IMPL
namespace visionhub {
	namespace v1 {
		class impl_memoryPool {
		public:
			std::vector<std::size_t> buckets;
			std::size_t alignment = 64;
			std::size_t inUseSize = 0;
			std::size_t totalSize = 0;
			std::size_t freeSize = 0;

			std::map<std::size_t, std::vector<void*>> free;

			std::mutex mtx;


			std::size_t roudUp(std::size_t bytes) {
				for (auto b : buckets) {
					if (bytes <= b) {
						return b;
					}
				}
				auto size = ((bytes + alignment - 1) / alignment) * alignment;

				return size;
			}

			visionhub::v1::memoryBlock makeHandle(void* p, std::size_t cap) {
				memoryBlock h; 
				h.data = static_cast<uint8_t*>(p); 
				h.capacity = cap;


				auto ret = [this, cap](void* raw) {
					if (!raw) return;
					std::scoped_lock<std::mutex> lock(mtx);
					free[cap].push_back(raw);
					inUseSize -= cap;
				};
				h.holder = std::shared_ptr<void>(p, ret);
				//std::memset(p, 0,  cap);

				return h;
			}
		};
	}
}
#pragma endregion



#pragma region Constructor
visionhub::v1::memoryPool::memoryPool(const std::vector<std::size_t> & buckets, std::size_t alignment) : impl(new impl_memoryPool()){

	this->impl->buckets = buckets;
	this->impl->alignment = alignment;

	if (alignment == 0 || (alignment & (alignment - 1)) != 0) {
		throw std::runtime_error("alignment must be power-of-two");
	}

	std::sort(this->impl->buckets.begin(), this->impl->buckets.end());

}
#pragma endregion

#pragma region Destructor
visionhub::v1::memoryPool::~memoryPool() {

}
#pragma endregion

#pragma region Public Functions
visionhub::v1::memoryBlock visionhub::v1::memoryPool::acquire(std::size_t bytes) {


	if (bytes == 0) {
		throw std::runtime_error("Invalid byte size");
	}

	std::scoped_lock lock(this->impl->mtx);

	auto need = this->impl->roudUp(bytes);


	// 효율이 90 이하로 떨어지는 버킷이 발생할 경우 bucket 리스트에 추가
	// need 사이즈 업데이트
	double percent = ((double)bytes / (double)need) * 100;
	if (percent < 90) {
		auto alignment = this->impl->alignment;
		auto size = ((bytes + alignment - 1) / alignment)* alignment;
		this->impl->buckets.push_back(size);
		std::sort(this->impl->buckets.begin(), this->impl->buckets.end());
		need = size;
	}

	auto& bin = this->impl->free[need];
	if (!bin.empty()) {
		void* p = bin.back();
		bin.pop_back();
		this->impl->inUseSize += need;
		return this->impl->makeHandle(p, need);
	}

	visionhub::v1::memoryBlock block;
	void* p = _aligned_malloc(need, this->impl->alignment);
	if (!p) {
		throw std::runtime_error("Can't process aligned_alloc");
	}

	this->impl->totalSize += need;
	this->impl->inUseSize += need;
	return this->impl->makeHandle(p, need);
}

void visionhub::v1::memoryPool::trim() {
	std::scoped_lock<std::mutex> lock(this->impl->mtx);
	for (auto& kv : this->impl->free) {
		for (void* p : kv.second) {
			_aligned_free(p);
		}
		this->impl->freeSize -= kv.first * kv.second.size();
		kv.second.clear();
	}
}

std::size_t visionhub::v1::memoryPool::totalSize() {

	return this->impl->totalSize;
}

std::size_t visionhub::v1::memoryPool::inUseSize() {

	return this->impl->inUseSize;
}

std::size_t visionhub::v1::memoryPool::freeSize() {

	return this->impl->freeSize;
}


void visionhub::v1::memoryPool::addBinSize(std::size_t size) {

	std::scoped_lock<std::mutex> lock(this->impl->mtx);

	for (auto b : this->impl->buckets) {
		if (size == b) {
			return;
		}
	}

	this->impl->buckets.push_back(size);
	std::sort(this->impl->buckets.begin(), this->impl->buckets.end());
}

std::vector<std::size_t> visionhub::v1::memoryPool::binSizes() {

	std::scoped_lock<std::mutex> lock(this->impl->mtx);

	return this->impl->buckets;
}
#pragma endregion


