

//C++
#include <msclr/marshal_cppstd.h>



//C++/CLI
#include "Core/Collection/Value.h"



//C#


#pragma region Constructor
VisionHub::V1::Value::Value(visionhub::v1::value_ptr _value) {
	*this->value = _value;
}

VisionHub::V1::Value::Value(visionhub::v1::value& _value) {
	*this->value = std::make_shared<visionhub::v1::value>(_value);
}


VisionHub::V1::Value::Value(System::IntPtr handle) {
	visionhub::v1::value_ptr* pointer = (visionhub::v1::value_ptr*)handle.ToPointer();
	*this->value = *pointer;
}

VisionHub::V1::Value::Value(const bool& _value) {
	*this->value = std::make_shared<visionhub::v1::value>(_value);
}

VisionHub::V1::Value::Value(const int8_t& _value) {
	*this->value = std::make_shared<visionhub::v1::value>(_value);
}

VisionHub::V1::Value::Value(const int16_t& _value) {
	*this->value = std::make_shared<visionhub::v1::value>(_value);
}

VisionHub::V1::Value::Value(const int32_t& _value) {
	*this->value = std::make_shared<visionhub::v1::value>(_value);
}

VisionHub::V1::Value::Value(const int64_t& _value) {
	*this->value = std::make_shared<visionhub::v1::value>(_value);
}



VisionHub::V1::Value::Value(const uint8_t& _value) {
	*this->value = std::make_shared<visionhub::v1::value>(_value);
}

VisionHub::V1::Value::Value(const uint16_t& _value) {
	*this->value = std::make_shared<visionhub::v1::value>(_value);
}

VisionHub::V1::Value::Value(const uint32_t& _value) {
	*this->value = std::make_shared<visionhub::v1::value>(_value);
}

VisionHub::V1::Value::Value(const uint64_t& _value) {
	*this->value = std::make_shared<visionhub::v1::value>(_value);
}

VisionHub::V1::Value::Value(const float& _value) {
	*this->value = std::make_shared<visionhub::v1::value>(_value);
}

VisionHub::V1::Value::Value(const double& _value) {
	*this->value = std::make_shared<visionhub::v1::value>(_value);
}

VisionHub::V1::Value::Value(System::String^ _value) {
	auto& temp = msclr::interop::marshal_as<std::string>(_value);
	*this->value = std::make_shared<visionhub::v1::value>(temp);
}

VisionHub::V1::Value::Value(Map^ _value) {

	std::unordered_map<std::string, visionhub::v1::value> temp;
	for each (auto pair in _value) {
		auto nativeKey = msclr::interop::marshal_as<std::string>(pair.Key);
		auto & nativeValue = *(pair.Value->value->get());
		temp[nativeKey] = nativeValue;
	}

	*this->value = std::make_shared<visionhub::v1::value>(temp);
}

VisionHub::V1::Value::Value(Array^ _value) {
	std::vector<visionhub::v1::value> temp;

	for (int index = 0; index < _value->Count; index++) {
		auto managedValue = _value[index];
		auto& nativeValue = *(*(managedValue->value));
		temp.push_back(nativeValue);
	}
	*this->value = std::make_shared<visionhub::v1::value>(temp);
}

VisionHub::V1::Value::Value(Blob^ _value) {
	visionhub::v1::blob_ptr * blob =  (visionhub::v1::blob_ptr*)_value->Handle.ToPointer();
	*this->value = std::make_shared<visionhub::v1::value>(**blob);
}

#pragma endregion

#pragma region Destructor
VisionHub::V1::Value::~Value() {
	this->Cleanup(false);
}
#pragma endregion


#pragma region Finalizer
VisionHub::V1::Value::!Value() {
	this->Cleanup(true);
}
#pragma endregion


#pragma region Private Functions
void VisionHub::V1::Value::Cleanup(bool finalizing) {
	if (this->disposing == true) return;
	this->disposing = true;

	if (!finalizing) {
		//Managed Code Free
	}

	if (this->value != nullptr) {
		delete this->value;
		this->value = nullptr;
	}
}
#pragma endregion


#pragma region Public Property
VisionHub::V1::ValueKind VisionHub::V1::Value::Kind::get() {
	return safe_cast<VisionHub::V1::ValueKind>(this->value->get()->kind());
}

std::size_t VisionHub::V1::Value::Size::get() {
	return this->value->get()->size();
}

std::size_t VisionHub::V1::Value::Count::get() {
	return this->value->get()->count();
}


System::Collections::Generic::List<System::String^>^ VisionHub::V1::Value::Keys::get() {
	System::Collections::Generic::List<System::String^>^ temp = gcnew System::Collections::Generic::List<System::String^>();
	auto& keys = this->value->get()->keys();
	for (auto& key : keys) {
		temp->Add(msclr::interop::marshal_as<System::String^>(key));
	}
	return temp;
}

VisionHub::V1::Value^ VisionHub::V1::Value::default::get(System::String^ key) {

	try {

		auto& nativeKey = msclr::interop::marshal_as<std::string>(key);
		auto& value = *(this->value->get());
		auto& returnValue = value[nativeKey];

		return gcnew VisionHub::V1::Value(returnValue);
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}


VisionHub::V1::Value^ VisionHub::V1::Value::default::get(int index) {

	try {

		auto& value = *(this->value->get());
		auto& returnValue = value[index];

		return gcnew VisionHub::V1::Value(returnValue);
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}


System::IntPtr VisionHub::V1::Value::Handle::get() {
	try {
		return System::IntPtr(this->value);
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}
#pragma endregion


#pragma region Public Functions
bool VisionHub::V1::Value::Get(bool% value) {
	bool nativeValue = false;
	auto retValue = this->value->get()->get(nativeValue);
	if(retValue)
		value = nativeValue;
	return retValue;
}

bool VisionHub::V1::Value::Get(int8_t% value) {
	int8_t nativeValue = false;
	auto retValue = this->value->get()->get(nativeValue);
	if (retValue)
		value = nativeValue;
	return retValue;
}

bool VisionHub::V1::Value::Get(int16_t% value) {
	int16_t nativeValue = false;
	auto retValue = this->value->get()->get(nativeValue);
	if (retValue)
		value = nativeValue;
	return retValue;
}

bool VisionHub::V1::Value::Get(int32_t% value) {
	int32_t nativeValue = false;
	auto retValue = this->value->get()->get(nativeValue);
	if (retValue)
		value = nativeValue;
	return retValue;
}

bool VisionHub::V1::Value::Get(int64_t% value) {
	int64_t nativeValue = false;
	auto retValue = this->value->get()->get(nativeValue);
	if (retValue)
		value = nativeValue;
	return retValue;
}



bool VisionHub::V1::Value::Get(uint8_t% value) {
	uint8_t nativeValue = false;
	auto retValue = this->value->get()->get(nativeValue);
	if (retValue)
		value = nativeValue;
	return retValue;
}

bool VisionHub::V1::Value::Get(uint16_t% value) {
	uint16_t nativeValue = false;
	auto retValue = this->value->get()->get(nativeValue);
	if (retValue)
		value = nativeValue;
	return retValue;
}

bool VisionHub::V1::Value::Get(uint32_t% value) {
	uint32_t nativeValue = false;
	auto retValue = this->value->get()->get(nativeValue);
	if (retValue)
		value = nativeValue;
	return retValue;
}

bool VisionHub::V1::Value::Get(uint64_t% value) {
	uint64_t nativeValue = false;
	auto retValue = this->value->get()->get(nativeValue);
	if (retValue)
		value = nativeValue;
	return retValue;
}

bool VisionHub::V1::Value::Get(float% value) {
	float nativeValue = false;
	auto retValue = this->value->get()->get(nativeValue);
	if (retValue)
		value = nativeValue;
	return retValue;
}

bool VisionHub::V1::Value::Get(double% value) {
	double nativeValue = false;
	auto retValue = this->value->get()->get(nativeValue);
	if (retValue)
		value = nativeValue;
	return retValue;
}


bool VisionHub::V1::Value::Get(System::String^% value) {
	std::string nativeValue = "";
	auto retValue = this->value->get()->get(nativeValue);
	if (retValue)
		value = msclr::interop::marshal_as<System::String^>(nativeValue);
	return retValue;
}


bool VisionHub::V1::Value::Get(Map^% value) {
	visionhub::v1::map nativeValue;
	auto retValue = this->value->get()->get(nativeValue);
	if (retValue) {

		auto managedValue = gcnew System::Collections::Generic::Dictionary<System::String^, VisionHub::V1::Value^>();

		for (auto& keypair : nativeValue) {
			managedValue->Add(
				msclr::interop::marshal_as<System::String^>(keypair.first),
				gcnew VisionHub::V1::Value(keypair.second));
		}
		value = managedValue;
	}
		
	return retValue;
}

bool VisionHub::V1::Value::Get(Array^% value) {
	visionhub::v1::array nativeValue;
	auto retValue = this->value->get()->get(nativeValue);
	if (retValue) {
		auto managedValue = gcnew System::Collections::Generic::List<VisionHub::V1::Value^>();
		for (auto& element : nativeValue) {
			managedValue->Add(gcnew VisionHub::V1::Value(element));
		}
		value = managedValue;
	}
	return retValue;
}

bool VisionHub::V1::Value::Get(Blob^% value) {
	visionhub::v1::blob nativeValue;
	auto retValue = this->value->get()->get(nativeValue);
	if (retValue) {
		auto managedValue = gcnew VisionHub::V1::Blob(std::make_shared<visionhub::v1::blob>(nativeValue));
		value = managedValue;
	}
	return retValue;
}


array<uint8_t>^ VisionHub::V1::Value::Serialize() {
	try {
		auto& buffer = this->value->get()->serialize();
		auto managedArray = gcnew array<uint8_t>((int)buffer.size());
		if (buffer.size() > 0) {
			
			pin_ptr<uint8_t> p = &managedArray[0];
			std::memcpy(p, buffer.data(), buffer.size() * sizeof(uint8_t));
		}
		return managedArray;
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}

VisionHub::V1::Value^ VisionHub::V1::Value::Deserialize(array<uint8_t>^ data) {
	try {


		if (data == nullptr || data->Length == 0) {
			throw gcnew System::Exception("Invalid buffer data");
		}


		std::vector<uint8_t> temp;
		temp.resize((std::size_t)data->Length);

		pin_ptr<uint8_t> p = &data[0];
		std::memcpy(temp.data(), p, sizeof(uint8_t) * data->Length);



		auto& nativeValue = visionhub::v1::value::deserialize(temp);
		auto managedValue = gcnew VisionHub::V1::Value(nativeValue);

		return managedValue;
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}
///////////////////////////////////////////////////////////////


void VisionHub::V1::Value::Set(const bool& value) {
	this->value->get()->set<bool>(value);
}
void VisionHub::V1::Value::Set(const int8_t& value) {
	this->value->get()->set<int8_t>(value);
}
void VisionHub::V1::Value::Set(const int16_t& value) {
	this->value->get()->set<int16_t>(value);
}
void VisionHub::V1::Value::Set(const int32_t& value) {
	this->value->get()->set<int32_t>(value);
}
void VisionHub::V1::Value::Set(const int64_t& value) {
	this->value->get()->set<int64_t>(value);
}
void VisionHub::V1::Value::Set(const uint8_t& value) {
	this->value->get()->set<uint8_t>(value);
}
void VisionHub::V1::Value::Set(const uint16_t& value) {
	this->value->get()->set<uint16_t>(value);
}
void VisionHub::V1::Value::Set(const uint32_t& value) {
	this->value->get()->set<uint32_t>(value);
}

void VisionHub::V1::Value::Set(const uint64_t& value) {
	this->value->get()->set<uint64_t>(value);
}

void VisionHub::V1::Value::Set(const float& value) {
	this->value->get()->set(value);
}
void VisionHub::V1::Value::Set(const double& value) {
	this->value->get()->set(value);
}
void VisionHub::V1::Value::Set(System::String^ value) {
	auto nativeValue = msclr::interop::marshal_as<std::string>(value);
	this->value->get()->set(nativeValue);
}
void VisionHub::V1::Value::Set(Map^ value) {

	std::unordered_map<std::string, visionhub::v1::value> nativeMap;

	for each (auto & keypair in value) {
		auto & nativeKey = msclr::interop::marshal_as<std::string>(keypair.Key);
		auto nativePointer = *((visionhub::v1::value_ptr *)keypair.Value->Handle.ToPointer());
		nativeMap[nativeKey] = *nativePointer;
	}

	this->value->get()->set(nativeMap);

}
void VisionHub::V1::Value::Set(Array^ value) {
	std::vector<visionhub::v1::value> _temp;

	for (int index = 0; index < value->Count; index++) {
		auto managedValue = value[index];
		auto nativePointer = *((visionhub::v1::value_ptr*)managedValue->Handle.ToPointer());
		_temp.push_back(*nativePointer);
	}

	this->value->get()->set(_temp);
}

void VisionHub::V1::Value::Set(Blob^ value) {
	auto nativePointer = *((visionhub::v1::blob_ptr*)value->Handle.ToPointer());
	this->value->get()->set(*nativePointer);
}
#pragma endregion


