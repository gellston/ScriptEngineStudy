#pragma once



#ifndef VISIONHUB_AOI_MANAGED_CORE_EXECMODE
#define VISIONHUB_AOI_MANAGED_CORE_EXECMODE

namespace VisionHub {
	namespace V1 {
		public enum class ExecMode {
			Run = 0,
			StepOnce = 1,
			RunToBreakPoint = 2
		};
	}
}


#endif