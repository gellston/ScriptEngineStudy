#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_TEST
#define VISIONHUB_AOI_NATIVE_CORE_TEST


#include "coreMacro/api.h"
#include "object.h"

#include "binding/helper.h"
#include "binding/staticCallStarter.h"


#include <string>



namespace visionhub {
	namespace v1 {
		struct test;
		using test_ptr = sp<test>;
		struct test : public visionhub::v1::object {
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
			VISIONHUB_AOI_NATIVE_CORE_API test(double x, double y, double width, double height);


			VISIONHUB_AOI_NATIVE_CORE_API static test_ptr make_test(double x, double y, double width, double height);

#pragma endregion

#pragma region Public Destructor
			VISIONHUB_AOI_NATIVE_CORE_API virtual ~test() = default;
#pragma endregion

#pragma region Public Functions
			VISIONHUB_AOI_NATIVE_CORE_API std::shared_ptr<snapValue> snap() override;
			VISIONHUB_AOI_NATIVE_CORE_API double x();
			VISIONHUB_AOI_NATIVE_CORE_API double y();
			VISIONHUB_AOI_NATIVE_CORE_API double width();
			VISIONHUB_AOI_NATIVE_CORE_API double height();

			VISIONHUB_AOI_NATIVE_CORE_API void x(double value);
			VISIONHUB_AOI_NATIVE_CORE_API void y(double value);
			VISIONHUB_AOI_NATIVE_CORE_API void width(double value);
			VISIONHUB_AOI_NATIVE_CORE_API void height(double value);
			VISIONHUB_AOI_NATIVE_CORE_API std::vector<test_ptr> get();
			VISIONHUB_AOI_NATIVE_CORE_API std::unordered_map<std::string, test_ptr> get2();
			VISIONHUB_AOI_NATIVE_CORE_API std::unordered_map<std::string, int> get3();
#pragma endregion

#pragma region Implicit Conversion
			//IMPLICIT_CAST(test, object)
#pragma endregion

		};
	}
}

#endif