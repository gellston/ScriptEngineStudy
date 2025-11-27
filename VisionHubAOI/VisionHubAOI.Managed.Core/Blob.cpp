
//C++


//C++/CLI
#include "Core/Collection/Blob.h"


//C#



#pragma region Constructor
VisionHub::V1::Blob::Blob(visionhub::v1::blob_ptr _blob) {
	*this->blob = _blob;
}

#pragma endregion

#pragma region Destructor
VisionHub::V1::Blob::~Blob() {
	this->Cleanup(false);
}
#pragma endregion


#pragma region Finalizer
VisionHub::V1::Blob::!Blob() {
	this->Cleanup(true);
}
#pragma endregion


#pragma region Private Functions
void VisionHub::V1::Blob::Cleanup(bool finalizing) {
	if (disposing == true) return;
	disposing = true;
	


	if (!finalizing) {
		//Managed Resource Cleanup
	}


	//Native Resource Cleanup
	if (this->blob != nullptr) {
		delete this->blob;
		this->blob = nullptr;
	}
	
}
#pragma endregion


#pragma region Public Property
std::size_t VisionHub::V1::Blob::Size::get() {
	return this->blob->get()->size();
}

System::IntPtr VisionHub::V1::Blob::Data::get() {
	return System::IntPtr(this->blob->get()->data());
}

System::IntPtr VisionHub::V1::Blob::Handle::get() {
	return System::IntPtr(this->blob);
}
#pragma endregion



