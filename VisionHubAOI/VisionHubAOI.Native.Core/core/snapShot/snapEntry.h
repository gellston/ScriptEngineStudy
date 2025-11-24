#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_SNAP_ENTRY
#define VISIONHUB_AOI_NATIVE_CORE_SNAP_ENTRY

#include "../coreMacro/api.h"

#include "snapValue.h"

#include <memory>
#include <string>

namespace visionhub {
	namespace v1{
		struct impl_snapEntry;
		struct snapEntry;
		using snapEntry_ptr = std::shared_ptr<snapEntry>;
		struct snapEntry {

#pragma region IMPL
		private:
			friend struct snapEntryAtt;
			std::shared_ptr<impl_snapEntry> impl;
#pragma endregion

#pragma region Constructor
		public:
			VISIONHUB_AOI_NATIVE_CORE_API snapEntry();
#pragma endregion

#pragma region Public Functions
			VISIONHUB_AOI_NATIVE_CORE_API void print(int intent);
			VISIONHUB_AOI_NATIVE_CORE_API snapEntry_ptr clone();

			VISIONHUB_AOI_NATIVE_CORE_API std::string name();
			VISIONHUB_AOI_NATIVE_CORE_API snapValue_ptr value();
#pragma endregion
		};



		struct snapEntryAtt {

#pragma region Private Property
		private:
			friend class engine;
			friend class impl_engine;
#pragma endregion

#pragma region Public Functions
			VISIONHUB_AOI_NATIVE_CORE_API static void setName(const snapEntry_ptr& e, const std::string & name);
			VISIONHUB_AOI_NATIVE_CORE_API static void setValue(const snapEntry_ptr& e, const snapValue_ptr& value);
#pragma endregion


		};
	}
}

#endif