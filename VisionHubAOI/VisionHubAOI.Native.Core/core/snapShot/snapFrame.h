#pragma once



#ifndef VISIONHUB_AOI_NATIVE_CORE_SNAP_FRAME
#define VISIONHUB_AOI_NATIVE_CORE_SNAP_FRAME


#include "snapEntry.h"


#include <optional>
#include <vector>
#include <string>

namespace visionhub {
	namespace v1 {
		class engine;
		class impl_engine;

		struct snapFrame;
		using snapFrame_ptr = std::shared_ptr<snapFrame>;
		struct impl_snapFrame;

		struct impl_snapValue;
		struct snapFrame {

#pragma region IMPL
		private:
			std::shared_ptr<impl_snapFrame> impl;
			friend struct snapFrameAtt;
#pragma endregion

#pragma region Constructor
		public:
			VISIONHUB_AOI_NATIVE_CORE_API snapFrame();
#pragma endregion

#pragma region Public Functions
			VISIONHUB_AOI_NATIVE_CORE_API void print(int intent);
			VISIONHUB_AOI_NATIVE_CORE_API std::vector<snapEntry_ptr> locals();
			VISIONHUB_AOI_NATIVE_CORE_API std::optional<snapEntry_ptr> thisObj();
			VISIONHUB_AOI_NATIVE_CORE_API int column();
			VISIONHUB_AOI_NATIVE_CORE_API int line();
			VISIONHUB_AOI_NATIVE_CORE_API std::string section();
			VISIONHUB_AOI_NATIVE_CORE_API std::string functionName();
#pragma endregion

		};

		
#pragma region Snap Frame Attorney
		struct snapFrameAtt {


#pragma region Private Property
		private:
			friend struct snapframe;
			friend class engine;
			friend class impl_engine;
#pragma endregion



#pragma region Public Functions
			VISIONHUB_AOI_NATIVE_CORE_API static void setColumn(const snapFrame_ptr& frame, int column);
			VISIONHUB_AOI_NATIVE_CORE_API static void setLine(const snapFrame_ptr& frame, int line);
			VISIONHUB_AOI_NATIVE_CORE_API static void setSection(const snapFrame_ptr& frame, const std::string & section);
			VISIONHUB_AOI_NATIVE_CORE_API static void setFuncName(const snapFrame_ptr& frame, const std::string & name);
			VISIONHUB_AOI_NATIVE_CORE_API static void setThisObj(const snapFrame_ptr& frame, const snapEntry_ptr & entry);
			VISIONHUB_AOI_NATIVE_CORE_API static void addLocals(const snapFrame_ptr& frame, const snapEntry_ptr& local);
#pragma endregion



		};
#pragma endregion


	}
}

#endif