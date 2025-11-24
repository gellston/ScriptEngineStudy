#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_RUNTIME
#define VISIONHUB_AOI_NATIVE_CORE_RUNTIME


#include "handle.h"

#include <memory>

namespace visionhub {
	namespace v1 {
		class memoryPool;
		struct runtime {
		public:
			visionhub::v1::handle engine;
			
		};
	}
}

#endif