#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_SNAP_SHOT
#define VISIONHUB_AOI_NATIVE_CORE_SNAP_SHOT

#include "snapFrame.h"
#include "snapEntry.h"

#include <memory>
#include <vector>

namespace visionhub {
	namespace v1 {
		struct impl_snapShot;
		struct snapShot;
		using snapShot_ptr = std::shared_ptr<snapShot>;
		struct snapShot {

#pragma region IMPL
		private:
			std::shared_ptr<impl_snapShot> impl;
			friend struct snapShotAtt;

#pragma endregion

		public:
#pragma region Constructor
			VISIONHUB_AOI_NATIVE_CORE_API snapShot();
#pragma endregion

#pragma region Public Functions
			VISIONHUB_AOI_NATIVE_CORE_API std::vector<snapFrame_ptr> frames();
			VISIONHUB_AOI_NATIVE_CORE_API std::vector<snapEntry_ptr> globals();
			VISIONHUB_AOI_NATIVE_CORE_API void print();
			VISIONHUB_AOI_NATIVE_CORE_API snapShot_ptr clone();
#pragma endregion

			
		};

		struct snapShotAtt {
#pragma region Private Property
		private:
			friend class engine;
			friend class impl_engine;
#pragma endregion

			VISIONHUB_AOI_NATIVE_CORE_API static void addFrame(const snapShot_ptr& snapShot, const snapFrame_ptr& frame);
			VISIONHUB_AOI_NATIVE_CORE_API static void addGlobal(const snapShot_ptr& snapShot, const snapEntry_ptr& entry);
		};
	}
}

#endif