#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_BINDING_HELPER
#define VISIONHUB_AOI_NATIVE_CORE_BINDING_HELPER

#include <atomic>
#include <memory>

namespace visionhub {
	namespace v1 {
		template <class T>
		using sp = std::shared_ptr<T>;
	}
}

#endif