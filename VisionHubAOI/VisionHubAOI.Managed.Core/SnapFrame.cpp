

#include <msclr/marshal_cppstd.h>


#include "Core/SnapShot/SnapFrame.h"


#pragma region Constructor
VisionHub::V1::SnapFrame::SnapFrame(visionhub::v1::snapFrame_ptr& snapFrame) {
	*this->snapFrame = snapFrame;
}
#pragma endregion


#pragma region Destructor
VisionHub::V1::SnapFrame::~SnapFrame() {

}
#pragma endregion


#pragma region Finalizer
VisionHub::V1::SnapFrame::!SnapFrame() {

}
#pragma endregion


#pragma region Private Functions
void VisionHub::V1::SnapFrame::Cleanup(bool finalizing) {

	if (this->disposing == true) return;
	this->disposing = true;


	if (!finalizing) {
		//Managed Resource Clean
	}


	if (this->snapFrame != nullptr) {
		delete this->snapFrame;
		this->snapFrame = nullptr;
	}

}
#pragma endregion


#pragma region Public Property
System::Collections::Generic::List<VisionHub::V1::SnapEntry^>^ VisionHub::V1::SnapFrame::Locals::get() {
	try {
		System::Collections::Generic::List<VisionHub::V1::SnapEntry^>^ managedSnapEntrys = gcnew System::Collections::Generic::List<VisionHub::V1::SnapEntry^>();
		auto& locals = this->snapFrame->get()->locals();

		for (auto& local : locals) {
			auto managedSnapEntry = gcnew VisionHub::V1::SnapEntry(local);
			managedSnapEntrys->Add(managedSnapEntry);
		}


		return managedSnapEntrys;
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}


VisionHub::V1::SnapEntry^ VisionHub::V1::SnapFrame::ThisObj::get() {
	try {
		auto thisObj = this->snapFrame->get()->thisObj();

		if (!thisObj.has_value())
			return nullptr;

		return gcnew VisionHub::V1::SnapEntry(thisObj.value());
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}



int VisionHub::V1::SnapFrame::Column::get() {
	return this->snapFrame->get()->column();
}

int VisionHub::V1::SnapFrame::Line::get() {
	return this->snapFrame->get()->line();
}

System::String^ VisionHub::V1::SnapFrame::Section::get() {
	return msclr::interop::marshal_as<System::String^>(this->snapFrame->get()->section());
}

System::String^ VisionHub::V1::SnapFrame::FunctionName::get() {
	return msclr::interop::marshal_as<System::String^>(this->snapFrame->get()->functionName());
}

bool VisionHub::V1::SnapFrame::HasThis::get() {
	return this->snapFrame->get()->hasThis();
}
#pragma endregion
