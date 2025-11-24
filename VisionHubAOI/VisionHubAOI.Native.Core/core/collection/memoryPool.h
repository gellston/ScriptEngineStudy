#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_MEMORY_POOL
#define VISIONHUB_AOI_NATIVE_CORE_MEMORY_POOL


#include "../coreMacro/api.h"


#include <memory>
#include <vector>

namespace visionhub {
	namespace v1 {
		class impl_memoryPool;
		struct memoryBlock;
		class memoryPool {

#pragma region IMPL
		private:
			std::unique_ptr<impl_memoryPool> impl;
#pragma endregion

#pragma region Private Functions


#pragma endregion


		public:
#pragma region Constructor
			VISIONHUB_AOI_NATIVE_CORE_API explicit memoryPool(const std::vector<std::size_t> & buckets = { 256 * 1024, 1 * 1024 * 1024, 4 * 1024 * 1024, 16 * 1024 * 1024 }, std::size_t alignment = 64);
#pragma endregion

#pragma region Destructor
			VISIONHUB_AOI_NATIVE_CORE_API ~memoryPool();
#pragma endregion

#pragma region Public Functions
			VISIONHUB_AOI_NATIVE_CORE_API visionhub::v1::memoryBlock acquire(std::size_t bytes);
			VISIONHUB_AOI_NATIVE_CORE_API void trim();
			VISIONHUB_AOI_NATIVE_CORE_API void addBinSize(std::size_t size);


			// Infomation 
			VISIONHUB_AOI_NATIVE_CORE_API std::vector<std::size_t> binSizes();
			VISIONHUB_AOI_NATIVE_CORE_API std::size_t totalSize();
			VISIONHUB_AOI_NATIVE_CORE_API std::size_t inUseSize();
			VISIONHUB_AOI_NATIVE_CORE_API std::size_t freeSize();
			
#pragma endregion
		};
	}
}

#endif
