#pragma once

#ifndef VISIONHUB_AOI_NATIVE_ENGINE_STACK_HELPER
#define VISIONHUB_AOI_NATIVE_ENGINE_STACK_HELPER

#include <stack>
#include <string>
#include <assert.h>
#include <angelscript.h>

namespace visionhub {
	namespace v1 {

		template<typename T, typename V>
		class helper_stack {
		public:

			static void constructor(T* self) {
				new (self)T();
			}

			static void destructor(T* self) {
				self->~T();
			}

			static void copyConstructor(T* self, const T& rhs)
			{
				new (self) T(rhs);
			}

			static void push(T* self, const V& value) {
				self->push(value);
			}

			static const V& top(T* self) {
				return self->top();
			}

			static bool empty(T* self) {
				return self->empty();
			}

			static void pop(T* self) {
				self->pop();
			}

			static std::size_t size(T* self) {
				return self->size();
			}
		};


		template<typename V> 
		void RegisterStack(asIScriptEngine* engine,
						   const std::string T_AS) {


			typedef std::stack<V> StackType;
			typedef helper_stack<StackType, V> FuncBase; 

			const std::string V_AS = std::string("stack_") + T_AS;

			assert(engine && "Passed NULL engine pointer to register stack");

			int error_code = 0;
			error_code = engine->RegisterObjectType(
				V_AS.c_str(),
				sizeof(StackType),
				asOBJ_VALUE | asGetTypeTraits<StackType>());
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
				(std::string("void push(const ") + T_AS + "&in)").c_str(),
				asFUNCTION(FuncBase::push),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register push function");

			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				(std::string("const ") + T_AS + "& top()").c_str(),
				asFUNCTION(FuncBase::top),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register push function");


			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"bool empty()",
				asFUNCTION(FuncBase::empty),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register push function");


			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void pop()",
				asFUNCTION(FuncBase::pop),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register push function");


			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"uint64 size()",
				asFUNCTION(FuncBase::size),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register push function");

		}

	}
}


#endif