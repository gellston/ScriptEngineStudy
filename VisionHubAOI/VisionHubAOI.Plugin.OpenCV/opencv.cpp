

#include "pluginOpencv/opencv.h"

#include <core/container/memoryPoolContainer.h>
#include <core/image.h>
#include <opencv2/opencv.hpp>



#pragma region Public Static Functions
std::shared_ptr<visionhub::v1::image> visionhub::v1::opencv::imread(const std::string& path, visionhub::v1::colorType colorType) {
	try {

		cv::ImreadModes mode = colorType == visionhub::v1::colorType::color ? cv::ImreadModes::IMREAD_COLOR : cv::ImreadModes::IMREAD_GRAYSCALE;

		auto cvImage = cv::imread(path, mode);
		
		if (cvImage.empty()) {
			throw std::exception("Invalid cv mat");
		}

		auto pool = visionhub::v1::memoryPoolContainer::get();
		auto image = std::make_shared<visionhub::v1::image>(cvImage.cols, cvImage.rows, cvImage.channels(), visionhub::v1::depthType::bit8, pool);
		std::memcpy(image->data().data, cvImage.data, image->size());
		return image;
	}
	catch (std::exception ex) {
		throw;
	}
}

void visionhub::v1::opencv::imwrite(const std::string & path, const std::shared_ptr<visionhub::v1::image> & image) {
	try {

		if (image == nullptr) {
			throw std::exception("Invalid image pointer");
		}


		auto cvImage = cv::Mat(image->height(), image->width(), CV_8UC1, image->data().data, image->stride());
		std::memcpy(cvImage.data, image->data().data, image->size());
		cv::imwrite(path, cvImage);
	}
	catch (std::exception ex) {
		throw;
	}
}
#pragma endregion
