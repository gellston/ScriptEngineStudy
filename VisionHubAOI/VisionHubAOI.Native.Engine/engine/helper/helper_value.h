#pragma once


#ifndef VISIONHUB_AOI_NATIVE_ENGINE_VALUE_HELPER
#define VISIONHUB_AOI_NATIVE_ENGINE_VALUE_HELPER

#include <vector>
#include <string>
#include <assert.h>
#include <memory>

#include <core/collection/value.h>

#include <angelscript.h>

namespace visionhub {
	namespace v1 {

		class helper_value {
		public:
			static void constructorNull(visionhub::v1::value* self) {
				new (self) visionhub::v1::value();
			}

			static void constructorBool(visionhub::v1::value* self, const bool & _value) {
				new (self) visionhub::v1::value(_value);
			}

			static void constructorInt8(visionhub::v1::value* self, const int8_t& _value) {
				new (self) visionhub::v1::value(_value);
			}

			static void constructorInt16(visionhub::v1::value* self, const int16_t& _value) {
				new (self) visionhub::v1::value(_value);
			}

			static void constructorInt32(visionhub::v1::value* self, const int32_t& _value) {
				new (self) visionhub::v1::value(_value);
			}

			static void constructorInt64(visionhub::v1::value* self, const int64_t& _value) {
				new (self) visionhub::v1::value(_value);
			}


			static void constructorUInt8(visionhub::v1::value* self, const uint8_t& _value) {
				new (self) visionhub::v1::value(_value);
			}

			static void constructorUInt16(visionhub::v1::value* self, const uint16_t& _value) {
				new (self) visionhub::v1::value(_value);
			}

			static void constructorUInt32(visionhub::v1::value* self, const uint32_t& _value) {
				new (self) visionhub::v1::value(_value);
			}

			static void constructorUInt64(visionhub::v1::value* self, const uint64_t& _value) {
				new (self) visionhub::v1::value(_value);
			}


			static void constructorFloat(visionhub::v1::value* self, const float& _value) {
				new (self) visionhub::v1::value(_value);
			}

			static void constructorDouble(visionhub::v1::value* self, const double& _value) {
				new (self) visionhub::v1::value(_value);
			}

			static void constructorString(visionhub::v1::value* self, const std::string& _value) {
				new (self) visionhub::v1::value(_value);
			}

			static void constructorValue(visionhub::v1::value* self, const visionhub::v1::value& _value) {
				new (self) visionhub::v1::value(_value);
			}

			static void destructor(visionhub::v1::value* self) {
				using T = visionhub::v1::value;

				self->~T();
			}

			static visionhub::v1::value opIndexString(visionhub::v1::value* self, const std::string& key) {

				try {

					auto _value = (*self)[key];
					return _value;
				}
				catch (...) {
					throw;
				}
			}

			static visionhub::v1::value opIndexInt(visionhub::v1::value* self, const int & index) {

				try {

					auto _value = (*self)[index];
					return _value;
				}
				catch (...) {
					throw;
				}
			}

			static void add(visionhub::v1::value* self, const visionhub::v1::value& value) {
				try {
					self->add(value);
				}
				catch (...) {
					throw;
				}
			}

			static void set(visionhub::v1::value* self, const std::string& key, const visionhub::v1::value& value) {
				try {
					self->set(key, value);
				}
				catch (...) {
					throw;
				}
			}

			static visionhub::v1::valueKind kind(visionhub::v1::value* self) {
				return self->kind();
			}

			static std::size_t size(visionhub::v1::value* self) {
				return self->size();
			}

			static std::size_t count(visionhub::v1::value* self) {
				return self->count();
			}

			bool static getBool(visionhub::v1::value* self, bool& value) {
				return self->get(value);
			}

			bool static getInt8(visionhub::v1::value* self, int8_t& value) {
				return self->get(value);
			}

			bool static getInt16(visionhub::v1::value* self, int16_t& value) {
				return self->get(value);
			}

			bool static getInt32(visionhub::v1::value* self, int32_t& value) {
				return self->get(value);
			}

			bool static getInt64(visionhub::v1::value* self, int64_t& value) {
				return self->get(value);
			}



			bool static getUInt8(visionhub::v1::value* self, uint8_t& value) {
				return self->get(value);
			}

			bool static getUInt16(visionhub::v1::value* self, uint16_t& value) {
				return self->get(value);
			}

			bool static getUInt32(visionhub::v1::value* self, uint32_t& value) {
				return self->get(value);
			}

			bool static getUInt64(visionhub::v1::value* self, uint64_t& value) {
				return self->get(value);
			}


			bool static getFloat(visionhub::v1::value* self, float& value) {
				return self->get(value);
			}

			bool static getDouble(visionhub::v1::value* self, double& value) {
				return self->get(value);
			}

			bool static getString(visionhub::v1::value* self, std::string& value) {
				return self->get(value);
			}




			void static setBool(visionhub::v1::value* self, const bool& value) {
				self->set(value);
			}

			void static setInt8(visionhub::v1::value* self, const int8_t& value) {
				self->set(value);
			}

			void static setInt16(visionhub::v1::value* self, const int16_t& value) {
				self->set(value);
			}

			void static setInt32(visionhub::v1::value* self, const int32_t& value) {
				self->set(value);
			}

			void static setInt64(visionhub::v1::value* self, const int64_t& value) {
				self->set(value);
			}



			void static setUInt8(visionhub::v1::value* self, const uint8_t& value) {
				self->set(value);
			}

			void static setUInt16(visionhub::v1::value* self, const uint16_t& value) {
				self->set(value);
			}

			void static setUInt32(visionhub::v1::value* self, const uint32_t& value) {
				self->set(value);
			}

			void static setUInt64(visionhub::v1::value* self, const uint64_t& value) {
				self->set(value);
			}


			void static setFloat(visionhub::v1::value* self, const float& value) {
				self->set(value);
			}

			void static setDouble(visionhub::v1::value* self, const double& value) {
				self->set(value);
			}

			void static setString(visionhub::v1::value* self, const std::string& value) {
				self->set(value);
			}

		};


		void RegisterValue(asIScriptEngine* engine) {

			const std::string V_AS = "value";

			int r = 0;
			r = engine->RegisterObjectType(
				V_AS.c_str(),
				sizeof(value),
				asOBJ_VALUE | asGetTypeTraits<value>());
			assert(r >= 0 && "Failed to register object type");


			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f()",
				asFUNCTION(helper_value::constructorNull),
				asCALL_CDECL_OBJFIRST
			);


			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_DESTRUCT,
				"void f()",
				asFUNCTION(helper_value::destructor),
				asCALL_CDECL_OBJFIRST
			);

			assert(r >= 0 && "Failed to register value constructor");

			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f(const bool&in)",
				asFUNCTION(helper_value::constructorBool),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register value constructor");


			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f(const int8&in)",
				asFUNCTION(helper_value::constructorInt8),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register value constructor");

			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f(const int16&in)",
				asFUNCTION(helper_value::constructorInt16),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register value constructor");

			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f(const int32&in)",
				asFUNCTION(helper_value::constructorInt32),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register value constructor");

			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f(const int64&in)",
				asFUNCTION(helper_value::constructorInt64),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register value constructor");


			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f(const uint8&in)",
				asFUNCTION(helper_value::constructorUInt8),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register value constructor");

			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f(const uint16&in)",
				asFUNCTION(helper_value::constructorUInt16),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register value constructor");

			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f(const uint32&in)",
				asFUNCTION(helper_value::constructorUInt32),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register value constructor");

			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f(const uint64&in)",
				asFUNCTION(helper_value::constructorUInt64),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register value constructor");


			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f(const uint32&in)",
				asFUNCTION(helper_value::constructorUInt32),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register value constructor");

			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f(const float&in)",
				asFUNCTION(helper_value::constructorFloat),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register value constructor");


			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f(const double&in)",
				asFUNCTION(helper_value::constructorDouble),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register value constructor");


			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f(const string&in)",
				asFUNCTION(helper_value::constructorString),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register value constructor");

			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f(const value&in)",
				asFUNCTION(helper_value::constructorValue),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register value constructor");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"value opIndex(const string&in)",
				asFUNCTION(helper_value::opIndexString),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register [string] operation");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"value opIndex(const int32&in)",
				asFUNCTION(helper_value::opIndexInt),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register [int] operation");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void add(const value&in)",
				asFUNCTION(helper_value::add),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register add Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void set(const string&in, const value&in)",
				asFUNCTION(helper_value::set),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register set Function");



			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"valueKind kind()",
				asFUNCTION(helper_value::kind),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register set Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"uint64 size()",
				asFUNCTION(helper_value::size),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register size Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"uint64 count()",
				asFUNCTION(helper_value::count),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register count Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"bool get(bool&out)",
				asFUNCTIONPR(helper_value::getBool, (visionhub::v1::value*, bool&), bool),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register get Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"bool get(int8&out)",
				asFUNCTIONPR(helper_value::getInt8, (visionhub::v1::value*, int8_t&), bool),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register get Function");

			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"bool get(int16&out)",
				asFUNCTIONPR(helper_value::getInt16, (visionhub::v1::value*, int16_t&), bool),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register get Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"bool get(int32&out)",
				asFUNCTIONPR(helper_value::getInt32, (visionhub::v1::value*, int32_t&), bool),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register get Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"bool get(int64&out)",
				asFUNCTIONPR(helper_value::getInt64, (visionhub::v1::value*, int64_t&), bool),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register get Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"bool get(uint8&out)",
				asFUNCTIONPR(helper_value::getUInt8, (visionhub::v1::value*, uint8_t&), bool),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register get Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"bool get(uint16&out)",
				asFUNCTIONPR(helper_value::getUInt16, (visionhub::v1::value*, uint16_t&), bool),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register get Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"bool get(uint32&out)",
				asFUNCTIONPR(helper_value::getUInt32, (visionhub::v1::value*, uint32_t&), bool),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register get Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"bool get(uint64&out)",
				asFUNCTIONPR(helper_value::getUInt64, (visionhub::v1::value*, uint64_t&), bool),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register get Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"bool get(float&out)",
				asFUNCTIONPR(helper_value::getFloat, (visionhub::v1::value*, float&), bool),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register get Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"bool get(double&out)",
				asFUNCTIONPR(helper_value::getDouble, (visionhub::v1::value*, double&), bool),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register get Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"bool get(string&out)",
				asFUNCTIONPR(helper_value::getString, (visionhub::v1::value*, std::string&), bool),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register get Function");




			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void set(const bool&in)",
				asFUNCTIONPR(helper_value::setBool, (visionhub::v1::value*, const bool&), void),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register set Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void set(const int8&in)",
				asFUNCTIONPR(helper_value::setInt8, (visionhub::v1::value*, const int8_t&), void),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register set Function");

			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void set(const int16&in)",
				asFUNCTIONPR(helper_value::setInt16, (visionhub::v1::value*, const int16_t&), void),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register set Function");

			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void set(const int32&in)",
				asFUNCTIONPR(helper_value::setInt32, (visionhub::v1::value*, const int32_t&), void),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register set Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void set(const int64&in)",
				asFUNCTIONPR(helper_value::setInt64, (visionhub::v1::value*, const int64_t&), void),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register set Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void set(const float&in)",
				asFUNCTIONPR(helper_value::setFloat, (visionhub::v1::value*, const float&), void),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register set Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void set(const double&in)",
				asFUNCTIONPR(helper_value::setDouble, (visionhub::v1::value*, const double&), void),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register set Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void set(const string&in)",
				asFUNCTIONPR(helper_value::setString, (visionhub::v1::value*, const std::string&), void),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register set Function");



			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void set(const uint8&in)",
				asFUNCTIONPR(helper_value::setUInt8, (visionhub::v1::value*, const uint8_t&), void),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register set Function");

			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void set(const uint16&in)",
				asFUNCTIONPR(helper_value::setUInt16, (visionhub::v1::value*, const uint16_t&), void),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register set Function");

			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void set(const uint32&in)",
				asFUNCTIONPR(helper_value::setUInt32, (visionhub::v1::value*, const uint32_t&), void),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register set Function");


			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void set(const uint64&in)",
				asFUNCTIONPR(helper_value::setUInt64, (visionhub::v1::value*, const uint64_t&), void),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register set Function");

		}

	}
}

#endif