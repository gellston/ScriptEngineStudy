

#include "engine/engineException/abortException.h"


#pragma region Constructor
visionhub::v1::abortException::abortException(const std::string& message) : std::runtime_error(message) {

}
#pragma endregion

#pragma region Destructor
visionhub::v1::abortException::~abortException() {

}
#pragma endregion



#pragma region Public Functions
const char* visionhub::v1::abortException::what() const noexcept {
	return std::runtime_error::what();
}
#pragma endregion
