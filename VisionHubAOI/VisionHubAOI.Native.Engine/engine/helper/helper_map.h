#pragma once

#ifndef VISIONHUB_AOI_NATIVE_ENGINE_MAP_HELPER
#define VISIONHUB_AOI_NATIVE_ENGINE_MAP_HELPER

#include <map>
#include <string>
#include <assert.h>
#include <angelscript.h>

namespace visionhub {
	namespace v1 {

		template<typename T, typename V>
		class helper_map {
		public:

			static void constructor(T* self) {
				new (self)T();
			}

			static void destructor(T* self) {
				self->~T();
			}

			static void copyConstructor(T* self, const T& rhs)
			{
				new (self)T(rhs);
			}

			static void insert(T* self, const std::string& key, const V& value) {
				self->insert({ key, value });
			}

			static void clear(T* self) {
				return self->clear();
			}

			static std::size_t count(T* self, const std::string&key) {
				return self->count(key);
			}

			static bool empty(T* self) {
				return self->empty();
			}

			static std::size_t erase(T* self, const std::string&key) {
				return self->erase(key);
			}

			static const V& opIndex(T* self, const std::string& key) {
				return (*self)[key];
			}

			static std::size_t size(T* self) {
				return self->size();
			}
		};


		template<typename V>
		void RegisterMap(
			asIScriptEngine* engine,
			const std::string T_AS) {


			typedef std::map<std::string, V> MapType;
			typedef helper_map<MapType, V> FuncBase;

			const std::string V_AS = std::string("map_") + T_AS;

			assert(engine && "Passed NULL engine pointer to register stack");

			int error_code = 0;
			error_code = engine->RegisterObjectType(
				V_AS.c_str(),
				sizeof(MapType),
				asOBJ_VALUE | asGetTypeTraits<MapType>());
			assert(error_code >= 0 && "Failed to register object type");

			error_code = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f()",
				asFUNCTION(FuncBase::constructor),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register constructor");

			error_code = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_DESTRUCT,
				"void f()",
				asFUNCTION(FuncBase::destructor),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register destructor");

			error_code = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				(std::string("void f(") + V_AS + "&in)").c_str(),
				asFUNCTION(FuncBase::copyConstructor),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register copy constructor");

			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				(std::string("void insert(string, const ") + T_AS + "&in)").c_str(),
				asFUNCTION(FuncBase::insert),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register insert function");

			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				std::string("void clear()").c_str(),
				asFUNCTION(FuncBase::clear),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register clear function");


			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				std::string("int64 count(const string&in)").c_str(),
				asFUNCTION(FuncBase::count),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register count function");


			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"bool empty()",
				asFUNCTION(FuncBase::empty),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register empty function");


			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void erase(const string &in)",
				asFUNCTION(FuncBase::erase),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register erase function");


			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				(T_AS + " & opIndex(const string&in) const").c_str(),
				asFUNCTION(FuncBase::opIndex),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register operator[]");


			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"uint64 size()",
				asFUNCTION(FuncBase::size),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register size function");

		}

	}
}


#endif