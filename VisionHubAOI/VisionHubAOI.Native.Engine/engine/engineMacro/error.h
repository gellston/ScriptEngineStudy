#pragma once



#ifndef VISIONHUB_AOI_NATIVE_ENGINE_MACRO
#define VISIONHUB_AOI_NATIVE_ENGINE_MACRO

#include <exception>


#define THROW_ERROR(condition, message) \
if (condition) { \
throw std::exception(message);\
}\


#define OK(condition) \
if (condition < 0) { \
throw std::exception("Error occured");\
}\

#endif