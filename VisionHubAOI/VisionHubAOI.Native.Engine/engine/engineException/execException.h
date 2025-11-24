#pragma once


#ifndef VISIONHUB_AOI_NATIVE_EXEC_EXCEPTION
#define VISIONHUB_AOI_NATIVE_EXEC_EXCEPTION

#include "../engineMacro/api.h"


#include <stdexcept>
#include <memory>


namespace visionhub {
	namespace v1 {
		class impl_execException;
		class execException : public  std::runtime_error {

#pragma region Private Property
		private:
			std::shared_ptr<impl_execException> impl;
#pragma endregion

#pragma region Public Constructor
		public:
			VISIONHUB_AOI_NATIVE_ENGINE_API execException(const std::string& message, int lineNumber);
#pragma endregion

#pragma region Destructor
			VISIONHUB_AOI_NATIVE_ENGINE_API virtual ~execException();
#pragma endregion


#pragma region Public Functions
			VISIONHUB_AOI_NATIVE_ENGINE_API int lineNumber();
			VISIONHUB_AOI_NATIVE_ENGINE_API const char* what() const noexcept override;
#pragma endregion


		};
	}
}


#endif