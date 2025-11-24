#pragma once


#ifndef VISIONHUB_AOI_NATIVE_ENGINE_SMART_PTR
#define VISIONHUB_AOI_NATIVE_ENGINE_SMART_PTR

#include <memory>
#include <string>
#include <assert.h>

#include <core/binding/binder.h>

#include <angelscript.h>

namespace visionhub {
	namespace v1 {

		template<class T>
		class helper_smart_ptr {
		public:

			static void constructor(std::shared_ptr<T>* self) {
				new (self) std::shared_ptr<T>();
			}

			static void destructor(std::shared_ptr<T>* self) {
				using SharedT = std::shared_ptr<T>;
				self->~SharedT();
			}

			static void copyConstructor(std::shared_ptr<T>* self, const std::shared_ptr<T>& other) {
				new (self) std::shared_ptr<T>(other);
			}

			static std::shared_ptr<T>& assign(std::shared_ptr<T>* self, const std::shared_ptr<T>& other) {
				
				*self = other;
				return *self;
			}

			static T* get(const std::shared_ptr<T>* self) {
				if (self == nullptr) return nullptr;
				if (*self == nullptr) return nullptr;

				return self->get();
			}
		};


		template<class T_ARG, class T_RET>
		class smart_ptr_cast {
		public:
			static std::shared_ptr<T_RET> convert(std::shared_ptr<T_ARG>* self) {
				std::shared_ptr<T_RET> o = *self;

				return o;
			}
		};


		template<typename T_ARG, typename T_RET> 
		void RegisterSmartPointerCast(asIScriptEngine* engine,
			const std::string ARG_NAME,
			const std::string RET_NAME) {

			typedef std::shared_ptr<T_RET> RetType;
			typedef std::shared_ptr<T_ARG> ArgType;

			typedef smart_ptr_cast<T_ARG, T_RET> FuncConvert;

			int r = 0;

			r = engine->RegisterObjectMethod(
				(ARG_NAME + "_ptr").c_str(),
				(RET_NAME + "_ptr opImplCast()").c_str(),
				asFUNCTION(FuncConvert::convert),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register smart pointer type converter");
		}


		template <typename V>
		void RegisterSmartPointer(asIScriptEngine* engine, binder& _binder, const std::string T_AS) {

			typedef std::shared_ptr<V> PtrType;
			typedef helper_smart_ptr<V> SmartType;

			int r = 0;

			const std::string V_AS =  T_AS + "_ptr";

			_binder.addObjExportFunc(V_AS, [](void* pointer) {
				auto* sp = reinterpret_cast<PtrType*>(pointer);

				if (!sp || !sp->get()) {
					return visionhub::v1::object_ptr{};
				}

				return std::dynamic_pointer_cast<visionhub::v1::object>(*sp);
			});

			r = engine->RegisterObjectType(
				V_AS.c_str(),					  
				sizeof(PtrType),					  
				asOBJ_VALUE | asGetTypeTraits<PtrType>());

			assert(r >= 0 && "Failed to register object type");

			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				"void f()",
				asFUNCTION(SmartType::constructor),
				asCALL_CDECL_OBJFIRST);
			assert(r >= 0 && "Failed to register smart pointer constructor");

			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_CONSTRUCT,
				("void f(const " + V_AS + "&in)").c_str(),
				asFUNCTION(SmartType::copyConstructor),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register smart pointer copy constructor");

			r = engine->RegisterObjectBehaviour(
				V_AS.c_str(),
				asBEHAVE_DESTRUCT,
				"void f()",
				asFUNCTION(SmartType::destructor),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register smart pointer destructor");

			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				(V_AS + "&opAssign(const " + V_AS + " &in)").c_str(),
				asFUNCTION(SmartType::assign),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register smart pointer destructor");

			r = engine->RegisterObjectMethod(
				V_AS.c_str(),
				(T_AS + "@ get()").c_str(),
				asFUNCTION(SmartType::get),
				asCALL_CDECL_OBJFIRST
			);
			assert(r >= 0 && "Failed to register smart pointer destructor");
		}
	}
}

#endif