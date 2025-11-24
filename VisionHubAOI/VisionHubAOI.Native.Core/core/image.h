#pragma once



#ifndef VISIONHUB_AOI_NATIVE_CORE_IMAGE
#define VISIONHUB_AOI_NATIVE_CORE_IMAGE



#include "coreMacro/api.h"
#include "types/depthType.h"
#include "object.h"

#include "binding/helper.h"
#include "binding/staticCallStarter.h"

#include "collection/memoryBlock.h"





namespace visionhub {
	namespace v1 {
		struct image;
		class memoryPool;
		struct impl_image;
		using image_ptr = sp<image>;
		struct image : public visionhub::v1::object {

#pragma region Private Property
		private:
			std::unique_ptr<impl_image> impl;
#pragma endregion

		public:
#pragma region Public Constructor
			VISIONHUB_AOI_NATIVE_CORE_API image(unsigned int width, 
												unsigned int height, 
												unsigned int channel, 
												depthType depth);

			VISIONHUB_AOI_NATIVE_CORE_API image(unsigned int width, 
												unsigned int height, 
												unsigned int channel, 
												depthType depth, 
												std::shared_ptr<memoryPool> pool);


			VISIONHUB_AOI_NATIVE_CORE_API static image_ptr make_image(unsigned int width,unsigned int height,unsigned int channel,depthType depth);

#pragma endregion

#pragma region Static Constructor
			STATIC_CTR_DECLARE()
#pragma endregion


#pragma region Public Destructor
			VISIONHUB_AOI_NATIVE_CORE_API virtual ~image();
#pragma endregion

#pragma region Public Functions
			VISIONHUB_AOI_NATIVE_CORE_API snapValue_ptr snap() override;
			VISIONHUB_AOI_NATIVE_CORE_API unsigned int width();
			VISIONHUB_AOI_NATIVE_CORE_API unsigned int height();
			VISIONHUB_AOI_NATIVE_CORE_API unsigned int channel();
			VISIONHUB_AOI_NATIVE_CORE_API std::size_t stride();
			VISIONHUB_AOI_NATIVE_CORE_API std::size_t size();
			VISIONHUB_AOI_NATIVE_CORE_API depthType depth();
			VISIONHUB_AOI_NATIVE_CORE_API memoryBlock data();
#pragma endregion

#pragma region Implicit Conversion
			//IMPLICIT_CAST(image, object)
#pragma endregion

		};
	}
}

#endif