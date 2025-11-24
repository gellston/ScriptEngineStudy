#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_RAII
#define VISIONHUB_AOI_NATIVE_CORE_RAII

#include <functional>

namespace visionhub {
	namespace v1 {
		struct raii {
		private:
			std::function<void()> callback;
		public:

			raii(std::function<void()> callback) {
				this->callback = callback;
			}

			~raii() {
				if (this->callback != nullptr) {
					this->callback();
				}
			}
		};
	}
}




#endif