

#include "engine/facade/facadeEngine.h"

#include <core/collection/memoryPool.h>
#include <core/collection/blob.h>

#include <core/image.h>

#include <core/reflection/typeRegistry.h>

#pragma region MACRO


#define VECTOR_CONVERSION(type)\
if (std::holds_alternative<std::vector<type>>(value)) {\
	auto & _vector = std::get<std::vector<type>>(value);\
	visionhub::v1::value _temp;\
	for (auto element : _vector) {\
		_temp.add(visionhub::v1::value(element));\
	}\
	objectValue.set(keyname, _temp);\
	continue;\
}\


#define MAP_CONVERSION(type)\
if (std::holds_alternative<std::unordered_map<std::string, type>>(value)) {\
	visionhub::v1::value tempValue;\
	auto map = std::get<std::unordered_map<std::string, type>>(value);\
	for (auto& element : map) {\
		tempValue.set(element.first, element.second);\
	}\
	objectValue.set(keyname, tempValue);\
	continue;\
}\


#pragma endregion



#pragma region Constructor

visionhub::v1::facadeEngine::facadeEngine() : pool(new visionhub::v1::memoryPool()) {

	this->_argument = std::make_shared<visionhub::v1::value>();
	this->_output = std::make_shared<visionhub::v1::value>();
}

#pragma endregion


#pragma region Public Functions

void visionhub::v1::facadeEngine::cout(const std::string& text) {

	std::cout << text << std::endl;
}

visionhub::v1::image_ptr visionhub::v1::facadeEngine::make_image(unsigned int width, unsigned int height, unsigned int channel, visionhub::v1::depthType depth) {
	try {

		auto size = width * height * channel * static_cast<int>(depth);
		return std::make_shared<visionhub::v1::image>(width, height, channel, depth, this->globalPool());
	}
	catch (...) {
		throw;
	}
}

std::shared_ptr<visionhub::v1::memoryPool> visionhub::v1::facadeEngine::globalPool() {
	return this->pool;
}

void visionhub::v1::facadeEngine::argument(const visionhub::v1::sharedValue & value) {
	this->_argument = value;
}

visionhub::v1::sharedValue visionhub::v1::facadeEngine::output() {
	return this->_output;
}

void visionhub::v1::facadeEngine::resetOutput() {
	this->_output = std::make_shared<visionhub::v1::value>();
}

visionhub::v1::value visionhub::v1::facadeEngine::argument() {
	return *this->_argument;
}
void visionhub::v1::facadeEngine::output(const visionhub::v1::value& value) {
	*(this->_output) = value;
}





void visionhub::v1::facadeEngine::output(const std::string& text, const object_ptr& _object) {
	if (_object == nullptr) return;

	std::function<visionhub::v1::value(object_ptr)> conversion = [&](object_ptr __object) -> visionhub::v1::value {
		
		auto objectType = _object->objType();

		auto information = visionhub::v1::typeRegistry::get().find(objectType);
		if (information == nullptr) return nullptr;

		auto props = information->props;
		auto output = this->_output;

		visionhub::v1::value objectValue;

		for (auto prop : props) {
			auto& keyname = prop.name;
			auto& method = prop.reader;

			try {
				auto value = method(__object.get());

				if (std::holds_alternative<std::monostate>(value)) { objectValue.set(keyname, nullptr); continue; }
				if (std::holds_alternative<int8_t>(value)) { objectValue.set(keyname, std::get<int8_t>(value)); continue;}
				if (std::holds_alternative<int16_t>(value)) { objectValue.set(keyname, std::get<int16_t>(value)); continue;}
				if (std::holds_alternative<int32_t>(value)) { objectValue.set(keyname, std::get<int32_t>(value)); continue;}
				if (std::holds_alternative<int64_t>(value)) { objectValue.set(keyname, std::get<int64_t>(value)); continue;}

				if (std::holds_alternative<uint8_t>(value)) { objectValue.set(keyname, std::get<uint8_t>(value));  continue;}
				if (std::holds_alternative<uint16_t>(value)) { objectValue.set(keyname, std::get<uint16_t>(value)); continue;}
				if (std::holds_alternative<uint32_t>(value)) { objectValue.set(keyname, std::get<uint32_t>(value)); continue;}
				if (std::holds_alternative<uint64_t>(value)) { objectValue.set(keyname, std::get<uint64_t>(value)); continue;}

				if (std::holds_alternative<float>(value)) { objectValue.set(keyname, std::get<float>(value)); continue;}
				if (std::holds_alternative<double>(value)) { objectValue.set(keyname, std::get<double>(value)); continue;}
				if (std::holds_alternative<std::string>(value)) { objectValue.set(keyname, std::get<std::string>(value)); continue;}
				if (std::holds_alternative<visionhub::v1::memoryBlock>(value)) {
					auto memoryBlock = std::get<visionhub::v1::memoryBlock>(value);
					objectValue.set(keyname, visionhub::v1::blob(memoryBlock));
					continue;
				}

				if (std::holds_alternative<std::shared_ptr<object>>(value)) {
					auto tempValue = conversion(__object);
					objectValue.set(keyname, tempValue);
					continue;
				}

				VECTOR_CONVERSION(bool)
				VECTOR_CONVERSION(int8_t)
				VECTOR_CONVERSION(int16_t)
				VECTOR_CONVERSION(int32_t)
				VECTOR_CONVERSION(int64_t)
				VECTOR_CONVERSION(uint8_t)
				VECTOR_CONVERSION(uint16_t)
				VECTOR_CONVERSION(uint32_t)
				VECTOR_CONVERSION(uint64_t)
				VECTOR_CONVERSION(float)
				VECTOR_CONVERSION(double)
				VECTOR_CONVERSION(std::string)
				VECTOR_CONVERSION(visionhub::v1::memoryBlock)
				if (std::holds_alternative<std::vector<object_ptr>>(value)) {
					visionhub::v1::value tempValue;
					auto smartPointerVec = std::get<std::vector<object_ptr>>(value);
					for (auto& smartPointer : smartPointerVec) {
						auto _tempValue = conversion(smartPointer);
						tempValue.add(_tempValue);
					}
					objectValue.set(keyname, tempValue);
					continue;
				}


				MAP_CONVERSION(bool)
				MAP_CONVERSION(int8_t)
				MAP_CONVERSION(int16_t)
				MAP_CONVERSION(int32_t)
				MAP_CONVERSION(int64_t)
				MAP_CONVERSION(uint8_t)
				MAP_CONVERSION(uint16_t)
				MAP_CONVERSION(uint32_t)
				MAP_CONVERSION(uint64_t)
				MAP_CONVERSION(float)
				MAP_CONVERSION(double)
				MAP_CONVERSION(std::string)
				if (std::holds_alternative<std::unordered_map<std::string, object_ptr>>(value)) {
						visionhub::v1::value tempValue; 
						auto map = std::get<std::unordered_map<std::string, object_ptr>>(value);
						for (auto& element : map) {
							auto _tempValue = conversion(element.second);
							tempValue.set(element.first, _tempValue);
						}
						objectValue.set(keyname, tempValue); 
						continue; 
				}
		
			}
			catch (...) {

			}
		}

		return objectValue;
	};


	auto returnValue = conversion(_object);
	this->_output->set(text, returnValue);

}
#pragma endregion
