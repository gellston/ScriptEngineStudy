#pragma once

#ifndef VISIONHUB_AOI_NATIVE_CORE_BINDING_STATIC_CALL_STARTER
#define VISIONHUB_AOI_NATIVE_CORE_BINDING_STATIC_CALL_STARTER

#include "../coreMacro/api.h"

#include <functional>

namespace visionhub {
	namespace v1 {
		struct staticCallStarter {

#pragma region Constructor
		public:
			VISIONHUB_AOI_NATIVE_CORE_API staticCallStarter(std::function<void()> caller);
#pragma endregion

		};
	}
}


#define STATIC_CTR_DECLARE()\
static void staticConstructor();\
static visionhub::v1::staticCallStarter constructor;\


#define STATIC_CTR_DEFINE(TYPE)\
visionhub::v1::staticCallStarter TYPE::constructor(TYPE::staticConstructor);\
void TYPE::staticConstructor()\

#endif

