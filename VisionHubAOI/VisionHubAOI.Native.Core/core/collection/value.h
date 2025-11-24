#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_VALUE
#define VISIONHUB_AOI_NATIVE_CORE_VALUE

#include "../coreMacro/api.h"
#include "valueKind.h"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace visionhub {
	namespace v1 {
		struct value;
		struct impl_value;
		struct blob;

		using sharedValue = std::shared_ptr<value>;
		using array = std::vector<value>;
		using map = std::unordered_map<std::string, value>;
		

		struct value {
#pragma region Private Property
		private:
			std::shared_ptr<impl_value> impl;
#pragma endregion

#pragma region Constructor
		public:
			VISIONHUB_AOI_NATIVE_CORE_API value();
			VISIONHUB_AOI_NATIVE_CORE_API value(std::monostate);
			VISIONHUB_AOI_NATIVE_CORE_API value(std::nullptr_t);
			VISIONHUB_AOI_NATIVE_CORE_API value(const bool&);
			VISIONHUB_AOI_NATIVE_CORE_API value(const int8_t&);
			VISIONHUB_AOI_NATIVE_CORE_API value(const int16_t&);
			VISIONHUB_AOI_NATIVE_CORE_API value(const int32_t&);
			VISIONHUB_AOI_NATIVE_CORE_API value(const int64_t&);
			VISIONHUB_AOI_NATIVE_CORE_API value(const uint8_t&);
			VISIONHUB_AOI_NATIVE_CORE_API value(const uint16_t&);
			VISIONHUB_AOI_NATIVE_CORE_API value(const uint32_t&);
			VISIONHUB_AOI_NATIVE_CORE_API value(const uint64_t&);
			VISIONHUB_AOI_NATIVE_CORE_API value(const float&);
			VISIONHUB_AOI_NATIVE_CORE_API value(const double&);
			VISIONHUB_AOI_NATIVE_CORE_API value(const char * s);
			VISIONHUB_AOI_NATIVE_CORE_API value(const std::string& s);
			VISIONHUB_AOI_NATIVE_CORE_API value(const map&);
			VISIONHUB_AOI_NATIVE_CORE_API value(const array&);
			VISIONHUB_AOI_NATIVE_CORE_API value(const blob&);
			VISIONHUB_AOI_NATIVE_CORE_API value(const value&);
#pragma endregion

#pragma region Public Functions
			template<typename T> bool get(T& value) {
				if (std::is_enum<T>()) {
					return this->get<int32_t>();
				}
				return false;
			}

			template<typename T> void set(const T& value) {
				if (std::is_enum<T>()) {
					this->set<int32_t>(value);
				}
				throw std::exception("Invalid data type");
			}

			VISIONHUB_AOI_NATIVE_CORE_API visionhub::v1::value operator [](const std::string &);
			VISIONHUB_AOI_NATIVE_CORE_API visionhub::v1::value operator [](const int&);

			VISIONHUB_AOI_NATIVE_CORE_API void add(const visionhub::v1::value& value);
			VISIONHUB_AOI_NATIVE_CORE_API void set(const std::string & key, const visionhub::v1::value & value);

			VISIONHUB_AOI_NATIVE_CORE_API visionhub::v1::valueKind kind();
			VISIONHUB_AOI_NATIVE_CORE_API std::size_t size();
			VISIONHUB_AOI_NATIVE_CORE_API std::size_t count();
			VISIONHUB_AOI_NATIVE_CORE_API std::vector<uint8_t> serialize();
			VISIONHUB_AOI_NATIVE_CORE_API static visionhub::v1::value deserialize(const std::vector<uint8_t>& data, std::size_t offset = 0);
#pragma endregion
		};

	}
}

template<> VISIONHUB_AOI_NATIVE_CORE_API bool visionhub::v1::value::get<bool>(bool&);
template<> VISIONHUB_AOI_NATIVE_CORE_API bool visionhub::v1::value::get<int8_t>(int8_t&);
template<> VISIONHUB_AOI_NATIVE_CORE_API bool visionhub::v1::value::get<int16_t>(int16_t&);
template<> VISIONHUB_AOI_NATIVE_CORE_API bool visionhub::v1::value::get<int32_t>(int32_t&);
template<> VISIONHUB_AOI_NATIVE_CORE_API bool visionhub::v1::value::get<int64_t>(int64_t&);
template<> VISIONHUB_AOI_NATIVE_CORE_API bool visionhub::v1::value::get<uint8_t>(uint8_t&);
template<> VISIONHUB_AOI_NATIVE_CORE_API bool visionhub::v1::value::get<uint16_t>(uint16_t&);
template<> VISIONHUB_AOI_NATIVE_CORE_API bool visionhub::v1::value::get<uint32_t>(uint32_t&);
template<> VISIONHUB_AOI_NATIVE_CORE_API bool visionhub::v1::value::get<uint64_t>(uint64_t&);
template<> VISIONHUB_AOI_NATIVE_CORE_API bool visionhub::v1::value::get<float>(float&);
template<> VISIONHUB_AOI_NATIVE_CORE_API bool visionhub::v1::value::get<double>(double&);
template<> VISIONHUB_AOI_NATIVE_CORE_API bool visionhub::v1::value::get<std::string>(std::string&);
template<> VISIONHUB_AOI_NATIVE_CORE_API bool visionhub::v1::value::get<visionhub::v1::map>(visionhub::v1::map&);
template<> VISIONHUB_AOI_NATIVE_CORE_API bool visionhub::v1::value::get<visionhub::v1::array>(visionhub::v1::array&);
template<> VISIONHUB_AOI_NATIVE_CORE_API bool visionhub::v1::value::get<visionhub::v1::blob>(visionhub::v1::blob&);


template<> VISIONHUB_AOI_NATIVE_CORE_API void visionhub::v1::value::set<bool>(const bool&);
template<> VISIONHUB_AOI_NATIVE_CORE_API void visionhub::v1::value::set<int8_t>(const int8_t&);
template<> VISIONHUB_AOI_NATIVE_CORE_API void visionhub::v1::value::set<int16_t>(const int16_t&);
template<> VISIONHUB_AOI_NATIVE_CORE_API void visionhub::v1::value::set<int32_t>(const int32_t&);
template<> VISIONHUB_AOI_NATIVE_CORE_API void visionhub::v1::value::set<int64_t>(const int64_t&);
template<> VISIONHUB_AOI_NATIVE_CORE_API void visionhub::v1::value::set<uint8_t>(const uint8_t&);
template<> VISIONHUB_AOI_NATIVE_CORE_API void visionhub::v1::value::set<uint16_t>(const uint16_t&);
template<> VISIONHUB_AOI_NATIVE_CORE_API void visionhub::v1::value::set<uint32_t>(const uint32_t&);
template<> VISIONHUB_AOI_NATIVE_CORE_API void visionhub::v1::value::set<uint64_t>(const uint64_t&);
template<> VISIONHUB_AOI_NATIVE_CORE_API void visionhub::v1::value::set<float>(const float&);
template<> VISIONHUB_AOI_NATIVE_CORE_API void visionhub::v1::value::set<double>(const double&);
template<> VISIONHUB_AOI_NATIVE_CORE_API void visionhub::v1::value::set<std::string>(const std::string&);
template<> VISIONHUB_AOI_NATIVE_CORE_API void visionhub::v1::value::set<visionhub::v1::blob>(const visionhub::v1::blob&);

template<> VISIONHUB_AOI_NATIVE_CORE_API void visionhub::v1::value::set<visionhub::v1::map>(const visionhub::v1::map&);
template<> VISIONHUB_AOI_NATIVE_CORE_API void visionhub::v1::value::set<visionhub::v1::array>(const visionhub::v1::array&);

#endif
