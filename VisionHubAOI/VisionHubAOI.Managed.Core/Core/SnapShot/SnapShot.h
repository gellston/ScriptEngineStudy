#pragma once

#ifndef VISIONHUB_AOI_MANAGED_CORE_SNAP_SHOT
#define VISIONHUB_AOI_MANAGED_CORE_SNAP_SHOT

//C++
#include <core/snapShot/snapShot.h>

//C++/CLI
#include "SnapFrame.h"
#include "SnapEntry.h"

//C#
using namespace System::Collections::Generic;

namespace VisionHub {
	namespace V1 {
		public ref class SnapShot {
#pragma region Private Property
		private:
			visionhub::v1::snapShot_ptr* snapShot = new visionhub::v1::snapShot_ptr();
			bool disposing = false;
#pragma endregion

#pragma region Constructor
		public:
			SnapShot(visionhub::v1::snapShot_ptr & snapShot);
			SnapShot(System::IntPtr handle);
#pragma endregion

#pragma region Destructor
			~SnapShot();
#pragma endregion

#pragma region Finalizer
			!SnapShot();
#pragma endregion

#pragma region Private Functions
		private:
			void Cleanup(bool finalizing);
#pragma endregion

#pragma region Public Property
		public:
			property List<SnapFrame^>^ Frames {
				List<SnapFrame^>^ get();
			}

			property List<SnapEntry^>^ Globals {
				List<SnapEntry^>^ get();
			}
#pragma endregion
		};
	}
}


#endif