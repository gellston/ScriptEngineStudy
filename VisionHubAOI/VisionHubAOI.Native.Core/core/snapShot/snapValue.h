#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_SNAP_VALUE
#define VISIONHUB_AOI_NATIVE_CORE_SNAP_VALUE


#include "../coreMacro/api.h"

#include "snapKind.h"


#include <string>
#include <vector>
#include <memory>


namespace visionhub {
	namespace v1 {
		class engine;
		struct memoryBlock;
		struct object;
		struct image;
		struct rect;
		struct test;

		struct snapValue;
		using snapValue_ptr = std::shared_ptr<snapValue>;
		struct impl_snapValue;
		struct snapValue {
#pragma region IMPL
		private:
			std::shared_ptr<impl_snapValue> impl;
			friend struct snapValueAtt;
#pragma endregion
		public:

#pragma region Constructor
			VISIONHUB_AOI_NATIVE_CORE_API snapValue();
#pragma endregion

#pragma region Public Functions
			VISIONHUB_AOI_NATIVE_CORE_API snapValue_ptr clone();
			VISIONHUB_AOI_NATIVE_CORE_API snapKind kind();
			VISIONHUB_AOI_NATIVE_CORE_API std::string type();
			VISIONHUB_AOI_NATIVE_CORE_API int8_t int8();
			VISIONHUB_AOI_NATIVE_CORE_API int16_t int16();
			VISIONHUB_AOI_NATIVE_CORE_API int32_t int32();
			VISIONHUB_AOI_NATIVE_CORE_API int64_t int64();
			VISIONHUB_AOI_NATIVE_CORE_API uint8_t uint8();
			VISIONHUB_AOI_NATIVE_CORE_API uint16_t uint16();
			VISIONHUB_AOI_NATIVE_CORE_API uint32_t uint32();
			VISIONHUB_AOI_NATIVE_CORE_API uint64_t uint64();
			VISIONHUB_AOI_NATIVE_CORE_API double double64();
			VISIONHUB_AOI_NATIVE_CORE_API float float32();
			VISIONHUB_AOI_NATIVE_CORE_API bool boolean();
			VISIONHUB_AOI_NATIVE_CORE_API std::string string();
			VISIONHUB_AOI_NATIVE_CORE_API std::vector<snapValue_ptr> elements();
			VISIONHUB_AOI_NATIVE_CORE_API std::vector<std::pair<std::string, snapValue_ptr>> fields();
			VISIONHUB_AOI_NATIVE_CORE_API memoryBlock memoryBlock();
			VISIONHUB_AOI_NATIVE_CORE_API void print(int intent);
#pragma endregion



		};

		struct snapValueAtt {

#pragma region Private Property
		private:
			friend class engine;
			friend class impl_engine;
			friend struct image;
			friend struct rect;
			friend struct test;
#pragma endregion

#pragma region Public Functions
			VISIONHUB_AOI_NATIVE_CORE_API static void setKind(const snapValue_ptr& value, const snapKind& kind);
			VISIONHUB_AOI_NATIVE_CORE_API static void setType(const snapValue_ptr& value, const std::string& s);
			VISIONHUB_AOI_NATIVE_CORE_API static void setValue(const snapValue_ptr& value, const int8_t& x);
			VISIONHUB_AOI_NATIVE_CORE_API static void setValue(const snapValue_ptr& value, const int16_t& x);
			VISIONHUB_AOI_NATIVE_CORE_API static void setValue(const snapValue_ptr& value, const int32_t& x);
			VISIONHUB_AOI_NATIVE_CORE_API static void setValue(const snapValue_ptr& value, const int64_t& x);
			VISIONHUB_AOI_NATIVE_CORE_API static void setValue(const snapValue_ptr& value, const uint8_t& x);
			VISIONHUB_AOI_NATIVE_CORE_API static void setValue(const snapValue_ptr& value, const uint16_t& x);
			VISIONHUB_AOI_NATIVE_CORE_API static void setValue(const snapValue_ptr& value, const uint32_t& x);
			VISIONHUB_AOI_NATIVE_CORE_API static void setValue(const snapValue_ptr& value, const uint64_t& x);
			VISIONHUB_AOI_NATIVE_CORE_API static void setValue(const snapValue_ptr& value, const double& x);
			VISIONHUB_AOI_NATIVE_CORE_API static void setValue(const snapValue_ptr& value, const float& x);
			VISIONHUB_AOI_NATIVE_CORE_API static void setValue(const snapValue_ptr& value, const bool& x);
			VISIONHUB_AOI_NATIVE_CORE_API static void setValue(const snapValue_ptr& value, const std::string& x);
			VISIONHUB_AOI_NATIVE_CORE_API static void setValue(const snapValue_ptr& value, const memoryBlock& block);


			VISIONHUB_AOI_NATIVE_CORE_API static void addField(const snapValue_ptr& value, const std::string &field, const snapValue_ptr& object);
			VISIONHUB_AOI_NATIVE_CORE_API static void addField(const snapValue_ptr& value, const std::string &field, const bool& _value);
			VISIONHUB_AOI_NATIVE_CORE_API static void addField(const snapValue_ptr& value, const std::string &field, const double& _value);
			VISIONHUB_AOI_NATIVE_CORE_API static void addField(const snapValue_ptr& value, const std::string &field, const float& _value);
			VISIONHUB_AOI_NATIVE_CORE_API static void addField(const snapValue_ptr& value, const std::string &field, const int16_t& _value);
			VISIONHUB_AOI_NATIVE_CORE_API static void addField(const snapValue_ptr& value, const std::string &field, const int32_t& _value);
			VISIONHUB_AOI_NATIVE_CORE_API static void addField(const snapValue_ptr& value, const std::string &field, const int64_t& _value);
			VISIONHUB_AOI_NATIVE_CORE_API static void addField(const snapValue_ptr& value, const std::string &field, const int8_t& _value);
			VISIONHUB_AOI_NATIVE_CORE_API static void addField(const snapValue_ptr& value, const std::string &field, const uint16_t& _value);
			VISIONHUB_AOI_NATIVE_CORE_API static void addField(const snapValue_ptr& value, const std::string &field, const uint32_t& _value);
			VISIONHUB_AOI_NATIVE_CORE_API static void addField(const snapValue_ptr& value, const std::string &field, const uint64_t& _value);
			VISIONHUB_AOI_NATIVE_CORE_API static void addField(const snapValue_ptr& value, const std::string &field, const uint8_t& _value);
			VISIONHUB_AOI_NATIVE_CORE_API static void addField(const snapValue_ptr& value, const std::string &field, const std::string& _value);
			VISIONHUB_AOI_NATIVE_CORE_API static void addField(const snapValue_ptr& value, const std::string &field, const memoryBlock& block);



			VISIONHUB_AOI_NATIVE_CORE_API static void addElement(const snapValue_ptr& value, const snapValue_ptr& object);

		
#pragma endregion
		};
	}
}

#endif