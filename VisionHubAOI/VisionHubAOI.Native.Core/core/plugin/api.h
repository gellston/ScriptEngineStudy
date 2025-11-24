#pragma once

#include "../types/coreVersion.h"
#include "../binding/binder.h"
#include "../binding/binderHelper.h"
#include "../container/memoryPoolContainer.h"


#ifndef VISIONHUB_AOI_NATIVE_PLUGIN_EXPORT
#define VISIONHUB_AOI_NATIVE_PLUGIN_API extern "C" __declspec(dllimport)
#else
#define VISIONHUB_AOI_NATIVE_PLUGIN_API extern "C" __declspec(dllexport)
#endif



#ifdef _DEBUG

#define VISIONHUB_PLUGIN_SANITY_CHECK()\
VISIONHUB_AOI_NATIVE_PLUGIN_API bool sanityCheck(){\
\
return true;\
}\

#else

#define VISIONHUB_PLUGIN_SANITY_CHECK()\
VISIONHUB_AOI_NATIVE_PLUGIN_API bool sanityCheck(){\
\
return false;\
}\

#endif







#define VISIONHUB_PLUGIN(param, pMajor, pMinor, pPatch)\
int pluginInitIMPL(visionhub::v1::binder & param);\
VISIONHUB_PLUGIN_SANITY_CHECK()\
VISIONHUB_AOI_NATIVE_PLUGIN_API int coreMajorVersion() { return visionhub::v1::coreVersion::major;}\
VISIONHUB_AOI_NATIVE_PLUGIN_API int coreMinorVersion() { return visionhub::v1::coreVersion::minor;}\
VISIONHUB_AOI_NATIVE_PLUGIN_API int corePatchVersion() { return visionhub::v1::coreVersion::patch;}\
VISIONHUB_AOI_NATIVE_PLUGIN_API int pluginMajorVersion() { return pMajor;}\
VISIONHUB_AOI_NATIVE_PLUGIN_API int pluginMinorVersion() { return pMinor;}\
VISIONHUB_AOI_NATIVE_PLUGIN_API int pluginPatchVersion() { return pPatch;}\
VISIONHUB_AOI_NATIVE_PLUGIN_API int pluginInit(visionhub::v1::binder & param){\
	visionhub::v1::memoryPoolContainer::set(param.globalPool());\
	return pluginInitIMPL(param);\
}\
int pluginInitIMPL(visionhub::v1::binder & param)\





#define PLUGIN_ERROR 1
#define PLUGIN_OK 0 



