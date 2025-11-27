#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_MEMORY_BLOCK
#define VISIONHUB_AOI_NATIVE_CORE_MEMORY_BLOCK

#include <cinttypes>
#include <memory>

namespace visionhub {
	namespace v1 {
		struct memoryBlock {
		public:
			uint8_t* data = nullptr;
			std::size_t capacity = 0;
			std::shared_ptr<void> holder;
			explicit operator bool() const noexcept {
				return data != nullptr;
			}
		};

		using memoryBlock_ptr = std::shared_ptr<memoryBlock>;
	}
}


#endif
