#pragma once


#ifndef VISIONHUB_AOI_MANAGED_CORE_SNAP_VALUE
#define VISIONHUB_AOI_MANAGED_CORE_SNAP_VALUE

//C++
#include <core/snapShot/snapValue.h>



//C++/CLI
#include "SnapKind.h"
#include "../Collection/MemoryBlock.h"


//C#

using namespace System::Collections::Generic;

namespace VisionHub {
	namespace V1 {
		public ref class SnapValue {

#pragma region Private Property
		private:
			visionhub::v1::snapValue_ptr* snapValue = new visionhub::v1::snapValue_ptr();
			bool disposing = false;
#pragma endregion

#pragma region Collection
		public:
			SnapValue(visionhub::v1::snapValue_ptr& value);
#pragma endregion

#pragma region Destructor
			~SnapValue();
#pragma endregion

#pragma region Finalizer
			!SnapValue();
#pragma endregion

#pragma region Private Functions
		private:
			void Cleanup(bool finalizing);
#pragma endregion


#pragma region Public Property
		public:
			property VisionHub::V1::SnapKind Kind{
				VisionHub::V1::SnapKind get();
			}

			property System::String^ Type {
				System::String^ get();
			}

			property int8_t Int8 {
				int8_t get();
			}

			property int16_t Int16 {
				int16_t get();
			}
			property int32_t Int32 {
				int32_t get();
			}
			property int64_t Int64 {
				int64_t get();
			}


			property uint8_t UInt8 {
				uint8_t get();
			}

			property uint16_t UInt16 {
				uint16_t get();
			}
			property uint32_t UInt32 {
				uint32_t get();
			}
			property uint64_t UInt64 {
				uint64_t get();
			}


			property double Double64 {
				double get();
			}

			property float Float32 {
				float get();
			}

			property bool Boolean {
				bool get();
			}

			property System::String^ String {
				System::String^ get();
			}

			property List<SnapValue^>^ Elements {
				List<SnapValue^>^ get();
			}

			property List<KeyValuePair<System::String^, VisionHub::V1::SnapValue^>>^ Fields {
				List<KeyValuePair<System::String^, VisionHub::V1::SnapValue^>>^ get();
			}

			property VisionHub::V1::MemoryBlock^ MemoryBlock {
				VisionHub::V1::MemoryBlock^ get();
			}


#pragma endregion




		};
	}
}

#endif