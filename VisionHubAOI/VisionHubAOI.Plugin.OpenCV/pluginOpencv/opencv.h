#pragma once



#ifndef VISIONHUB_AOI_PLUGIN_OPENCV
#define VISIONHUB_AOI_PLUGIN_OPENCV


#include <core/types/colorType.h>

#include <string>
#include <memory>

namespace visionhub {
	namespace v1 {
		struct image;
		class opencv {
		public:

#pragma region Public Static Functions
			static std::shared_ptr<image> imread(const std::string& path, visionhub::v1::colorType colorType);
			static void imwrite(const std::string& path, const std::shared_ptr<image> & image);
#pragma endregion

		};

	}
}


#endif