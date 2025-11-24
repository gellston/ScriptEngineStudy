/**

    @file      engine.h
    @brief     script engine의 컴파일, 빌드, 디버깅 및 script와의 상호작용을 담당 
    @details   ~
    @author    구봉회
    @date      24.11.2025
    @copyright © HyVISION, 2025. All right reserved.

**/
#pragma once

#pragma once




#ifndef VISIONHUB_AOI_NATIVE_ENGINE
#define VISIONHUB_AOI_NATIVE_ENGINE

#include "engineMacro/api.h"

#include "iengine.h"
#include <core/types/traceType.h>
#include <core/types/execMode.h>
#include <core/snapShot/snapShot.h>
#include <core/collection/value.h>

#include <memory>
#include <string>
#include <vector>
#include <deque>
#include <functional>



namespace visionhub {
	namespace v1 {

		using traceCallback = std::function<void(visionhub::v1::traceType, int, int, std::string, std::string)>;
		using traceMessage = std::tuple<visionhub::v1::traceType, int, int, std::string, std::string>;
		using lineCallback = std::function<void(int, int, std::string)>;
		using pluginInfo = std::tuple<int, int, int, std::string>;
		using snapShotCallback = std::function<void(visionhub::v1::snapShot_ptr)>;

#pragma region Impl
		class impl_engine;
#pragma endregion

		class engine : visionhub::v1::iengine{

		private:
#pragma region Private Property
			std::unique_ptr<impl_engine> impl;
#pragma endregion

#pragma region Private Functions
			void loadInternals();
#pragma endregion

#pragma region Constructor

			VISIONHUB_AOI_NATIVE_ENGINE_API engine();
#pragma endregion

		public:
#pragma region Delete Copy and Move
			VISIONHUB_AOI_NATIVE_ENGINE_API engine(const engine&) = delete;
			VISIONHUB_AOI_NATIVE_ENGINE_API engine& operator=(const engine&) = delete;
			VISIONHUB_AOI_NATIVE_ENGINE_API engine(engine&&) = delete;
			VISIONHUB_AOI_NATIVE_ENGINE_API engine& operator=(engine&&) = delete;
#pragma endregion

#pragma region Destructor
			VISIONHUB_AOI_NATIVE_ENGINE_API virtual ~engine();
#pragma endregion

#pragma region Factory

			VISIONHUB_AOI_NATIVE_ENGINE_API static std::shared_ptr<engine> create();
#pragma endregion


#pragma region Public Functions



			VISIONHUB_AOI_NATIVE_ENGINE_API std::vector<pluginInfo> plugins();


			VISIONHUB_AOI_NATIVE_ENGINE_API void addLibrary(std::vector<std::string> names);
			VISIONHUB_AOI_NATIVE_ENGINE_API void loadLibrary(std::string path);
			VISIONHUB_AOI_NATIVE_ENGINE_API void loadScript(std::string scriptName, std::string content);
			VISIONHUB_AOI_NATIVE_ENGINE_API void compile();


			//run
			VISIONHUB_AOI_NATIVE_ENGINE_API void mode(visionhub::v1::execMode mode);
			VISIONHUB_AOI_NATIVE_ENGINE_API void setup();
			VISIONHUB_AOI_NATIVE_ENGINE_API void run();
			VISIONHUB_AOI_NATIVE_ENGINE_API void shutdown();
			VISIONHUB_AOI_NATIVE_ENGINE_API void gc();
			VISIONHUB_AOI_NATIVE_ENGINE_API void abort();


			//collection
			VISIONHUB_AOI_NATIVE_ENGINE_API void argument(visionhub::v1::sharedValue data);
			VISIONHUB_AOI_NATIVE_ENGINE_API visionhub::v1::sharedValue output();
			VISIONHUB_AOI_NATIVE_ENGINE_API void resetOutput();

			//Logs
			VISIONHUB_AOI_NATIVE_ENGINE_API void storeLogs(bool enable);
			VISIONHUB_AOI_NATIVE_ENGINE_API std::deque<traceMessage> & getLogs();
			VISIONHUB_AOI_NATIVE_ENGINE_API void clearLogs();
			VISIONHUB_AOI_NATIVE_ENGINE_API void setMaxLog(std::size_t count);


			//Break point
			VISIONHUB_AOI_NATIVE_ENGINE_API void markBreakPoint(int lineNumber);
			VISIONHUB_AOI_NATIVE_ENGINE_API void eraseBreakPoint(int lineNumber);
			VISIONHUB_AOI_NATIVE_ENGINE_API void eraseAllBreakPoints();

			//Event
			VISIONHUB_AOI_NATIVE_ENGINE_API void setTraceCallback(visionhub::v1::traceCallback callback);
			VISIONHUB_AOI_NATIVE_ENGINE_API visionhub::v1::traceCallback& getTraceCallback();

			VISIONHUB_AOI_NATIVE_ENGINE_API void setLineCallback(visionhub::v1::lineCallback callback);
			VISIONHUB_AOI_NATIVE_ENGINE_API visionhub::v1::lineCallback& getLineCallback();

			VISIONHUB_AOI_NATIVE_ENGINE_API void setSnapshotCallback(visionhub::v1::snapShotCallback callback);
			VISIONHUB_AOI_NATIVE_ENGINE_API visionhub::v1::snapShotCallback& getSnapShotCallback();
#pragma endregion



		};
	}
}

#endif