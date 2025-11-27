#pragma once


#ifndef VISIONHUB_AOI_MANAGED_CORE_SNAP_FRAME
#define VISIONHUB_AOI_MANAGED_CORE_SNAP_FRAME


//C++
#include <core/snapShot/snapFrame.h>

//C++/CLI
#include "SnapEntry.h"


//C#

namespace VisionHub {
	namespace V1 {
		public ref class SnapFrame {
#pragma region Private Property
		private:
			visionhub::v1::snapFrame_ptr* snapFrame = new visionhub::v1::snapFrame_ptr();
			bool disposing = false;
#pragma endregion

#pragma region Constructor
		public:
			SnapFrame(visionhub::v1::snapFrame_ptr& snapFrame);
#pragma endregion

#pragma region Destructor
			~SnapFrame();
#pragma endregion

#pragma region Finalizer
			!SnapFrame();
#pragma endregion


#pragma region Private Functions
		private:
			void Cleanup(bool finalizing);
#pragma endregion

#pragma region Public Property
		public:
			property System::Collections::Generic::List<SnapEntry^>^ Locals{
				System::Collections::Generic::List<SnapEntry^>^ get();
			}

			property SnapEntry^ ThisObj {
				SnapEntry^ get();
			}

			property int Column {
				int get();
			}

			property int Line {
				int get();
			}

			property System::String^ Section {
				System::String^ get();
			}

			property System::String^ FunctionName {
				System::String^ get();
			}

			property bool HasThis {
				bool get();
			}
#pragma endregion






		};
	}
}

#endif