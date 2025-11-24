

#include "core/snapShot/snapShot.h"


#include <iostream>

#pragma region IMPL
namespace visionhub {
	namespace v1 {
		struct impl_snapShot {
		public:
			std::vector<snapFrame_ptr> frames;
			std::vector<snapEntry_ptr > globals;



		};
	}
}
#pragma endregion


#pragma region Constructor
visionhub::v1::snapShot::snapShot() : impl(new impl_snapShot()) {

}


#pragma endregion

#pragma region Public Functions
void visionhub::v1::snapShot::print() {
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "[globals]:" << std::endl;
	for (auto& global : this->impl->globals) {
		std::cout << "{" << std::endl;
		global->print(1);
		std::cout << "}" << std::endl;
	}
	std::cout << std::endl;

	std::cout << "[frames]:" << std::endl;
	for (auto frame : this->impl->frames) {
		std::cout << "{" << std::endl;
		frame->print(1);
		std::cout << "}" << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

visionhub::v1::snapShot_ptr visionhub::v1::snapShot::clone() {
	auto temp = std::make_shared<snapShot>();
	temp->impl->frames = this->impl->frames;
	temp->impl->globals = this->impl->globals;

	return temp;
}

std::vector<visionhub::v1::snapFrame_ptr> visionhub::v1::snapShot::frames() {

	return this->impl->frames;
}
std::vector<visionhub::v1::snapEntry_ptr> visionhub::v1::snapShot::globals() {
	return this->impl->globals;
}

#pragma endregion


#pragma region Snap Shot Att
void visionhub::v1::snapShotAtt::addFrame(const snapShot_ptr& snapShot, const snapFrame_ptr& frame) {
	snapShot->impl->frames.push_back(frame);
}

void visionhub::v1::snapShotAtt::addGlobal(const snapShot_ptr& snapShot, const snapEntry_ptr& entry) {
	snapShot->impl->globals.push_back(entry);
}
#pragma endregion


