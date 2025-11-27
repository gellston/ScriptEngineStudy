#pragma once

#ifndef VISIONHUB_AOI_MANAGED_ENGINE
#define VISIONHUB_AOI_MANAGED_ENGINE


//C++
#include <engine/engine.h>
#include <string>


//C++/CLI



//C#
using namespace System::Collections::Generic;

namespace VisionHub {
	namespace V1 {

		using PluginInfo = System::Tuple<int, int, int, System::String^>;
		using TraceMessage = System::Tuple<VisionHub::V1::TraceType, int, int, System::String^, System::String^>;


		public ref class Engine {
		private:
#pragma region Private Property
			visionhub::v1::engine_ptr* engine = new visionhub::v1::engine_ptr();
			bool disposing = false;

			delegate void LineCallbackDelegate(int, int, std::string);
			delegate void TraceCallbackDelegate(visionhub::v1::traceType, int, int, std::string, std::string);
			delegate void SnapShotCallbackDelegate(visionhub::v1::snapShot_ptr);


			LineCallbackDelegate^ OnLineCallbackDelegate;
			TraceCallbackDelegate^ OnTraceCallbackDelegate;
			SnapShotCallbackDelegate^ OnSnapShotCallbackDelegate;


			Engine(visionhub::v1::engine_ptr & engine);
#pragma endregion

#pragma region Constructor
		public:
		
#pragma endregion

#pragma region Destructor
			~Engine();
#pragma endregion

#pragma region Finalizer
			!Engine();
#pragma endregion

#pragma region Private Functions
		private:
			void Cleanup(bool finalizing);

			void OnLineCallback(int, int, std::string);
			void OnTraceCallback(visionhub::v1::traceType, int, int, std::string, std::string);
			void OnSnapShotCallback(visionhub::v1::snapShot_ptr);
#pragma endregion


#pragma region Static Functions
		public:
			static Engine^ Create();
#pragma endregion


#pragma region Public Property
			property List<PluginInfo^>^ Plugins{
				List<PluginInfo^>^ get();
			}

			property VisionHub::V1::ExecMode Mode {
				void set(VisionHub::V1::ExecMode mode);
			}
#pragma endregion



#pragma region Public Functions
		public:
			void AddLibrary(... array<System::String^>^ names);
			void LoadPlugin(System::String^ Path);
			void LoadScript(System::String^ scriptName, System::String^ content);
			void LoadScript(System::String^ path);

			void Compile(System::String^ scriptName, System::String^ content);
			void Compile(System::String^ path);
			void Compile();

			void Setup();
			void Run();
			void ShutDown();
			void GC();
			void Abort();


			void Argument(VisionHub::V1::Value^ data);
			VisionHub::V1::Value^ Output();
			void ResetOutput();

			
			void StoreLogs(bool enable);
			Queue<TraceMessage^>^ GetLogs();
			void SetMaxLog(unsigned long long count);
			void ClearLogs();
		

			void MarkBreakPoint(int lineNumber);
			void EraseBreakPoint(int lineNumber);
			void EraseAllBreakPoints();

#pragma endregion


#pragma region Event
			event System::Action<int, int, System::String^>^ LineEvent;
			event System::Action<VisionHub::V1::TraceType, int, int, System::String^, System::String^>^ TraceEvent;
			event System::Action<VisionHub::V1::SnapShot^>^ SnapShotEvent;
#pragma endregion



		};
	}
}





#endif