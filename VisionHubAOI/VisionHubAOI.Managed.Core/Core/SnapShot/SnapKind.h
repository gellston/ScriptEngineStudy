#pragma once

#ifndef VISIONHUB_AOI_MANAGED_CORE_SNAP_KIND
#define VISIONHUB_AOI_MANAGED_CORE_SNAP_KIND


namespace VisionHub {
	namespace V1 {
		enum class SnapKind {
			_NULL_ = 1,
			_Bool_,
			_Int8_,
			_Int16_,
			_Int32_,
			_Int64_,
			_UInt8_,
			_UInt16_,
			_UInt32_,
			_UInt64_,
			_Float_,
			_Double_,
			_String_,
			_Array_,
			_Map_,
			_Memory_,
			_Unidentified_,
			_Script_,
			_Native_
		};
	}
}

#endif