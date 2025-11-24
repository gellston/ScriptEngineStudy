#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_TYPE_REGISTRY
#define VISIONHUB_AOI_NATIVE_CORE_TYPE_REGISTRY


#include "../collection/memoryBlock.h"
#include "../types/coreTypes.h"
#include "../coreMacro/api.h"

#include <variant>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>

#include <memory>

namespace visionhub {
	namespace v1 {
		struct object;
		using object_ptr = std::shared_ptr<object>;
		using meta = std::variant<
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
			visionhub::v1::memoryBlock,
			object_ptr,

			std::vector<std::monostate>,
			std::vector<bool>,
			std::vector<int8_t>,
			std::vector<int16_t>,
			std::vector<int32_t>,
			std::vector<int64_t>,
			std::vector<uint8_t>,
			std::vector<uint16_t>,
			std::vector<uint32_t>,
			std::vector<uint64_t>,
			std::vector<float>,
			std::vector<double>,
			std::vector<std::string>,
			std::vector<visionhub::v1::memoryBlock>,
			std::vector<object_ptr>,

			std::unordered_map<std::string, std::monostate>,
			std::unordered_map<std::string, bool>,
			std::unordered_map<std::string, int8_t>,
			std::unordered_map<std::string, int16_t>,
			std::unordered_map<std::string, int32_t>,
			std::unordered_map<std::string, int64_t>,
			std::unordered_map<std::string, uint8_t>,
			std::unordered_map<std::string, uint16_t>,
			std::unordered_map<std::string, uint32_t>,
			std::unordered_map<std::string, uint64_t>,
			std::unordered_map<std::string, float>,
			std::unordered_map<std::string, double>,
			std::unordered_map<std::string, std::string>,
			std::unordered_map<std::string, visionhub::v1::memoryBlock>,
			std::unordered_map<std::string, object_ptr>
		>;

	
		struct propertyInfo {
			std::string name = "";
			std::function<meta(visionhub::v1::object* o)> reader;
		};


		struct typeInfo {
			std::string name = "";
			visionhub::v1::coreTypes coreType;
			std::vector<propertyInfo> props;

			propertyInfo searchProps(const std::string & name) {
				for (auto prop : props) {
					if (prop.name != name) continue;
					return prop;
				}

				throw std::exception("Invalid prop name");
			}
		};


		class impl_typeRegistry;
		class typeRegistry {

#pragma region Private
		private:
			std::unique_ptr<impl_typeRegistry> impl;
#pragma endregion

#pragma region Constructor
		private:
			VISIONHUB_AOI_NATIVE_CORE_API typeRegistry();
#pragma endregion


#pragma region Public Functions
		public:
			VISIONHUB_AOI_NATIVE_CORE_API static typeRegistry& get();
			VISIONHUB_AOI_NATIVE_CORE_API void add(typeInfo ti);
			VISIONHUB_AOI_NATIVE_CORE_API typeInfo* find(visionhub::v1::coreTypes type);
			VISIONHUB_AOI_NATIVE_CORE_API std::vector<visionhub::v1::typeInfo> typeInfo();
#pragma endregion

		};



		template<typename T>
		struct is_std_vector : std::false_type {
			using type = void;
		};


		template<typename T>
		struct is_std_vector<std::vector<T>> : std::true_type {
			using type = T;
		};


		template<typename T>
		struct is_std_map : std::false_type {
			using type = void;
		};

		template<typename T>
		struct is_std_map<std::unordered_map<std::string, T>> : std::true_type {
			using type = T;
		};


		template<typename T>
		struct is_smart_pointer{
			using type = void;
			static constexpr bool value = false;
		};

		template<typename T>
		struct is_smart_pointer<std::shared_ptr<T>> {
			using type = T;
			static constexpr bool value = true;
		};



		struct typeBuilder {
			typeInfo ti;
			explicit typeBuilder(const std::string& name, visionhub::v1::coreTypes ct) {
				ti.name = name;
				ti.coreType = ct;
			}

			typeInfo& complete() {
				return ti;
			}

			template<class T, class R> typeBuilder& prop(const char* name, R(T::* getter)()) {
				ti.props.push_back(propertyInfo{
					name,
					[getter](visionhub::v1::object* o)->visionhub::v1::meta {
						if (o == nullptr) return meta();
						auto self = static_cast<T*>(o);
						if constexpr (std::is_enum_v<R>) {
							return static_cast<int32_t>((self->*getter)());
						}
						else if constexpr (is_std_vector<R>::value){
							using inType = typename is_std_vector<R>::type;
							if constexpr (is_smart_pointer<inType>::value) {
								std::vector<object_ptr> temp;
								std::vector<inType> returnValue = (self->*getter)();
								for (auto& element : returnValue) {
									auto castedElement = std::dynamic_pointer_cast<object>(element);
									temp.push_back(castedElement);
								}
								return temp;
							}
						}
						else if constexpr (is_std_map<R>::value) {
							using inType = typename is_std_map<R>::type;
							if constexpr (is_smart_pointer<inType>::value) {
								std::unordered_map<std::string, object_ptr> temp;
								std::unordered_map<std::string, inType> returnValue = (self->*getter)();
								for (auto& key_pair : returnValue) {
									auto& key = key_pair.first;
									auto element = key_pair.second;
									auto castedElement = std::dynamic_pointer_cast<object>(element);
									temp.insert({key, castedElement});
								}
								return temp;
							}
						}
						else {
							return (self->*getter)(); // bool, double, string µî
						}
					}
					});
				return *this;
			}
		};
	}
}

#define REFLECTION_BEGIN(TYPENAME)\
using namespace visionhub::v1;\
typeRegistry::get().add(\
typeBuilder(#TYPENAME, visionhub::v1::coreTypes::TYPENAME)\


#define REFLECTION_PROP(TYPENAME, PROP)\
.prop<TYPENAME>(#PROP, &TYPENAME::PROP)\


#define REFLECTION_END()\
.complete()\
);\



#endif