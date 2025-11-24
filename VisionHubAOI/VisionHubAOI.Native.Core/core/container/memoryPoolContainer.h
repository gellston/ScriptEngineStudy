#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_MEMORY_POOL_CONTAINER
#define VISIONHUB_AOI_NATIVE_CORE_MEMORY_POOL_CONTAINER

#include "../collection/memoryPool.h"


#include <memory>
#include <vector>
#include <atomic>

namespace visionhub {
	namespace v1 {
		struct memoryBlock;
		class memoryPool;
		class memoryPoolContainer {

#pragma region Types
		private:
			struct state {
				std::shared_ptr<memoryPool> pool = nullptr;
			};

			memoryPoolContainer() = delete;
#pragma endregion

#pragma region Public Functions
		public:

			inline static state& slot() {
				static state s;

				return s;
			}

			inline static void set(const std::shared_ptr<memoryPool> & pool) {
				auto & state = slot();
				state.pool = pool;
			}

			inline static std::shared_ptr<memoryPool> get() {
				auto & state = slot();
				return state.pool;
			}
#pragma endregion


		};
	}
}

#endif
