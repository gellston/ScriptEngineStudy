#pragma once


#ifndef VISIONHUB_AOI_NATIVE_SUSPEND_EXCEPTION
#define VISIONHUB_AOI_NATIVE_SUSPEND_EXCEPTION

#include "../engineMacro/api.h"


#include <stdexcept>


namespace visionhub {
	namespace v1 {
		class suspendException : public std::runtime_error {
#pragma region Public Constructor
		public:
			VISIONHUB_AOI_NATIVE_ENGINE_API suspendException(const std::string& message);
			VISIONHUB_AOI_NATIVE_ENGINE_API virtual ~suspendException();
#pragma endregion

#pragma region Public Functions
			VISIONHUB_AOI_NATIVE_ENGINE_API const char* what() const noexcept override;
#pragma endregion


		};
	}
}




#endif