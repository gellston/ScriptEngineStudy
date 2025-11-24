#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_RECT
#define VISIONHUB_AOI_NATIVE_CORE_RECT


#include "coreMacro/api.h"
#include "object.h"

#include "binding/helper.h"
#include "binding/staticCallStarter.h"



namespace visionhub {
	namespace v1 {
		struct rect;
		using rect_ptr = sp<rect>;
		struct rect : public visionhub::v1::object{
		public:
#pragma region Public Property
			double _x = 0;
			double _y = 0;
			double _width = 0;
			double _height = 0;
#pragma endregion

#pragma region Static Constructor
			STATIC_CTR_DECLARE()
#pragma endregion


#pragma region Public Constructor
			VISIONHUB_AOI_NATIVE_CORE_API rect(double x, double y, double width, double height);


			VISIONHUB_AOI_NATIVE_CORE_API static rect_ptr make_rect(double x, double y, double width, double height);

#pragma endregion

#pragma region Public Destructor
			VISIONHUB_AOI_NATIVE_CORE_API virtual ~rect() = default;
#pragma endregion

#pragma region Public Functions
			VISIONHUB_AOI_NATIVE_CORE_API snapValue_ptr snap() override;
			VISIONHUB_AOI_NATIVE_CORE_API double x();
			VISIONHUB_AOI_NATIVE_CORE_API double y();
			VISIONHUB_AOI_NATIVE_CORE_API double width();
			VISIONHUB_AOI_NATIVE_CORE_API double height();

			VISIONHUB_AOI_NATIVE_CORE_API void x(double value);
			VISIONHUB_AOI_NATIVE_CORE_API void y(double value);
			VISIONHUB_AOI_NATIVE_CORE_API void width(double value);
			VISIONHUB_AOI_NATIVE_CORE_API void height(double value);
#pragma endregion

#pragma region Implicit Conversion
			//IMPLICIT_CAST(rect, object)
#pragma endregion

		};
	}
}

#endif