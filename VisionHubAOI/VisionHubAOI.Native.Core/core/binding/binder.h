#pragma once

#ifndef VISIONHUB_AOI_NATIVE_CORE_BINDER
#define VISIONHUB_AOI_NATIVE_CORE_BINDER

#include <string>
#include <functional>
#include <unordered_map>


#include "../types/runtime.h"
#include "../coreMacro/api.h"

class asIScriptEngine;
struct asSFuncPtr;

namespace visionhub {
	namespace v1 {
		
		struct object;
		using object_ptr = std::shared_ptr<object>;
		using exportObjFunction = std::function<object_ptr(void*)>;
		using exportObjTable = std::unordered_map<std::string, exportObjFunction>;

		class memoryPool;

		struct binder
		{
#pragma region Private Property
		private:
			asIScriptEngine* engine = nullptr;
			exportObjTable exportObjTableInfo;
			std::shared_ptr<memoryPool> pool;
#pragma endregion

		public:

#pragma region Constructor
			VISIONHUB_AOI_NATIVE_CORE_API binder(visionhub::v1::runtime runtime, std::shared_ptr<memoryPool> pool);
#pragma endregion

#pragma region Public Functions
			VISIONHUB_AOI_NATIVE_CORE_API std::shared_ptr<memoryPool> globalPool();
			VISIONHUB_AOI_NATIVE_CORE_API binder& nameSpace(const std::string& name);
			VISIONHUB_AOI_NATIVE_CORE_API binder& addObject(const std::string& typeName);
			VISIONHUB_AOI_NATIVE_CORE_API binder& addGlobalFunction(const std::string& decl, const asSFuncPtr& memberFunc, void* thisPtr);
			VISIONHUB_AOI_NATIVE_CORE_API binder& addGlobalFunction(const std::string& decl, const asSFuncPtr& function);
			VISIONHUB_AOI_NATIVE_CORE_API binder& addFactory(const std::string typeName, const std::string& decl, const asSFuncPtr& function);
			VISIONHUB_AOI_NATIVE_CORE_API binder& addProperty(const std::string typeName, const std::string& decl, const int byteoffset);
			VISIONHUB_AOI_NATIVE_CORE_API binder& addMethod(const std::string typeName, const std::string& decl, const asSFuncPtr& memberFunc);
			VISIONHUB_AOI_NATIVE_CORE_API binder& addRef(const std::string typeName, const asSFuncPtr& memberFunc);
			VISIONHUB_AOI_NATIVE_CORE_API binder& addRelease(const std::string typeName, const asSFuncPtr& memberFunc);
			VISIONHUB_AOI_NATIVE_CORE_API binder& addImplicitCast(const std::string sourceName, const std::string& targetName, const asSFuncPtr& memberFunc);
			VISIONHUB_AOI_NATIVE_CORE_API binder& addExplicitCast(const std::string sourceName, const std::string& targetName, const asSFuncPtr& memberFunc);
			VISIONHUB_AOI_NATIVE_CORE_API binder& addEnum(const std::string& typeName);
			VISIONHUB_AOI_NATIVE_CORE_API binder& addEnumValue(const std::string& typeName, const std::string& valueName, int value);
			VISIONHUB_AOI_NATIVE_CORE_API binder& addObjExportFunc(const std::string& typeName, const exportObjFunction& exporter);
			VISIONHUB_AOI_NATIVE_CORE_API binder& appendObjExportTable(exportObjTable& table);
#pragma endregion

		};
	}
}


#endif