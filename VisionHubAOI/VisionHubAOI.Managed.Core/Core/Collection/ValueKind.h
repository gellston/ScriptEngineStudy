#pragma once


#ifndef VISIONHUB_AOI_MANAGED_CORE_VALUE_KIND
#define VISIONHUB_AOI_MANAGED_CORE_VALUE_KIND

namespace VisionHub {
	namespace V1 {
		enum class ValueKind {
			_NULL_ = 1,
			_Bool_,
			_Int8_,
			_Int16_,
			_Int32_,
			_Int64_,
			_Uint8_,
			_Uint16_,
			_Uint32_,
			_Uint64_,
			_Float_,
			_Double_,
			_String_,
			_Array_,
			_Map_,
			_Blob_,
		};
	}
}


#endif
