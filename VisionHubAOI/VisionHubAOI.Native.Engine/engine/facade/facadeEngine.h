#pragma once


#ifndef VISIONHUB_AOI_NATIVE_ENGINE_FACADE
#define VISIONHUB_AOI_NATIVE_ENGINE_FACADE


#include <core/types/depthType.h>
#include <core/collection/value.h>
#include <core/object.h>

#include <string>
#include <iostream>


namespace visionhub {
	namespace v1 {
		class memoryPool;
		struct image;
		using image_ptr = sp<image>;
		struct facadeEngine {


#pragma region Private Property
		private:
			std::shared_ptr<memoryPool> pool;
			visionhub::v1::value_ptr _argument;
			visionhub::v1::value_ptr _output;
#pragma endregion

		public:

#pragma region Constructor
			facadeEngine();
#pragma endregion



#pragma region Public Functions
			std::shared_ptr<memoryPool> globalPool();
			void cout(const std::string& text);
			image_ptr make_image(unsigned int width, unsigned int height, unsigned int channel, depthType depth);

			void argument(const visionhub::v1::value_ptr& value);
			visionhub::v1::value_ptr output();
			void resetOutput();

			visionhub::v1::value argument();
			void output(const visionhub::v1::value & value);
			void output(const std::string& text, const object_ptr & object);
#pragma endregion

		};
	}
}



#endif