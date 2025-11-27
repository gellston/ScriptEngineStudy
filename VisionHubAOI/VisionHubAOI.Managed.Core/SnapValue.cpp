

//C++
#include <msclr/marshal_cppstd.h>



//C++/CLI
#include "Core/SnapShot/SnapValue.h"


//C#



#pragma region Constructor
VisionHub::V1::SnapValue::SnapValue(visionhub::v1::snapValue_ptr& value) {
	*this->snapValue = value;
}
#pragma endregion


#pragma region Destructor
VisionHub::V1::SnapValue::~SnapValue() {

	this->Cleanup(false);
}
#pragma endregion

#pragma region Finalizer
VisionHub::V1::SnapValue::!SnapValue() {
	this->Cleanup(true);
}
#pragma endregion

#pragma region Private Functions
void VisionHub::V1::SnapValue::Cleanup(bool finalizing) {
	if (this->disposing == true) return; 
	this->disposing = true;


	if (!finalizing) {
		//managed resource clean;
	}


	if (this->snapValue != nullptr) {
		delete this->snapValue;
	}
}
#pragma endregion


#pragma region Public Property
VisionHub::V1::SnapKind VisionHub::V1::SnapValue::Kind::get() {
	return safe_cast<VisionHub::V1::SnapKind>(this->snapValue->get()->kind());
}


System::String^ VisionHub::V1::SnapValue::Type::get() {
	return msclr::interop::marshal_as<System::String^>(this->snapValue->get()->type());
}

int8_t VisionHub::V1::SnapValue::Int8::get() {
	return this->snapValue->get()->int8();
}

int16_t VisionHub::V1::SnapValue::Int16::get() {
	return this->snapValue->get()->int16();
}

int32_t VisionHub::V1::SnapValue::Int32::get() {
	return this->snapValue->get()->int32();
}

int64_t VisionHub::V1::SnapValue::Int64::get() {
	return this->snapValue->get()->int64();
}


uint8_t VisionHub::V1::SnapValue::UInt8::get() {
	return this->snapValue->get()->uint8();
}

uint16_t VisionHub::V1::SnapValue::UInt16::get() {
	return this->snapValue->get()->uint16();
}

uint32_t VisionHub::V1::SnapValue::UInt32::get() {
	return this->snapValue->get()->uint32();
}

uint64_t VisionHub::V1::SnapValue::UInt64::get() {
	return this->snapValue->get()->uint64();
}

double VisionHub::V1::SnapValue::Double64::get() {
	return this->snapValue->get()->double64();
}

float VisionHub::V1::SnapValue::Float32::get() {
	return this->snapValue->get()->float32();
}


bool VisionHub::V1::SnapValue::Boolean::get() {
	return this->snapValue->get()->boolean();
}

System::String^ VisionHub::V1::SnapValue::String::get() {
	return msclr::interop::marshal_as<System::String^>(this->snapValue->get()->string());
}

List<VisionHub::V1::SnapValue^>^ VisionHub::V1::SnapValue::Elements::get() {
	try {

		List<VisionHub::V1::SnapValue^>^ temp = gcnew List<VisionHub::V1::SnapValue^>();


		auto& elements = this->snapValue->get()->elements();

		for (auto& element : elements) {

			auto managedSnapValue = gcnew VisionHub::V1::SnapValue(element);
			temp->Add(managedSnapValue);
		}

		return temp;

	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}


List<KeyValuePair<System::String^, VisionHub::V1::SnapValue^>>^ VisionHub::V1::SnapValue::Fields::get() {
	try {

		List<KeyValuePair<System::String^, VisionHub::V1::SnapValue^>>^ temp = gcnew List<KeyValuePair<System::String^, VisionHub::V1::SnapValue^>>();

		auto& fields = this->snapValue->get()->fields();

		for (auto& field : fields) {
			
			auto managedKey = msclr::interop::marshal_as<System::String^>(field.first);
			auto managedValue = gcnew VisionHub::V1::SnapValue(field.second);


			KeyValuePair<System::String^, VisionHub::V1::SnapValue^> pair = KeyValuePair<System::String^, VisionHub::V1::SnapValue^>(managedKey, managedValue);
			temp->Add(pair);
		}

		return temp;
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}


VisionHub::V1::MemoryBlock^ VisionHub::V1::SnapValue::MemoryBlock::get() {
	try {
		auto& memoryBlock = this->snapValue->get()->memoryBlock();
		return gcnew VisionHub::V1::MemoryBlock(memoryBlock);
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}
#pragma endregion





