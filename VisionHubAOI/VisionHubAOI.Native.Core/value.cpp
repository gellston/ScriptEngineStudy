
#include "core/collection/value.h"
#include "core/collection/blob.h"

#include <variant>

using variant_t = std::variant<
	std::monostate,
	bool,
	int8_t,
	int16_t,
	int32_t,
	int64_t,
	uint8_t,
	uint16_t,
	uint32_t,
	uint64_t,
	float,
	double,
	std::string,
	visionhub::v1::array,
	visionhub::v1::map,
	visionhub::v1::blob
>;


#pragma region IMPL
namespace visionhub {
	namespace v1 {
		struct impl_value {
		public:

			variant_t v;

		};
	}
}
#pragma endregion


#pragma region Constructor
visionhub::v1::value::value() : impl(new impl_value()) {
	this->impl->v = std::monostate{};
}

visionhub::v1::value::value(std::monostate state) : impl(new impl_value()) {
	this->impl->v = state;
}

visionhub::v1::value::value(std::nullptr_t) : impl(new impl_value()) {
	this->impl->v = std::monostate{};
}
visionhub::v1::value::value(const bool & data) : impl(new impl_value()) {
	this->impl->v = data;
}
visionhub::v1::value::value(const int8_t& data) : impl(new impl_value()) {
	this->impl->v = data;
}
visionhub::v1::value::value(const int16_t& data) : impl(new impl_value()) {
	this->impl->v = data;
}
visionhub::v1::value::value(const int32_t& data) : impl(new impl_value()) {
	this->impl->v = data;
}
visionhub::v1::value::value(const int64_t& data) : impl(new impl_value()) {
	this->impl->v = data;
}
visionhub::v1::value::value(const uint8_t& data) : impl(new impl_value()) {
	this->impl->v = data;
}
visionhub::v1::value::value(const uint16_t& data) : impl(new impl_value()) {
	this->impl->v = data;
}
visionhub::v1::value::value(const uint32_t& data) : impl(new impl_value()) {
	this->impl->v = data;
}
visionhub::v1::value::value(const uint64_t& data) : impl(new impl_value()) {
	this->impl->v = data;
}
visionhub::v1::value::value(const float& data) : impl(new impl_value()) {
	this->impl->v = data;
}
visionhub::v1::value::value(const double& data) : impl(new impl_value()) {
	this->impl->v = data;
}
visionhub::v1::value::value(const char* s) : impl(new impl_value()) {
	this->impl->v = std::string(s);
}
visionhub::v1::value::value(const std::string& s) : impl(new impl_value()) {
	this->impl->v = s;
}
visionhub::v1::value::value(const map& data) : impl(new impl_value()) {
	this->impl->v = data;
}
visionhub::v1::value::value(const array& data) : impl(new impl_value()) {
	this->impl->v = data;
}
visionhub::v1::value::value(const blob& data) : impl(new impl_value()) {
	this->impl->v = data;
}

visionhub::v1::value::value(const visionhub::v1::value& value) : impl(new impl_value()) {
	this->impl->v = value.impl->v;
}
#pragma endregion

#pragma region Public Functions


template<> bool visionhub::v1::value::get<bool>(bool& value) {
	if (!std::holds_alternative<bool>(this->impl->v)) return false;

	value = std::get<bool>(this->impl->v);

	return true;
}

template<> bool visionhub::v1::value::get<int8_t>(int8_t& value) {
	if (!std::holds_alternative<int8_t>(this->impl->v)) return false;

	value = std::get<int8_t>(this->impl->v);

	return true;
}
template<> bool visionhub::v1::value::get<int16_t>(int16_t& value) {
	if (!std::holds_alternative<int16_t>(this->impl->v)) return false;

	value = std::get<int16_t>(this->impl->v);

	return true;
}
template<> bool visionhub::v1::value::get<int32_t>(int32_t& value) {
	if (!std::holds_alternative<int32_t>(this->impl->v)) return false;

	value = std::get<int32_t>(this->impl->v);

	return true;
}
template<> bool visionhub::v1::value::get<int64_t>(int64_t& value) {
	if (!std::holds_alternative<int64_t>(this->impl->v)) return false;

	value = std::get<int64_t>(this->impl->v);

	return true;
}
template<> bool visionhub::v1::value::get<uint8_t>(uint8_t& value) {
	if (!std::holds_alternative<uint8_t>(this->impl->v)) return false;

	value = std::get<uint8_t>(this->impl->v);

	return true;
}
template<> bool visionhub::v1::value::get<uint16_t>(uint16_t& value) {
	if (!std::holds_alternative<uint16_t>(this->impl->v)) return false;

	value = std::get<uint16_t>(this->impl->v);

	return true;
}
template<> bool visionhub::v1::value::get<uint32_t>(uint32_t& value) {
	if (!std::holds_alternative<uint32_t>(this->impl->v)) return false;

	value = std::get<uint32_t>(this->impl->v);

	return true;
}
template<> bool visionhub::v1::value::get<uint64_t>(uint64_t& value) {
	if (!std::holds_alternative<uint64_t>(this->impl->v)) return false;

	value = std::get<uint64_t>(this->impl->v);

	return true;
}
template<> bool visionhub::v1::value::get<float>(float& value) {
	if (!std::holds_alternative<float>(this->impl->v)) return false;

	value = std::get<float>(this->impl->v);

	return true;
}
template<> bool visionhub::v1::value::get<double>(double& value) {
	if (!std::holds_alternative<double>(this->impl->v)) return false;

	value = std::get<double>(this->impl->v);

	return true;
}
template<> bool visionhub::v1::value::get<std::string>(std::string& value) {
	if (!std::holds_alternative<std::string>(this->impl->v)) return false;

	value = std::get<std::string>(this->impl->v);

	return true;
}
template<> bool visionhub::v1::value::get<visionhub::v1::map>(visionhub::v1::map& value) {
	if (!std::holds_alternative<visionhub::v1::map>(this->impl->v)) return false;

	value = std::get<visionhub::v1::map>(this->impl->v);

	return true;
}
template<> bool visionhub::v1::value::get<visionhub::v1::array>(visionhub::v1::array& value) {
	if (!std::holds_alternative<visionhub::v1::array>(this->impl->v)) return false;

	value = std::get<visionhub::v1::array>(this->impl->v);

	return true;
}
template<> bool visionhub::v1::value::get<visionhub::v1::blob>(visionhub::v1::blob& value) {
	if (!std::holds_alternative<visionhub::v1::blob>(this->impl->v)) return false;

	value = std::get<visionhub::v1::blob>(this->impl->v);

	return true;
}











template<> void visionhub::v1::value::set<bool>(const bool& value) {
	this->impl->v = value;
}
template<> void visionhub::v1::value::set<int8_t>(const int8_t& value) {
	this->impl->v = value;
}
template<> void visionhub::v1::value::set<int16_t>(const int16_t& value) {
	this->impl->v = value;
}
template<> void visionhub::v1::value::set<int32_t>(const int32_t& value) {
	this->impl->v = value;
}
template<> void visionhub::v1::value::set<int64_t>(const int64_t& value) {
	this->impl->v = value;
}
template<> void visionhub::v1::value::set<uint8_t>(const uint8_t& value) {
	this->impl->v = value;
}
template<> void visionhub::v1::value::set<uint16_t>(const uint16_t& value) {
	this->impl->v = value;
}
template<> void visionhub::v1::value::set<uint32_t>(const uint32_t& value) {
	this->impl->v = value;
}
template<> void visionhub::v1::value::set<uint64_t>(const uint64_t& value) {
	this->impl->v = value;
}
template<> void visionhub::v1::value::set<float>(const float& value) {
	this->impl->v = value;
}
template<> void visionhub::v1::value::set<double>(const double& value) {
	this->impl->v = value;
}
template<> void visionhub::v1::value::set<std::string>(const std::string& value) {
	this->impl->v = value;
}
template<> void visionhub::v1::value::set<visionhub::v1::map>(const visionhub::v1::map& value) {
	this->impl->v = value;
}
template<> void visionhub::v1::value::set<visionhub::v1::array>(const visionhub::v1::array& value) {
	this->impl->v = value;
}
template<> void visionhub::v1::value::set<visionhub::v1::blob>(const visionhub::v1::blob& value) {
	this->impl->v = value;
}






visionhub::v1::value visionhub::v1::value::operator [](const std::string & key) {
	if (!std::holds_alternative<visionhub::v1::map>(this->impl->v)) {
		throw std::exception("Invalid value type");
	}

	auto& map = std::get<visionhub::v1::map>(this->impl->v);
	if (map.find(key) == map.end()) {
		throw std::exception("Invalid map key");
	}
	auto& value = map[key];
	return value;
}

visionhub::v1::value visionhub::v1::value::operator [](const int & index) {
	if (!std::holds_alternative<visionhub::v1::array>(this->impl->v)) {
		throw std::exception("Invalid value type");
	}

	auto& _array = std::get<visionhub::v1::array>(this->impl->v);
	if (_array.size() <= index) {
		throw std::exception("Invalid array index");
	}

	return _array[index];
}


void visionhub::v1::value::add(const visionhub::v1::value& value) {
	if (!std::holds_alternative<visionhub::v1::array>(this->impl->v)) {
		visionhub::v1::array _array;
		this->impl->v = _array;
	}

	auto& _array = std::get<visionhub::v1::array>(this->impl->v);
	_array.push_back(value);
}


void visionhub::v1::value::set(const std::string& key, const visionhub::v1::value & value) {
	if (!std::holds_alternative<visionhub::v1::map>(this->impl->v)) {
		visionhub::v1::map _map;
		this->impl->v = _map;
	}

	auto& _map = std::get<visionhub::v1::map>(this->impl->v);
	_map.insert({ key, value });
}



visionhub::v1::valueKind visionhub::v1::value::kind() {
	if (std::holds_alternative<bool>(this->impl->v)) return visionhub::v1::valueKind::_bool_;
	if (std::holds_alternative<int8_t>(this->impl->v)) return visionhub::v1::valueKind::_int8_;
	if (std::holds_alternative<int16_t>(this->impl->v)) return visionhub::v1::valueKind::_int16_;
	if (std::holds_alternative<int32_t>(this->impl->v)) return visionhub::v1::valueKind::_int32_;
	if (std::holds_alternative<int64_t>(this->impl->v)) return visionhub::v1::valueKind::_int64_;
	if (std::holds_alternative<uint8_t>(this->impl->v)) return visionhub::v1::valueKind::_uint8_;
	if (std::holds_alternative<uint16_t>(this->impl->v)) return visionhub::v1::valueKind::_uint16_;
	if (std::holds_alternative<uint32_t>(this->impl->v)) return visionhub::v1::valueKind::_uint32_;
	if (std::holds_alternative<uint64_t>(this->impl->v)) return visionhub::v1::valueKind::_uint64_;
	if (std::holds_alternative<float>(this->impl->v)) return visionhub::v1::valueKind::_float_;
	if (std::holds_alternative<double>(this->impl->v)) return visionhub::v1::valueKind::_double_;
	if (std::holds_alternative<std::string>(this->impl->v)) return visionhub::v1::valueKind::_string_;
	if (std::holds_alternative<visionhub::v1::map>(this->impl->v)) return visionhub::v1::valueKind::_map_;
	if (std::holds_alternative<visionhub::v1::array>(this->impl->v)) return visionhub::v1::valueKind::_array_;
	if (std::holds_alternative<visionhub::v1::blob>(this->impl->v)) return visionhub::v1::valueKind::_blob_;

	return visionhub::v1::valueKind::_null_;
}

std::size_t visionhub::v1::value::count() {
	if (std::holds_alternative<visionhub::v1::map>(this->impl->v)) {

		auto& map = std::get<visionhub::v1::map>(this->impl->v);
		return map.size();
	}
	if (std::holds_alternative<visionhub::v1::array>(this->impl->v)) {
		auto& _array = std::get<visionhub::v1::array>(this->impl->v);
		return _array.size();
	}

	return 0;
}

std::size_t visionhub::v1::value::size() {
	
	std::size_t _size = 0;
	_size += sizeof(int8_t);


	// primitive type format (tpyeinfo, value size)
	auto type = this->kind();
	switch (type)
	{
	case visionhub::v1::valueKind::_bool_: {
		_size += sizeof(bool);
		return _size;
	}
	case visionhub::v1::valueKind::_int8_: {
		_size += sizeof(int8_t);
		return _size;
	}
	case visionhub::v1::valueKind::_int16_: {
		_size += sizeof(int16_t);
		return _size;
	}
	case visionhub::v1::valueKind::_int32_: {
		_size += sizeof(int32_t);
		return _size;
	}
	case visionhub::v1::valueKind::_int64_: {
		_size += sizeof(int64_t);
		return _size;
	}
	case visionhub::v1::valueKind::_uint8_: {
		_size += sizeof(uint8_t);
		return _size;
	}
	case visionhub::v1::valueKind::_uint16_: {
		_size += sizeof(uint16_t);
		return _size;
	}
	case visionhub::v1::valueKind::_uint32_: {
		_size += sizeof(uint32_t);
		return _size;
	}
	case visionhub::v1::valueKind::_uint64_: {
		_size += sizeof(uint64_t);
		return _size;
	}
	case visionhub::v1::valueKind::_float_: {
		_size += sizeof(float);
		return _size;
	}
	case visionhub::v1::valueKind::_double_: {
		_size += sizeof(double);
		return _size;
	}
	case visionhub::v1::valueKind::_null_: {
		return _size;
	}
	}


	// string, blob type (typeinfo, size, value)
	switch (type)
	{
	case visionhub::v1::valueKind::_string_: {

		auto& buffer = std::get<std::string>(this->impl->v);
		_size += sizeof(uint64_t);
		_size += buffer.size();

		return _size;
	}

	case visionhub::v1::valueKind::_blob_: {
		auto& blob = std::get<visionhub::v1::blob>(this->impl->v);
		_size += sizeof(uint64_t);
		_size += blob.size();
		return _size;
	}
	}


	// array type (typeinfo, element count, value)
	// map type (typeinfo, field count, (key, value pair))
	// key pair( string size, string value, value size)
	switch (type)
	{
	case visionhub::v1::valueKind::_array_: {

		auto& _array = std::get<visionhub::v1::array>(this->impl->v);
		_size += sizeof(uint64_t);
		for (auto& element : _array) {
			_size += element.size();
		}
		return _size;
	}

	case visionhub::v1::valueKind::_map_: {
		auto& map = std::get<visionhub::v1::map>(this->impl->v);
		_size += sizeof(uint64_t);
		for (auto& key_pair : map) {
			auto & key = key_pair.first;
			auto& value = key_pair.second;

			_size += sizeof(uint64_t);
			_size += key.size();
			_size += value.size();
		}
		return _size;
	}
	}

	return 0;

}




visionhub::v1::value visionhub::v1::value::deserialize(const std::vector<uint8_t>& buffer, std::size_t  offset) {
	try {



		auto data = buffer.data();

		data += offset;
		

		auto valueKind = static_cast<visionhub::v1::valueKind>(*data);

		data += 1;
		offset += 1;

		switch (valueKind)
		{
		case visionhub::v1::valueKind::_null_: {
			visionhub::v1::value _value;
			return _value;
		}
		case visionhub::v1::valueKind::_bool_: {
			visionhub::v1::value _value((*(bool*)data));
			return _value;
		}
		case visionhub::v1::valueKind::_int8_: {
			visionhub::v1::value _value((*(int8_t*)data));
			return _value;
		}
		case visionhub::v1::valueKind::_int16_: {
			visionhub::v1::value _value((*(int16_t*)data));
			return _value;
		}
		case visionhub::v1::valueKind::_int32_: {
			visionhub::v1::value _value((*(int32_t*)data));
			return _value;
		}
		case visionhub::v1::valueKind::_int64_: {
			visionhub::v1::value _value((*(int64_t*)data));
			return _value;
		}
		case visionhub::v1::valueKind::_uint8_: {
			visionhub::v1::value _value((*(uint8_t*)data));
			return _value;
		}
		case visionhub::v1::valueKind::_uint16_: {
			visionhub::v1::value _value((*(uint16_t*)data));
			return _value;
		}
		case visionhub::v1::valueKind::_uint32_: {
			visionhub::v1::value _value((*(uint32_t*)data));
			return _value;
		}
		case visionhub::v1::valueKind::_uint64_: {
			visionhub::v1::value _value((*(uint64_t*)data));
			return _value;
		}
		case visionhub::v1::valueKind::_float_: {
			visionhub::v1::value _value((*(float*)data));
			return _value;
		}
		case visionhub::v1::valueKind::_double_: {
			visionhub::v1::value _value((*(double*)data));
			return _value;
		}
		}


		switch (valueKind)
		{
		case visionhub::v1::valueKind::_string_: {
			auto size = *(uint64_t*)data;
			data += sizeof(uint64_t);
			offset += sizeof(uint64_t);

			auto dataPoint = (char *)data;
			std::string stringValue(dataPoint, size);
			visionhub::v1::value _value(stringValue);
			return _value;
		}
		case visionhub::v1::valueKind::_blob_: {
			auto size = *(uint64_t*)data;
			data += sizeof(uint64_t);
			offset += sizeof(uint64_t);

			auto dataPoint = (uint8_t*)&data;

			visionhub::v1::blob _blob(dataPoint, size);
			visionhub::v1::value _value(_blob);
			return _value;
		}
		}



		switch (valueKind)
		{
		case visionhub::v1::valueKind::_array_: {

			auto size = *(uint64_t*)data;
			data += sizeof(uint64_t);
			offset += sizeof(uint64_t);

			std::vector<visionhub::v1::value> _array;
			for (int index = 0; index < size; index++) {
				auto element = visionhub::v1::value::deserialize(buffer, offset);
				_array.push_back(element);

				auto element_size = element.size();
				data += element_size;
				offset += element_size;
			}
			
			visionhub::v1::value _value(_array);
			return _value;
		}
		case visionhub::v1::valueKind::_map_: {
			auto size = *(uint64_t*)data;
			data += sizeof(uint64_t);
			offset += sizeof(uint64_t);

			std::unordered_map<std::string, visionhub::v1::value> _map;
			for (int index = 0; index < size; index++) {

				auto keySize = *(uint64_t*)data;
				data += sizeof(uint64_t);
				offset += sizeof(uint64_t);

				std::string keyValue((char *)data, keySize);
				data += keySize;
				offset += keySize;

				auto element = visionhub::v1::value::deserialize(buffer, offset);
				_map.emplace(keyValue, element);

				auto element_size = element.size();
				data += element_size;
				offset += element_size;
			}

			visionhub::v1::value _value(_map);
			return _value;
		}

		}


		throw std::exception("deserialization failed");
	}
	catch (...) {
		throw;
	}
}



std::vector<uint8_t> visionhub::v1::value::serialize() {
	
	try {
		std::vector<uint8_t> buffer;

		auto size = this->size();
		buffer.resize(size);





		// primitive type format (tpyeinfo, value size)
		auto type = this->kind();
		buffer[0] = static_cast<int8_t>(type);

		switch (type)
		{
		case visionhub::v1::valueKind::_bool_: {
			auto start = (void *)&buffer[1];
			auto data = std::get<bool>(this->impl->v);
			std::memcpy(start, &data, sizeof(bool));
			return buffer;
		}
		case visionhub::v1::valueKind::_int8_: {
			auto start = (void*)&buffer[1];
			auto data = std::get<int8_t>(this->impl->v);
			std::memcpy(start, &data, sizeof(int8_t));
			return buffer;
		}
		case visionhub::v1::valueKind::_int16_: {
			auto start = (void*)&buffer[1];
			auto data = std::get<int16_t>(this->impl->v);
			std::memcpy(start, &data, sizeof(int16_t));
			return buffer;
		}
		case visionhub::v1::valueKind::_int32_: {
			auto start = (void*)&buffer[1];
			auto data = std::get<int32_t>(this->impl->v);
			std::memcpy(start, &data, sizeof(int32_t));
			return buffer;
		}
		case visionhub::v1::valueKind::_int64_: {
			auto start = (void*)&buffer[1];
			auto data = std::get<int64_t>(this->impl->v);
			std::memcpy(start, &data, sizeof(int64_t));
			return buffer;
		}
		case visionhub::v1::valueKind::_uint8_: {
			auto start = (void*)&buffer[1];
			auto data = std::get<uint8_t>(this->impl->v);
			std::memcpy(start, &data, sizeof(uint8_t));
			return buffer;
		}
		case visionhub::v1::valueKind::_uint16_: {
			auto start = (void*)&buffer[1];
			auto data = std::get<uint16_t>(this->impl->v);
			std::memcpy(start, &data, sizeof(uint16_t));
			return buffer;
		}
		case visionhub::v1::valueKind::_uint32_: {
			auto start = (void*)&buffer[1];
			auto data = std::get<uint32_t>(this->impl->v);
			std::memcpy(start, &data, sizeof(uint32_t));
			return buffer;
		}
		case visionhub::v1::valueKind::_uint64_: {
			auto start = (void*)&buffer[1];
			auto data = std::get<uint64_t>(this->impl->v);
			std::memcpy(start, &data, sizeof(uint64_t));
			return buffer;
		}
		case visionhub::v1::valueKind::_float_: {
			auto start = (void*)&buffer[1];
			auto data = std::get<float>(this->impl->v);
			std::memcpy(start, &data, sizeof(float));
			return buffer;
		}
		case visionhub::v1::valueKind::_double_: {
			auto start = (void*)&buffer[1];
			auto data = std::get<double>(this->impl->v);
			std::memcpy(start, &data, sizeof(double));
			return buffer;
		}
		case visionhub::v1::valueKind::_null_: {
			return buffer;
		}
		}


		// string, blob type (typeinfo, size, value)
		switch (type)
		{
		case visionhub::v1::valueKind::_string_: {

			auto & data = std::get<std::string>(this->impl->v);
			auto size = data.size();
			auto sizePoint = (uint64_t*)&buffer[1];
			*sizePoint = size;
			sizePoint += 1;

			
			std::memcpy(sizePoint, data.c_str(), size);
			return buffer;
		}

		case visionhub::v1::valueKind::_blob_: {

			auto& data = std::get<visionhub::v1::blob>(this->impl->v);
			auto size = data.size();

			auto sizePoint = (uint64_t*)&buffer[1];
			*sizePoint = size;
			sizePoint += 1;


			std::memcpy(sizePoint, data.data(), size);
			return buffer;
		}
		}


		// array type (typeinfo, element count, value)
		// map type (typeinfo, field count, (key, value pair))
		// key pair( string size, string value, value size)
		switch (type)
		{
		case visionhub::v1::valueKind::_array_: {
			auto& elements = std::get<array>(this->impl->v);

			auto sizePoint = (uint64_t*)&buffer[1];
			*sizePoint = elements.size();
			sizePoint += 1;

			auto bufferPoint = (uint8_t*)sizePoint;
			for (auto& element : elements) {
				
				auto element_data = element.serialize();
				auto element_size = element_data.size();
				std::memcpy(bufferPoint, element_data.data(), element_size);
				bufferPoint += element_size;
			}

			return buffer;
		}

		case visionhub::v1::valueKind::_map_: {
			auto& keypairs = std::get<map>(this->impl->v);

			auto sizePoint = (uint64_t*)&buffer[1];
			*sizePoint = keypairs.size();
			sizePoint += 1;

			auto bufferPoint = (uint8_t*)sizePoint;
			for (auto& keypair : keypairs) {

				auto key = keypair.first;
				auto key_size = key.size();


				std::memcpy(bufferPoint, &key_size, sizeof(uint64_t));
				bufferPoint += sizeof(uint64_t);

				std::memcpy(bufferPoint, key.c_str(), key_size);
				bufferPoint += key_size;

				auto element_data = keypair.second.serialize();
				auto element_size = element_data.size();

				std::memcpy(bufferPoint, element_data.data(), element_size);
				bufferPoint += element_size;
			}

			return buffer;
		}
		}



		throw std::exception("serialization failed");


	}
	catch (...) {
		throw;
	}
	


	
}
#pragma endregion




