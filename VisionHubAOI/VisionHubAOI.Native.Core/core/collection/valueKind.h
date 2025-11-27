#pragma once

#ifndef VISIONHUB_AOI_NATIVE_CORE_VALUE_KIND
#define VISIONHUB_AOI_NATIVE_CORE_VALUE_KIND

namespace visionhub {
	namespace v1 {
		enum class valueKind {
			_null_ = 1,
			_bool_,
			_int8_,
			_int16_,
			_int32_,
			_int64_,
			_uint8_,
			_uint16_,
			_uint32_,
			_uint64_,
			_float_,
			_double_,
			_string_,
			_array_,
			_map_,
			_blob_,
		};
	}
}

#endif