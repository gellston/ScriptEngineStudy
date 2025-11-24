#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_RAII2
#define VISIONHUB_AOI_NATIVE_CORE_RAII2

#include <functional>

namespace visionhub {
	namespace v1 {
		struct raii2 {
		private:
			std::function<void()> finalizer;
		public:

			raii2(std::function<void()> starter, std::function<void()> finalizer) {
				starter();
				this->finalizer = finalizer;
			}

			~raii2() {
				if (this->finalizer != nullptr) {
					this->finalizer();
				}
			}
		};
	}
}




#endif