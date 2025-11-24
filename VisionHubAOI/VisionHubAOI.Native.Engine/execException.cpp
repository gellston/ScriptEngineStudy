

#include "engine/engineException/execException.h"



#pragma region IMPL
namespace visionhub {
	namespace v1 {
		class impl_execException {
		public:

			int lineNumber = -1;
		};
	}
}

#pragma endregion


#pragma region Constructor
visionhub::v1::execException::execException(const std::string& message, int number): impl(new impl_execException()), std::runtime_error(message){

	this->impl->lineNumber = number;
}
#pragma endregion

#pragma region Destructor
visionhub::v1::execException::~execException() {

}
#pragma endregion



#pragma region Public Functions
int visionhub::v1::execException::lineNumber() {
	return this->impl->lineNumber;
}

const char* visionhub::v1::execException::what() const noexcept {
	return std::runtime_error::what();
}

#pragma endregion
