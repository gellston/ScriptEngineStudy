
#include "Core/SnapShot/SnapShot.h"


#pragma region Constructor
VisionHub::V1::SnapShot::SnapShot(visionhub::v1::snapShot_ptr& snapShot) {
	*this->snapShot = snapShot;
}


VisionHub::V1::SnapShot::SnapShot(System::IntPtr handle) {

	auto snapShot = *((visionhub::v1::snapShot_ptr *)handle.ToPointer());
	*this->snapShot = snapShot;
}
#pragma endregion

#pragma region Destructor
VisionHub::V1::SnapShot::~SnapShot() {
	this->Cleanup(false);
}
#pragma endregion

#pragma region Finalizer
VisionHub::V1::SnapShot::!SnapShot() {
	this->Cleanup(true);
}
#pragma endregion

#pragma region Private Functions
void VisionHub::V1::SnapShot::Cleanup(bool finalizing) {
	if (this->disposing == true) return;
	this->disposing = true;


	if (!finalizing) {
		//Managed Code Cleanup
	}


	//Native Code Cleaup
	if (this->snapShot != nullptr) {
		delete this->snapShot;
	}
}
#pragma endregion


#pragma region Public Property
List<VisionHub::V1::SnapFrame^>^ VisionHub::V1::SnapShot::Frames::get() {
	try {

		List<VisionHub::V1::SnapFrame^>^ temp = gcnew List<VisionHub::V1::SnapFrame^>();

		auto& frames = this->snapShot->get()->frames();

		for (auto& frame : frames) {
			auto managedFrame = gcnew VisionHub::V1::SnapFrame(frame);
			temp->Add(managedFrame);
		}

		return temp;
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}

List<VisionHub::V1::SnapEntry^>^ VisionHub::V1::SnapShot::Globals::get() {
	try {
		List<VisionHub::V1::SnapEntry^>^ temp = gcnew List<VisionHub::V1::SnapEntry^>();

		auto& globals = this->snapShot->get()->globals();

		for (auto& global : globals) {
			auto managedGlobal = gcnew VisionHub::V1::SnapEntry(global);
			temp->Add(managedGlobal);
		}

		return temp;
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}
#pragma endregion
