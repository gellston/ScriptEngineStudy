#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_BLOB
#define VISIONHUB_AOI_NATIVE_CORE_BLOB

#include "../coreMacro/api.h"

#include <memory>
#include <vector>

namespace visionhub {
	namespace v1 {
		struct blob;
		struct impl_blob;
		using sharedBlob = std::shared_ptr<blob>;
		struct memoryBlock;
		struct blob {
#pragma region Private Property
		private:
			std::shared_ptr<impl_blob> impl;
#pragma endregion

#pragma region Constructor
		public:
			VISIONHUB_AOI_NATIVE_CORE_API blob(const void* data, std::size_t n);
			VISIONHUB_AOI_NATIVE_CORE_API blob(const memoryBlock & block);
#pragma endregion

#pragma region Public Functions 
			VISIONHUB_AOI_NATIVE_CORE_API std::size_t size();
			VISIONHUB_AOI_NATIVE_CORE_API std::uint8_t* data();
#pragma endregion



#pragma region Static Functions
			static VISIONHUB_AOI_NATIVE_CORE_API blob from(const void* data, std::size_t n);
			//static VISIONHUB_AOI_NATIVE_CORE_API std::vector<uint8_t> serialize(blob& blob);
			//static VISIONHUB_AOI_NATIVE_CORE_API blob deserialize(std::vector<uint8_t> data);
#pragma endregion
		};
	}
}


#endif
