#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_EXECMODE
#define VISIONHUB_AOI_NATIVE_CORE_EXECMODE


namespace visionhub {
	namespace v1 {
		enum class execMode {
			run = 0,
			stepOnce = 1,
			runToBreakPoint = 2,
		};
	}
}


#endif