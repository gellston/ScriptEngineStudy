


#include "core/binding/binder.h"
#include "core/binding/binderHelper.h"






#pragma region Constructor
visionhub::v1::binder::binder(visionhub::v1::runtime runtime, std::shared_ptr<memoryPool> pool) {
	this->engine = (asIScriptEngine*)runtime.engine;
	this->pool = pool;
	THROW_ERROR_BINDER(this->engine == nullptr, "Invalid engine")
	THROW_ERROR_BINDER(this->pool == nullptr, "Invalid global pool")
}

#pragma endregion


#pragma region Public Functions
visionhub::v1::binder& visionhub::v1::binder::nameSpace(const std::string& name) {
	THROW_ERROR_BINDER(this->engine->SetDefaultNamespace(name.c_str()) < 0, "Set default namespace failed")
	return *this;
}

visionhub::v1::binder& visionhub::v1::binder::addObject(const std::string & typeName) {
	THROW_ERROR_BINDER(this->engine->RegisterObjectType(typeName.c_str(), 0, asOBJ_REF | asOBJ_NOCOUNT) < 0, "Add object type failed")
		return *this;
}

visionhub::v1::binder& visionhub::v1::binder::addGlobalFunction(const std::string& decl, const asSFuncPtr& memberFunc, void * thisPtr) {
	THROW_ERROR_BINDER(engine->RegisterGlobalFunction(decl.c_str(), memberFunc, asCALL_THISCALL_ASGLOBAL, thisPtr) < 0, "Add global function failed")
	return *this;
}

visionhub::v1::binder& visionhub::v1::binder::addGlobalFunction(const std::string& decl, const asSFuncPtr& function) {
	THROW_ERROR_BINDER(engine->RegisterGlobalFunction(decl.c_str(), function, asCALL_CDECL) < 0, "Add global function failed")
	return *this;
}

visionhub::v1::binder& visionhub::v1::binder::addProperty(const std::string typeName, const std::string& decl, const int byteoffset) {
	THROW_ERROR_BINDER(engine->RegisterObjectProperty(typeName.c_str(), decl.c_str(), byteoffset) < 0, "Add property failed")
	return *this;
}

visionhub::v1::binder& visionhub::v1::binder::addMethod(const std::string typeName, const std::string& decl, const asSFuncPtr& memberFunc) {
	THROW_ERROR_BINDER(engine->RegisterObjectMethod(typeName.c_str(), decl.c_str(), memberFunc, asCALL_THISCALL) < 0, "Add member function failed")
	return *this;
}


visionhub::v1::binder& visionhub::v1::binder::addRef(const std::string typeName, const asSFuncPtr& memberFunc) {
	THROW_ERROR_BINDER(engine->RegisterObjectBehaviour(typeName.c_str(), asBEHAVE_ADDREF, "void f()", memberFunc, asCALL_THISCALL) < 0, "Add global member function failed")
	return *this;
}

visionhub::v1::binder& visionhub::v1::binder::addRelease(const std::string typeName, const asSFuncPtr& memberFunc) {
	THROW_ERROR_BINDER(engine->RegisterObjectBehaviour(typeName.c_str(), asBEHAVE_RELEASE, "void f()", memberFunc, asCALL_THISCALL) < 0, "Add global member function failed")
	return *this;
}

visionhub::v1::binder& visionhub::v1::binder::addFactory(const std::string typeName, const std::string& decl, const asSFuncPtr& function) {
	THROW_ERROR_BINDER(engine->RegisterObjectBehaviour(typeName.c_str(), asBEHAVE_FACTORY, decl.c_str(), function, asCALL_CDECL) < 0, "Add factoryfunction failed")
	return *this;
}

visionhub::v1::binder& visionhub::v1::binder::addImplicitCast(const std::string sourceName, const std::string& targetName, const asSFuncPtr& memberFunc) {
	std::string castDescription = "";
	castDescription += targetName;
	castDescription += "@ ";
	castDescription += "opImplCast()";
	THROW_ERROR_BINDER(engine->RegisterObjectMethod(sourceName.c_str(), castDescription.c_str(), memberFunc, asCALL_CDECL_OBJFIRST) < 0, "Add Implicit cast failed")
	return *this;
}

visionhub::v1::binder& visionhub::v1::binder::addExplicitCast(const std::string sourceName, const std::string& targetName, const asSFuncPtr& memberFunc) {
	std::string castDescription = "";
	castDescription += targetName;
	castDescription += "@ ";
	castDescription += "opCast()";
	THROW_ERROR_BINDER(engine->RegisterObjectMethod(sourceName.c_str(), castDescription.c_str(), memberFunc, asCALL_CDECL_OBJFIRST) < 0, "Add Implicit cast failed")
	return *this;
}


visionhub::v1::binder& visionhub::v1::binder::addEnum(const std::string& typeName) {
	THROW_ERROR_BINDER(engine->RegisterEnum(typeName.c_str()) < 0, "Add enum failed")
	return *this;
}

visionhub::v1::binder& visionhub::v1::binder::addEnumValue(const std::string& typeName, const std::string& valueName, int value) {
	THROW_ERROR_BINDER(engine->RegisterEnumValue(typeName.c_str(), valueName.c_str(), value) < 0, "Add enum value failed");
	return *this;
}

visionhub::v1::binder& visionhub::v1::binder::addObjExportFunc(const std::string & typeName, const visionhub::v1::exportObjFunction & exporter) {
	this->exportObjTableInfo.emplace(typeName, exporter);
	return *this;
}

visionhub::v1::binder& visionhub::v1::binder::appendObjExportTable(exportObjTable& table) {
	for (auto& info : this->exportObjTableInfo) {
		table.emplace(info.first, info.second);
	}
	return *this;
}


std::shared_ptr<visionhub::v1::memoryPool> visionhub::v1::binder::globalPool() {
	return this->pool;
}
#pragma endregion
