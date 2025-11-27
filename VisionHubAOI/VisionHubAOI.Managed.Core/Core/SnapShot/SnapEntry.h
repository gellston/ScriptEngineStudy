#pragma once


#ifndef VISIONHUB_AOI_MANAGED_CORE_SNAP_ENTRY
#define VISIONHUB_AOI_MANAGED_CORE_SNAP_ENTRY


//C++
#include <core/snapShot/snapEntry.h>


//C++/CLI
#include "SnapValue.h"


//C#

namespace VisionHub {
	namespace V1 {
		public ref class SnapEntry {

#pragma region Private Property
		private:
			visionhub::v1::snapEntry_ptr * snapEntry = new visionhub::v1::snapEntry_ptr();
			bool disposing = false;
#pragma endregion

		public:

#pragma region Constructor
			SnapEntry(visionhub::v1::snapEntry_ptr & entry);
#pragma endregion

#pragma region Destructor
			~SnapEntry();
#pragma endregion

#pragma region Finalizer
			!SnapEntry();
#pragma endregion

#pragma region Private Functions
		private:
			void Cleanup(bool finalizing);
#pragma endregion

#pragma region Public Property
		public:
			property System::String^ Name {
				System::String^ get();
			}

			property VisionHub::V1::SnapValue^ Value {
				VisionHub::V1::SnapValue^ get();
			}
#pragma endregion


		};
	}
}



#endif