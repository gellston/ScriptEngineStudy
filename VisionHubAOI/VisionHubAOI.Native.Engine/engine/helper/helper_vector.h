/*
   std::vector binding library for AngelScript
   Copyright (c) 2004 Anthony "JM" Casteel
   This software is provided 'as-is', without any express or implied
   warranty. In no event will the authors be held liable for any
   damages arising from the use of this software.
   Permission is granted to anyone to use this software for any
   purpose, including commercial applications, and to alter it and
   redistribute it freely, subject to the following restrictions:
   1. The origin of this software must not be misrepresented; you
	  must not claim that you wrote the original software. If you use
	  this software in a product, an acknowledgment in the product
	  documentation would be appreciated but is not required.
   2. Altered source versions must be plainly marked as such, and
	  must not be misrepresented as being the original software.
   3. This notice may not be removed or altered from any source
	  distribution.
   The original version of this library can be located at:
   http://www.angelcode.com/angelscript/
   AngelScript Copyright (c) 2003-2004 Andreas Jönsson (andreas@angelcode.com)
   Anthony "JM" Casteel
   DeyjaL@AOL.com
*/

// 2004-10-26 : Minor changes by Andreas Jönsson
// 2005-01-08 : Made compileable for dreamcast by Fredrik Ehnbom

#ifndef VISIONHUB_AOI_NATIVE_ENGINE_VECTOR_HELPER
#define VISIONHUB_AOI_NATIVE_ENGINE_VECTOR_HELPER


#include <vector>
#include <string>
#include <assert.h>

#include <angelscript.h>

namespace visionhub {
	namespace v1 {
		template <typename T, typename V>
		class helper_vector
		{
		public:
			static void constructor(T* self)
			{
				new (self) T();
			}

			static void destructor(T* self)
			{
				self->~T();
			}

			static void copyConstructor(T* self, const T& rhs)
			{
				new (self) T(rhs);
			}

			static void numConstructor(T* self, int size)
			{
				new (self) T(size);
			}

			static T& assign(T* self, const T& rhs)
			{
				*self = rhs;
				return *self;
			}

			static V& index(T* self, int i)
			{

				if (i < 0 || i >= (signed)self->size())
				{
					asIScriptContext* context = asGetActiveContext();
					if (context)
						context->SetException("Array Index Out of Bounds.");
					return *((V*)0);
				}

				return (*self)[i];
			}

			static int size(T* self)
			{
				return (int)self->size();
			}

			static void resize(T* self, int size)
			{
				self->resize(size);
			}

			static void pushBack(T* self, const V& in)
			{
				self->push_back(in);
			}

			static void popBack(T* self)
			{
				self->pop_back();
			}

			static void erase(T* self, int i)
			{
				self->erase(self->begin() + i);
			}

			static void insert(T* self, int i, const V& e)
			{
				self->insert(self->begin() + i, e);
			}

			static void clear(T* self)
			{
				self->clear();
			}
		};

		template <typename V>
		void RegisterVector(asIScriptEngine* engine,
						    const std::string T_AS)
		{
			typedef std::vector<V> VectorType;
			typedef helper_vector<VectorType, V> FuncBase;

			const std::string V_AS = std::string("vector_") + T_AS;

			assert(engine && "Passed NULL engine pointer to registerVector");

			int error_code = 0;
			error_code = engine->RegisterObjectType(
				V_AS.c_str(), 
				sizeof(VectorType), 
				asOBJ_VALUE | asGetTypeTraits<VectorType>());
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

			error_code = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f(int)",
				asFUNCTION(FuncBase::numConstructor),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register construct(size)");

			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				(T_AS + " & opIndex(int)").c_str(),
				asFUNCTION(FuncBase::index),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register operator[]");

			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				("const " + T_AS + " & opIndex(int) const").c_str(),
				asFUNCTION(FuncBase::index),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register operator[]");

			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				(V_AS + " & opAssign(const " + V_AS + "&in)").c_str(),
				asFUNCTION(FuncBase::assign),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register operator=");

			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"int size() const",
				asFUNCTION(FuncBase::size),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register size");

			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void clear()",
				asFUNCTION(FuncBase::clear),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register clear");

			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void resize(int)",
				asFUNCTION(FuncBase::resize),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register resize");

			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				(std::string("void push_back(") + T_AS + "&in)").c_str(),
				asFUNCTION(FuncBase::pushBack),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register push_back");

			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void pop_back()",
				asFUNCTION(FuncBase::popBack),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register pop_back");

			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				"void erase(int)",
				asFUNCTION(FuncBase::erase),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register erase");

			error_code = engine->RegisterObjectMethod(
				V_AS.c_str(),
				(std::string("void insert(int, const ") + T_AS + " &in)").c_str(),
				asFUNCTION(FuncBase::insert),
				asCALL_CDECL_OBJFIRST);
			assert(error_code >= 0 && "Failed to register insert");

		}
	}
}


#endif