#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_BINDER_HELPER
#define VISIONHUB_AOI_NATIVE_CORE_BINDER_HELPER

#include <angelscript.h>

#define THROW_ERROR_BINDER(condition, message) \
if (condition) { \
throw std::exception(message);\
}\

#define OK_BINDER(condition) \
if (condition < 0) { \
throw std::exception("Error occured");\
}\


#define METHOD(c, f) asMETHOD(c, f)
#define METHODPR(c, m, p, r) asMETHODPR(c, m, p, r)
#define FUNCTION(f) asFUNCTION(f)
#define FUNCTIONPR(f, p, r) asFUNCTIONPR(f, p, r)

#define OFFSET(s, m) asOFFSET(s, m)

#define addAutoRef(type) \
addRef(#type, METHOD(type, AddRef))\
.addRelease(#type, METHOD(type, Release))\


template<class A, class B>
B* refCast(A* a) {
	if (!a) return nullptr;
	if (auto b = dynamic_cast<B*>(a)) { b->AddRef(); return b; }
	return nullptr;
}

#define CAST(s, t) asFUNCTION((refCast<s, t>))

#define addObjExport(name, source)\
addObjExportFunc(name, [](void * pointer){\
auto& sp = *reinterpret_cast<std::shared_ptr<source>*>(pointer);\
return std::dynamic_pointer_cast<visionhub::v1::object>(sp);\
})\


#define addAutoProperty(type, prop, decl)\
addProperty(#type, decl, OFFSET(type, prop))\

#define addAutoMethod1(type, method, decl)\
addMethod(#type, decl, METHOD(type, method))\

#define addAutoMethod2(type, method, P, R, decl)\
addMethod(#type, decl, METHODPR(type, method, P, R))\

#define addAutoGlobalMethod1(type, method, decl, pointer)\
addGlobalFunction(decl, METHOD(type, method), pointer)\

#define addAutoGlobalMethod2(type, method, P, R, decl, pointer)\
addGlobalFunction(decl, METHODPR(type, method, P, R), pointer)\

#define addAutoGlobalFunction1(type, f, decl)\
addGlobalFunction(decl, FUNCTION(type::f))\

#define addAutoGlobalFunction2(type, f, P, R, decl)\
addGlobalFunction(decl, FUNCTIONPR(type::f, P, R))\


#define addAutoFactory(type, f, P, R, decl)\
addFactory(#type, decl, FUNCTIONPR(type::f, P, R))\

//#define addConstructor(type, decl)\
//addGlobalFunction(decl, FUNCTION(type::type##_Constructor))\


#define addAutoEnumValue(type, enumValue)\
addEnumValue(#type, #enumValue, static_cast<int>(type::enumValue))



#endif