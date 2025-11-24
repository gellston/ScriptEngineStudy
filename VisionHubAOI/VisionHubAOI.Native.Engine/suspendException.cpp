

#include "engine/engineException/suspendException.h"


#pragma region Constructor
visionhub::v1::suspendException::suspendException(const std::string& message) : std::runtime_error(message) {

}
#pragma endregion

#pragma region Destructor
visionhub::v1::suspendException::~suspendException() {

}
#pragma endregion



#pragma region Public Functions
const char* visionhub::v1::suspendException::what() const noexcept {
	return std::runtime_error::what();
}
#pragma endregion
