
#include "core/snapShot/snapFrame.h"

#include <iostream>

#pragma region IMPL

namespace visionhub {
	namespace v1 {
		struct impl_snapFrame {
		public:

			std::string function;
			std::string section;

			int line = 0;
			int column = 0;

			std::vector<snapEntry_ptr> locals;
			std::optional<snapEntry_ptr> thisObj;
		};
	}
}
#pragma endregion


#pragma region Constructor
visionhub::v1::snapFrame::snapFrame() : impl(new impl_snapFrame()) {

}
#pragma endregion

#pragma region Public Functions
void visionhub::v1::snapFrame::print(int intent) {
	std::cout << std::string(intent, '\t') << "function:" << this->impl->function << std::endl;
	std::cout << std::string(intent, '\t') << "section:" << this->impl->section << std::endl;
	std::cout << std::string(intent, '\t') << "line:" << this->impl->line << std::endl;
	std::cout << std::string(intent, '\t') << "column:" << this->impl->column << std::endl;

	std::cout << std::string(intent, '\t') << "[local]" << std::endl;
	std::cout << std::string(intent, '\t') << "{" << std::endl;
	
	auto locals = this->locals();
	for (auto local : locals) {
		local->print(intent + 1);
	}

	std::cout << std::string(intent, '\t') << "}" << std::endl;
}

std::vector<visionhub::v1::snapEntry_ptr> visionhub::v1::snapFrame::locals() {
	return this->impl->locals;
}

std::optional<visionhub::v1::snapEntry_ptr> visionhub::v1::snapFrame::thisObj() {
	return this->impl->thisObj;
}


int visionhub::v1::snapFrame::column() {
	return this->impl->column;
}

int visionhub::v1::snapFrame::line() {
	return this->impl->line;
}

std::string visionhub::v1::snapFrame::section() {
	return this->impl->section;
}
std::string visionhub::v1::snapFrame::functionName() {
	return this->impl->function;
}
#pragma endregion



#pragma region Snap Frame Attorney


void visionhub::v1::snapFrameAtt::setColumn(const snapFrame_ptr& frame, int  column) {
	frame->impl->column = column;
}
void visionhub::v1::snapFrameAtt::setSection(const snapFrame_ptr& frame, const std::string & section) {
	frame->impl->section = section;
}
void visionhub::v1::snapFrameAtt::setFuncName(const snapFrame_ptr& frame, const std::string & name) {
	frame->impl->function = name;
}
void visionhub::v1::snapFrameAtt::setThisObj(const snapFrame_ptr& frame, const snapEntry_ptr & entry) {
	frame->impl->thisObj = entry;
}

void visionhub::v1::snapFrameAtt::addLocals(const snapFrame_ptr& frame, const snapEntry_ptr& local) {
	frame->impl->locals.push_back(local);
}

void visionhub::v1::snapFrameAtt::setLine(const snapFrame_ptr& frame, int  line) {
	frame->impl->line = line;
}

#pragma endregion



