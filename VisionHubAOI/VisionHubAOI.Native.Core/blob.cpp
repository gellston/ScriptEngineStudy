
#include "core/collection/blob.h"
#include "core/collection/memoryBlock.h"

#include <vector>

#pragma region Impl
namespace visionhub {
	namespace v1 {
		struct impl_blob {
		public:

			//std::vector<uint8_t> data;
			//std::size_t size = 0;

			visionhub::v1::memoryBlock block;
		};
	}
}
#pragma endregion


#pragma region Constructor
visionhub::v1::blob::blob(const void* data, std::size_t n) : impl(new impl_blob()){


	if (data == nullptr) {
		throw std::exception("Invalid data pointer");
	}

	if (n <= 0) {
		throw std::exception("Invalid data size");
	}

	try {
		memoryBlock block;
		block.capacity = n;
		block.data = (uint8_t*)std::malloc(block.capacity);

		if (block.data == nullptr) {
			throw std::exception("Malloc failed");
		}

		std::memset(block.data, 0, block.capacity);
		block.holder = std::shared_ptr<void>(block.data, [this](void* raw) {
			if (!raw) return;
			std::free(raw);
		});

		this->impl->block = block;
	}
	catch (...) {
		throw;
	}

	std::memcpy(this->impl->block.data, data, n);

}

visionhub::v1::blob::blob(const visionhub::v1::memoryBlock & block) : impl(new impl_blob()) {

	this->impl->block = block;
}

visionhub::v1::blob::blob() : impl(new impl_blob()) {

}
#pragma endregion

#pragma region Public Functions
std::size_t visionhub::v1::blob::size() {
	return this->impl->block.capacity;
}

std::uint8_t* visionhub::v1::blob::data() {
	return this->impl->block.data;
}
#pragma endregion


#pragma region Static Functions
visionhub::v1::blob visionhub::v1::blob::from(const void* data, std::size_t n) {
	try {

		auto blob = visionhub::v1::blob(data, n);


		return blob;
	}
	catch(...){
		throw;
	}
}

//std::vector<uint8_t> visionhub::v1::blob::serialize(blob& blob) {
//
//	try {
//
//		std::vector<uint8_t> buffer;
//		buffer = blob.impl->data;
//
//		return buffer;
//	}
//	catch (...) {
//		throw;
//	}
//
//}

//visionhub::v1::blob visionhub::v1::blob::deserialize(std::vector<uint8_t> data) {
//	
//
//
//}
#pragma endregion
