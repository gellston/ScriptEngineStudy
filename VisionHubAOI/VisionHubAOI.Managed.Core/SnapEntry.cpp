

//C++
#include <msclr/marshal_cppstd.h>


//C++/CLI
#include "Core/SnapShot/SnapEntry.h"



//C#


#pragma region Constructor
VisionHub::V1::SnapEntry::SnapEntry(visionhub::v1::snapEntry_ptr& entry) {

	*this->snapEntry = entry;
}
#pragma endregion


#pragma region Destructor
VisionHub::V1::SnapEntry::~SnapEntry() {

}
#pragma endregion

#pragma region Finalizer
VisionHub::V1::SnapEntry::!SnapEntry() {

}
#pragma endregion

#pragma region Private Functions
void VisionHub::V1::SnapEntry::Cleanup(bool finalizing) {

	if (this->disposing == true) return;
	this->disposing = true;



	if (!finalizing) {
		//Managed Resource Clean
	}


	if (this->snapEntry != nullptr) {
		delete this->snapEntry;
		this->snapEntry = nullptr;
	}

}
#pragma endregion


#pragma region Public Property
System::String^ VisionHub::V1::SnapEntry::Name::get() {
	return msclr::interop::marshal_as<System::String^>(this->snapEntry->get()->name());
}

VisionHub::V1::SnapValue^ VisionHub::V1::SnapEntry::Value::get() {
	return gcnew VisionHub::V1::SnapValue(this->snapEntry->get()->value());
}
#pragma endregion


