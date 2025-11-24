#pragma once


#include <core/plugin/api.h>


#include "opencv.h"

VISIONHUB_PLUGIN(binder, 0, 0, 0) {
	

	try {


		binder
			.nameSpace("opencv")
			.addAutoGlobalFunction1(visionhub::v1::opencv, imread, "core::image_ptr imread(const string&in, core::colorType)")
			.addAutoGlobalFunction1(visionhub::v1::opencv, imwrite, "void imwrite(const string&in, const core::image_ptr&in)");

		return PLUGIN_OK;
	}
	catch (std::exception ex) {
		return PLUGIN_ERROR;
	}

	
}