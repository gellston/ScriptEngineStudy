#pragma once


#ifndef VISIONHUB_AOI_NATIVE_ENGINE_ADAPTER_VALUE
#define VISIONHUB_AOI_NATIVE_ENGINE_ADAPTER_VALUE


#include <core/binding/helper.h>
#include <core/collection/value.h>
#include <core/collection/raii.h>
#include <core/collection/raii2.h>

namespace visionhub {
	namespace v1 {
		struct var {

		public:
#pragma region Public Property
			sharedValue _value;
#pragma endregion

#pragma region Public Constructor
			explicit var(std::shared_ptr<visionhub::v1::value> v) : _value(std::move(v)) {}
#pragma endregion

			//REFERENCE_COUNTER()

#pragma region Script Constructor
			static var* varNull() {return new var(std::make_shared<visionhub::v1::value>());}
			static var* varBool(bool v) { return new var(std::make_shared<visionhub::v1::value>(v)); }
			static var* varInt8(int8_t v) { return new var(std::make_shared<visionhub::v1::value>(v)); }
			static var* varInt16(int16_t v) { return new var(std::make_shared<visionhub::v1::value>(v)); }
			static var* varInt32(int32_t v) { 
				return new var(std::make_shared<visionhub::v1::value>(v)); 
			}
			static var* varInt64(int64_t v) { return new var(std::make_shared<visionhub::v1::value>(v)); }

			static var* varUInt8(uint8_t v) { return new var(std::make_shared<visionhub::v1::value>(v)); }
			static var* varUInt16(uint16_t v) { return new var(std::make_shared<visionhub::v1::value>(v)); }
			static var* varUInt32(uint32_t v) { return new var(std::make_shared<visionhub::v1::value>(v)); }
			static var* varUInt64(uint64_t v) { return new var(std::make_shared<visionhub::v1::value>(v)); }

			static var* varFloat(float v) { return new var(std::make_shared<visionhub::v1::value>(v)); }
			static var* varDouble(double v) { return new var(std::make_shared<visionhub::v1::value>(v)); }
			static var* varString(const std::string& s) { return new var(std::make_shared<visionhub::v1::value>(s)); }
#pragma endregion

#pragma region Public Functions
			visionhub::v1::valueKind kind() {
				return this->_value->kind();
			}

			std::size_t size() {
				return this->_value->size();
			}


			//getter
			bool get(bool& value) {
				return this->_value->get(value);
			}

			bool get(int8_t& value) {
				return this->_value->get(value);
			}

			bool get(int16_t& value) {
				return this->_value->get(value);
			}
			bool get(int32_t& value) {
				return this->_value->get(value);
			}

			bool get(int64_t& value) {
				return this->_value->get(value);
			}

			bool get(uint8_t& value) {
				return this->_value->get(value);
			}

			bool get(uint16_t& value) {
				return this->_value->get(value);
			}

			bool get(uint32_t& value) {
				return this->_value->get(value);
			}

			bool get(uint64_t& value) {
				return this->_value->get(value);
			}


			bool get(std::string& value) {
				return this->_value->get(value);
			}

			bool get(float& value) {
				return this->_value->get(value);
			}

			bool get(double& value) {
				return this->_value->get(value);
			}

			visionhub::v1::var* opIndex(int index) {
				try {

					auto variable = (*this->_value)[index];
					auto sharedVariable = std::make_shared<visionhub::v1::value>(std::move(variable));
					return new visionhub::v1::var(sharedVariable);
				}
				catch (...) {
					throw;
				}
			}

			visionhub::v1::var* opIndex(const std::string& key) {
				try {

					auto variable = (*this->_value)[key];
					auto sharedVariable = std::make_shared<visionhub::v1::value>(std::move(variable));
					return new visionhub::v1::var(sharedVariable);
				}
				catch (...) {
					throw;
				}
			}

			void add(visionhub::v1::var* val) {
				try {
					//visionhub::v1::raii reset([&] {
					//	if (val) val->Release();
					//});
					auto& variable = val->_value;
					this->_value->add(*variable);

					
				}
				catch (...) {
					throw;
				}
			}


			void set(const std::string& key, visionhub::v1::var* var) {
				try {

					/*visionhub::v1::raii reset([&] {
						if (var) var->Release();
					});*/
					auto& variable = var->_value;
					this->_value->set(key, *variable);
				}
				catch (...) {
					throw;
				}
			}

			//setter
			void set(bool& value) {
				this->_value->set(value);
			}

			void set(int8_t& value) {
				this->_value->set(value);
			}

			void set(int16_t& value) {
				this->_value->set(value);
			}
			void set(int32_t& value) {
				this->_value->set(value);
			}

			void set(int64_t& value) {
				this->_value->set(value);
			}

			void set(uint8_t& value) {
				this->_value->set(value);
			}

			void set(uint16_t& value) {
				this->_value->set(value);
			}

			void set(uint32_t& value) {
				this->_value->set(value);
			}

			void set(uint64_t& value) {
				this->_value->set(value);
			}


			void set(std::string& value) {
				this->_value->set(value);
			}

			void set(float& value) {
				this->_value->set(value);
			}

			void set(double& value) {
				this->_value->set(value);
			}
#pragma endregion




		};
	}
}



#endif