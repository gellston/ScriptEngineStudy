
#include "core/snapShot/snapValue.h"
#include "core/collection/memoryBlock.h"

#include <iostream>


#pragma region IMPL
namespace visionhub {
	namespace v1 {
		struct impl_snapValue {
		public:

			visionhub::v1::snapKind kind = visionhub::v1::snapKind::_null_;
			std::string type;
			bool boolValue = false;

			int8_t int8 = 0;
			int16_t int16 = 0;
			int32_t int32 = 0;
			int64_t int64 = 0;
			uint8_t uint8 = 0;
			uint16_t uint16 = 0;
			uint32_t uint32 = 0;
			uint64_t uint64 = 0;

			


			double double64 = 0.0;
			float float32 = 0.0f;

			std::string stringValue;


			std::vector<snapValue_ptr> elements;
			std::vector<std::pair<std::string, snapValue_ptr>> fields;
			
			memoryBlock memoryBlock;
		};
	}
}
#pragma endregion


#pragma region Consturctor
visionhub::v1::snapValue::snapValue() : impl(new impl_snapValue()) {

}
#pragma endregion

#pragma region Public Functions
visionhub::v1::snapValue_ptr visionhub::v1::snapValue::clone() {
	auto temp = std::make_shared<snapValue>();
	temp->impl->kind = this->impl->kind;
	temp->impl->type = this->impl->type;
	temp->impl->boolValue = this->impl->boolValue;
	temp->impl->int8 = this->impl->int8;
	temp->impl->int16 = this->impl->int16;
	temp->impl->int32 = this->impl->int32;
	temp->impl->int64 = this->impl->int64;

	temp->impl->uint8 = this->impl->uint8;
	temp->impl->uint16 = this->impl->uint16;
	temp->impl->uint32 = this->impl->uint32;
	temp->impl->uint64 = this->impl->uint64;

	temp->impl->double64 = this->impl->double64;
	temp->impl->float32 = this->impl->float32;


	temp->impl->stringValue = this->impl->stringValue;
	temp->impl->elements = this->impl->elements;
	temp->impl->fields = this->impl->fields;
	temp->impl->memoryBlock = this->impl->memoryBlock;
	return temp;
}

visionhub::v1::snapKind visionhub::v1::snapValue::kind() {
	return this->impl->kind;
}

std::string visionhub::v1::snapValue::type() {
	return this->impl->type;
}

int8_t visionhub::v1::snapValue::int8() {
	return this->impl->int8;
}

int16_t visionhub::v1::snapValue::int16() {
	return this->impl->int16;
}

int32_t visionhub::v1::snapValue::int32() {
	return this->impl->int32;
}

int64_t visionhub::v1::snapValue::int64() {
	return this->impl->int64;
}



uint8_t visionhub::v1::snapValue::uint8() {
	return this->impl->uint8;
}

uint16_t visionhub::v1::snapValue::uint16() {
	return this->impl->uint16;
}

uint32_t visionhub::v1::snapValue::uint32() {
	return this->impl->uint32;
}

uint64_t visionhub::v1::snapValue::uint64() {
	return this->impl->uint64;
}




float visionhub::v1::snapValue::float32() {
	return this->impl->float32;
}

double visionhub::v1::snapValue::double64() {
	return this->impl->double64;
}

bool visionhub::v1::snapValue::boolean() {
	return this->impl->boolValue;
}

std::string visionhub::v1::snapValue::string() {
	return this->impl->stringValue;
}

std::vector<visionhub::v1::snapValue_ptr> visionhub::v1::snapValue::elements() {
	return this->impl->elements;
}

std::vector<std::pair<std::string, visionhub::v1::snapValue_ptr>> visionhub::v1::snapValue::fields() {
	return this->impl->fields;
}

visionhub::v1::memoryBlock visionhub::v1::snapValue::memoryBlock() {
	return this->impl->memoryBlock;
}

void visionhub::v1::snapValue::print(int intent) {
	std::cout << std::string(intent, '\t') << "{" << std::endl;
	std::cout << std::string(intent + 1, '\t') << "kind:" << std::to_string((int)this->impl->kind) << std::endl;
	std::cout << std::string(intent + 1, '\t') << "type:" << this->impl->type << std::endl;
	
	switch (this->impl->kind)
	{
	case visionhub::v1::snapKind::_bool_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << this->impl->boolValue << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_int8_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << this->impl->int8 << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_int16_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << this->impl->int16 << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_int32_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << this->impl->int32 << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_int64_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << this->impl->int64 << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_uint8_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << this->impl->uint8 << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_uint16_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << this->impl->uint16 << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_uint32_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << this->impl->uint32 << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_uint64_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << this->impl->uint64 << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_string_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << this->impl->stringValue << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_float_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << this->impl->float32 << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_double_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << this->impl->double64 << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_native_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << std::endl;
		std::cout << std::string(intent + 1, '\t') << "{" << std::endl;
		for (auto element : this->impl->fields) {
			element.second->print(intent + 1);
		}
		std::cout << std::string(intent + 1, '\t') << "}" << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_map_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << std::endl;
		std::cout << std::string(intent + 1, '\t') << "{" << std::endl;
		for (auto element : this->impl->fields) {
			element.second->print(intent + 1);
		}
		std::cout << std::string(intent + 1, '\t') << "}" << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_memory_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << "[memory]" << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_array_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << std::endl;
		std::cout << std::string(intent + 1, '\t') << "{" << std::endl;
		for (auto element : this->impl->elements) {
			element->print(intent + 1);
		}
		std::cout << std::string(intent + 1, '\t') << "}" << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_null_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << "null" << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_script_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << std::endl;
		std::cout << std::string(intent + 1, '\t') << "{" << std::endl;
		for (auto element : this->impl->fields) {
			element.second->print(intent + 1);
		}
		std::cout << std::string(intent + 1, '\t') << "}" << std::endl;
		break;
	}
	case visionhub::v1::snapKind::_unidentified_: {
		std::cout << std::string(intent + 1, '\t') << "value:" << "unidentified" << std::endl;
		break;
	}
	}


	std::cout << std::string(intent, '\t') << "}" << std::endl;
}

#pragma endregion








#pragma region SnapValueAtt
void visionhub::v1::snapValueAtt::setKind(const snapValue_ptr& value, const snapKind& kind) {
	value->impl->kind = kind;
}

void visionhub::v1::snapValueAtt::setType(const snapValue_ptr& value, const std::string& s) {
	value->impl->type = s;
}

void visionhub::v1::snapValueAtt::setValue(const snapValue_ptr& value, const int8_t& x) {
	value->impl->kind = visionhub::v1::snapKind::_int8_;
	value->impl->type = "int8";
	value->impl->int8 = x;
}
void visionhub::v1::snapValueAtt::setValue(const snapValue_ptr& value, const int16_t& x) {
	value->impl->kind = visionhub::v1::snapKind::_int16_;
	value->impl->type = "int16";
	value->impl->int16 = x;
}
void visionhub::v1::snapValueAtt::setValue(const snapValue_ptr& value, const int32_t& x) {
	value->impl->kind = visionhub::v1::snapKind::_int32_;
	value->impl->type = "int32";
	value->impl->int32 = x;
}
void visionhub::v1::snapValueAtt::setValue(const snapValue_ptr& value, const int64_t& x) {
	value->impl->kind = visionhub::v1::snapKind::_int64_;
	value->impl->type = "int64";
	value->impl->int64 = x;
}



void visionhub::v1::snapValueAtt::setValue(const snapValue_ptr& value, const uint8_t& x) {
	value->impl->kind = visionhub::v1::snapKind::_uint8_;
	value->impl->type = "uint8";
	value->impl->uint8 = x;
}
void visionhub::v1::snapValueAtt::setValue(const snapValue_ptr& value, const uint16_t& x) {
	value->impl->kind = visionhub::v1::snapKind::_uint16_;
	value->impl->type = "uint16";
	value->impl->uint16 = x;
}
void visionhub::v1::snapValueAtt::setValue(const snapValue_ptr& value, const uint32_t& x) {
	value->impl->kind = visionhub::v1::snapKind::_uint32_;
	value->impl->type = "uint32";
	value->impl->uint32 = x;
}
void visionhub::v1::snapValueAtt::setValue(const snapValue_ptr& value, const uint64_t& x) {
	value->impl->kind = visionhub::v1::snapKind::_uint64_;
	value->impl->type = "uint64";
	value->impl->uint64 = x;
}


void visionhub::v1::snapValueAtt::setValue(const snapValue_ptr& value, const  std::string& x) {
	value->impl->kind = visionhub::v1::snapKind::_string_;
	value->impl->type = "string";
	value->impl->stringValue = x;
}

void visionhub::v1::snapValueAtt::setValue(const snapValue_ptr& value, const  bool& x) {
	value->impl->kind = visionhub::v1::snapKind::_bool_;
	value->impl->type = "bool";
	value->impl->boolValue = x;
}

void visionhub::v1::snapValueAtt::setValue(const snapValue_ptr& value, const  memoryBlock& block) {
	value->impl->kind = visionhub::v1::snapKind::_memory_;
	value->impl->type = "memoryBlock";
	value->impl->memoryBlock = block;
}

void visionhub::v1::snapValueAtt::setValue(const snapValue_ptr& value, const  float& x) {
	value->impl->kind = visionhub::v1::snapKind::_float_;
	value->impl->type = "float";
	value->impl->float32 = x;
}

void visionhub::v1::snapValueAtt::setValue(const snapValue_ptr& value, const  double& x) {
	value->impl->kind = visionhub::v1::snapKind::_double_;
	value->impl->type = "double";
	value->impl->double64 = x;
}



void visionhub::v1::snapValueAtt::addField(const snapValue_ptr& value, const std::string & field, const  double& _value) {
	auto _value_ = std::make_shared<visionhub::v1::snapValue>();
	visionhub::v1::snapValueAtt::setValue(_value_, _value);
	value->impl->fields.push_back({ field, _value_ });
}


void visionhub::v1::snapValueAtt::addField(const snapValue_ptr& value, const std::string& field, const  int8_t& _value) {
	auto _value_ = std::make_shared<visionhub::v1::snapValue>();
	visionhub::v1::snapValueAtt::setValue(_value_, _value);
	value->impl->fields.push_back({ field, _value_ });
}

void visionhub::v1::snapValueAtt::addField(const snapValue_ptr& value, const std::string& field, const int16_t& _value) {
	auto _value_ = std::make_shared<visionhub::v1::snapValue>();
	visionhub::v1::snapValueAtt::setValue(_value_, _value);
	value->impl->fields.push_back({ field, _value_ });
}

void visionhub::v1::snapValueAtt::addField(const snapValue_ptr& value, const std::string& field, const  int32_t& _value) {
	auto _value_ = std::make_shared<visionhub::v1::snapValue>();
	visionhub::v1::snapValueAtt::setValue(_value_, _value);
	value->impl->fields.push_back({ field, _value_ });
}

void visionhub::v1::snapValueAtt::addField(const snapValue_ptr& value, const std::string& field, const  int64_t& _value) {
	auto _value_ = std::make_shared<visionhub::v1::snapValue>();
	visionhub::v1::snapValueAtt::setValue(_value_, _value);
	value->impl->fields.push_back({ field, _value_ });
}

void visionhub::v1::snapValueAtt::addField(const snapValue_ptr& value, const std::string& field, const  uint8_t& _value) {
	auto _value_ = std::make_shared<visionhub::v1::snapValue>();
	visionhub::v1::snapValueAtt::setValue(_value_, _value);
	value->impl->fields.push_back({ field, _value_ });
}

void visionhub::v1::snapValueAtt::addField(const snapValue_ptr& value, const std::string& field, const uint16_t& _value) {
	auto _value_ = std::make_shared<visionhub::v1::snapValue>();
	visionhub::v1::snapValueAtt::setValue(_value_, _value);
	value->impl->fields.push_back({ field, _value_ });
}

void visionhub::v1::snapValueAtt::addField(const snapValue_ptr& value, const std::string& field, const  uint32_t& _value) {
	auto _value_ = std::make_shared<visionhub::v1::snapValue>();
	visionhub::v1::snapValueAtt::setValue(_value_, _value);
	value->impl->fields.push_back({ field, _value_ });
}

void visionhub::v1::snapValueAtt::addField(const snapValue_ptr& value, const std::string& field, const  uint64_t& _value) {
	auto _value_ = std::make_shared<visionhub::v1::snapValue>();
	visionhub::v1::snapValueAtt::setValue(_value_, _value);
	value->impl->fields.push_back({ field, _value_ });
}


void visionhub::v1::snapValueAtt::addField(const snapValue_ptr& value, const std::string& field, const  float& _value) {
	auto _value_ = std::make_shared<visionhub::v1::snapValue>();
	visionhub::v1::snapValueAtt::setValue(_value_, _value);
	value->impl->fields.push_back({ field, _value_ });
}

void visionhub::v1::snapValueAtt::addField(const snapValue_ptr& value, const std::string& field, const  bool& _value) {
	auto _value_ = std::make_shared<visionhub::v1::snapValue>();
	visionhub::v1::snapValueAtt::setValue(_value_, _value);
	value->impl->fields.push_back({ field, _value_ });
}


void visionhub::v1::snapValueAtt::addField(const snapValue_ptr& value, const std::string& field, const  memoryBlock& block) {
	auto _value_ = std::make_shared<visionhub::v1::snapValue>();
	visionhub::v1::snapValueAtt::setValue(_value_, block);
	value->impl->fields.push_back({ field, _value_ });
}

void visionhub::v1::snapValueAtt::addField(const snapValue_ptr& value, const std::string& field, const  std::string& _value) {
	auto _value_ = std::make_shared<visionhub::v1::snapValue>();
	visionhub::v1::snapValueAtt::setValue(_value_, _value);
	value->impl->fields.push_back({ field, _value_ });
}


void visionhub::v1::snapValueAtt::addField(const snapValue_ptr& value, const std::string& field, const  snapValue_ptr& object) {

	value->impl->fields.push_back({ field, object });
}





void visionhub::v1::snapValueAtt::addElement(const snapValue_ptr& value, const snapValue_ptr& object) {
	value->impl->elements.push_back(object);
}





#pragma endregion

