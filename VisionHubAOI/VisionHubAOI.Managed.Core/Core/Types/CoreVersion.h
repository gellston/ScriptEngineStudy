#pragma once



#ifndef VISIONHUB_AOI_MANAGED_CORE_VERSION
#define VISIONHUB_AOI_MANAGED_CORE_VERSION


namespace VisionHub {
	namespace V1 {
		public value class CoreVersion {
		public:
			static const int Major();
			static const int Minor();
			static const int Patch();
		};
	}
}



#endif