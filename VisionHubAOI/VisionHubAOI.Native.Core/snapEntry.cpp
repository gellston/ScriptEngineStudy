
#include "core/snapShot/snapEntry.h"


#include <iostream>

#pragma region IMPL
namespace visionhub {
	namespace v1 {
		struct impl_snapEntry {
		public:
			std::string name;
			snapValue_ptr value;

		};
	}
}
#pragma endregion


#pragma region Constructor
visionhub::v1::snapEntry::snapEntry() : impl(new impl_snapEntry()) {

}
#pragma endregion

#pragma region Public Functions
void visionhub::v1::snapEntry::print(int intent) {
	std::cout << std::string(intent, '\t') << "{" << std::endl;
	std::cout << std::string(intent + 1, '\t') << "name:" << this->impl->name << std::endl;
	/*std::cout << std::string(intent, '\t') << "type:" << this->impl->value->type() << std::endl;
	*/
	this->impl->value->print(intent + 1);
	std::cout << std::string(intent, '\t') << "}" << std::endl;
}

visionhub::v1::snapEntry_ptr visionhub::v1::snapEntry::clone() {
	auto temp = std::make_shared<snapEntry>();
	temp->impl->name = this->impl->name;
	temp->impl->value = this->impl->value;
	return temp;
}

std::string visionhub::v1::snapEntry::name() {
	return this->impl->name;

}

visionhub::v1::snapValue_ptr visionhub::v1::snapEntry::value() {
	return this->impl->value;
}

#pragma endregion



#pragma region Snap Entry Att
void visionhub::v1::snapEntryAtt::setName(const visionhub::v1::snapEntry_ptr& e, const std::string & name) {
	e->impl->name = name;
}

void visionhub::v1::snapEntryAtt::setValue(const visionhub::v1::snapEntry_ptr& e, const visionhub::v1::snapValue_ptr& value) {
	e->impl->value = value;
}

#pragma endregion
