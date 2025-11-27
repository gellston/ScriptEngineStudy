//C++
#include <msclr/marshal_cppstd.h>


//C++/CLI
#include "Engine/Engine.h"


//C#

using namespace System::Runtime::InteropServices;


#pragma region Constructor
VisionHub::V1::Engine::Engine(visionhub::v1::engine_ptr& engine) {
	*this->engine = engine;


	this->OnLineCallbackDelegate = gcnew VisionHub::V1::Engine::LineCallbackDelegate(this, &VisionHub::V1::Engine::OnLineCallback);
	this->OnTraceCallbackDelegate = gcnew VisionHub::V1::Engine::TraceCallbackDelegate(this, &VisionHub::V1::Engine::OnTraceCallback);
	this->OnSnapShotCallbackDelegate = gcnew VisionHub::V1::Engine::SnapShotCallbackDelegate(this, &VisionHub::V1::Engine::OnSnapShotCallback);


	auto OnLineCallbackDelegatePointer = (void (*)(int, int, std::string))Marshal::GetFunctionPointerForDelegate(this->OnLineCallbackDelegate).ToPointer();
	auto OnTraceCallbackDelegatePointer = (void (*)(visionhub::v1::traceType, int, int, std::string, std::string))Marshal::GetFunctionPointerForDelegate(this->OnTraceCallbackDelegate).ToPointer();
	auto OnSnapShotCallbackDelegatePointer = (void (*)(visionhub::v1::snapShot_ptr)) Marshal::GetFunctionPointerForDelegate(OnSnapShotCallbackDelegate).ToPointer();


	this->engine->get()->setLineCallback(OnLineCallbackDelegatePointer);
	this->engine->get()->setTraceCallback(OnTraceCallbackDelegatePointer);
	this->engine->get()->setSnapshotCallback(OnSnapShotCallbackDelegatePointer);

	
}
#pragma endregion


#pragma region Destructor
VisionHub::V1::Engine::~Engine() {
	this->Cleanup(false);
}
#pragma endregion


#pragma region Finalizer
VisionHub::V1::Engine::!Engine() {
	this->Cleanup(true);
}
#pragma endregion


#pragma region Private Functions
void VisionHub::V1::Engine::Cleanup(bool finalizing) {

	if (this->disposing == true) return;
	this->disposing = true;


	if (!finalizing) {
		//Managed Resource Clean Up
	}



	if (this->engine != nullptr) {
		delete this->engine;
		this->engine = nullptr;
	}

}

void VisionHub::V1::Engine::OnLineCallback(int column, int row, std::string message) {

	this->LineEvent(
		column, 
		row, 
		msclr::interop::marshal_as<System::String^>(message)
	);
}

void VisionHub::V1::Engine::OnTraceCallback(visionhub::v1::traceType type, int column, int row, std::string section, std::string message) {

	this->TraceEvent(
		safe_cast<VisionHub::V1::TraceType>(type),
		column,
		row,
		msclr::interop::marshal_as<System::String^>(section),
		msclr::interop::marshal_as<System::String^>(message)
	);
}

void VisionHub::V1::Engine::OnSnapShotCallback(visionhub::v1::snapShot_ptr snapShot) {

	try {

		auto managedSnapShot = gcnew VisionHub::V1::SnapShot(System::IntPtr(&snapShot));
		this->SnapShotEvent(managedSnapShot);
	}
	catch (...) {

	}

}
#pragma endregion


#pragma region Static Functions
VisionHub::V1::Engine^ VisionHub::V1::Engine::Create() {
	try {
		return gcnew VisionHub::V1::Engine(visionhub::v1::engine::create());
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}
#pragma endregion


#pragma region Public Property
List<VisionHub::V1::PluginInfo^>^ VisionHub::V1::Engine::Plugins::get() {

	try {
		List<VisionHub::V1::PluginInfo^>^ temp = gcnew List<VisionHub::V1::PluginInfo^>();

		auto& plugins = this->engine->get()->plugins();
		for (auto& plugin : plugins) {
			auto& major = std::get<0>(plugin);
			auto& minor = std::get<1>(plugin);
			auto& patch = std::get<2>(plugin);
			auto& name = std::get<3>(plugin);
			temp->Add(gcnew VisionHub::V1::PluginInfo(major, minor, patch, msclr::interop::marshal_as<System::String^>(name)));
		}

		return temp;
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}

void VisionHub::V1::Engine::Mode::set(VisionHub::V1::ExecMode mode) {
	try {
		auto nativeMode = safe_cast<visionhub::v1::execMode>(mode);

		this->engine->get()->mode(nativeMode);
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}
#pragma endregion

#pragma region Public Functions
void VisionHub::V1::Engine::AddLibrary(... array<System::String^>^ names) {

	try {

		std::vector<std::string> nativeNames;

		for (int index = 0; index < names->Length; index++) {
			auto name = names[index];
			nativeNames.push_back(msclr::interop::marshal_as<std::string>(name));
		}

		this->engine->get()->addLibrary(nativeNames);
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}

}

void VisionHub::V1::Engine::LoadPlugin(System::String^ path) {
	try {

		this->engine->get()->loadPlugin(msclr::interop::marshal_as<std::string>(path));

	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}

void VisionHub::V1::Engine::LoadScript(System::String^ scriptName, System::String^ content) {
	try {

		auto nativeScriptName = msclr::interop::marshal_as<std::string>(scriptName);
		auto nativeContent = msclr::interop::marshal_as<std::string>(content);

		this->engine->get()->loadScript(nativeScriptName, nativeContent);

	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}

void VisionHub::V1::Engine::LoadScript(System::String^ path) {
	try {

		auto nativeScriptName = msclr::interop::marshal_as<std::string>(path);
		

		this->engine->get()->loadScript(nativeScriptName);

	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}


void VisionHub::V1::Engine::Compile(System::String^ scriptName, System::String^ content) {
	try {

		auto nativeScriptName = msclr::interop::marshal_as<std::string>(scriptName);
		auto nativeContent = msclr::interop::marshal_as<std::string>(content);

		this->engine->get()->compile(nativeScriptName, nativeContent);

	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}

void VisionHub::V1::Engine::Compile(System::String^ path) {
	try {

		auto managedPath = msclr::interop::marshal_as<std::string>(path);

		this->engine->get()->compile(managedPath);

	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}

void VisionHub::V1::Engine::Compile() {
	try {

		this->engine->get()->compile();

	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}



void VisionHub::V1::Engine::Setup() {
	try {

		this->engine->get()->setup();

	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}

void VisionHub::V1::Engine::Run() {
	try {

		this->engine->get()->run();

	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}

void VisionHub::V1::Engine::ShutDown() {
	try {

		this->engine->get()->shutdown();

	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}

void VisionHub::V1::Engine::GC() {
	try {

		this->engine->get()->gc();

	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}

void VisionHub::V1::Engine::Abort() {
	try {

		this->engine->get()->abort();

	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}



void VisionHub::V1::Engine::Argument(VisionHub::V1::Value^ data) {
	try {

		auto nativeValue = *((visionhub::v1::value_ptr *)data->Handle.ToPointer());
		this->engine->get()->argument(nativeValue);
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}

VisionHub::V1::Value^ VisionHub::V1::Engine::Output() {
	try {


		auto nativeValue = this->engine->get()->output();
		auto handle = System::IntPtr(&nativeValue);
		return gcnew VisionHub::V1::Value(handle);
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}

void VisionHub::V1::Engine::ResetOutput() {
	try {


		this->engine->get()->resetOutput();


	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}



void VisionHub::V1::Engine::StoreLogs(bool enable) {
	try {
		this->engine->get()->storeLogs(enable);
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}

Queue<VisionHub::V1::TraceMessage^>^ VisionHub::V1::Engine::GetLogs() {


	try {
		Queue<VisionHub::V1::TraceMessage^>^ temp = gcnew Queue<VisionHub::V1::TraceMessage^>();


		auto logs = this->engine->get()->getLogs();
		std::deque<visionhub::v1::traceMessage> copyLogs = logs;


		while (!copyLogs.empty()) {
			auto& message = copyLogs.front();
			copyLogs.pop_front();

			//type, row, col, section, message
			auto & type = std::get<0>(message);
			auto & row = std::get<1>(message);
			auto & col = std::get<2>(message);
			auto & section = std::get<3>(message);
			auto & _message = std::get<4>(message);

			temp->Enqueue(gcnew VisionHub::V1::TraceMessage(
				safe_cast<VisionHub::V1::TraceType>(type),
				row,
				col,
				msclr::interop::marshal_as<System::String^>(section),
				msclr::interop::marshal_as<System::String^>(_message)
			));
		}

		return temp;
	}
	catch (std::exception ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}

}

void VisionHub::V1::Engine::SetMaxLog(unsigned long long count) {
	this->engine->get()->setMaxLog(count);
}

void VisionHub::V1::Engine::ClearLogs() {
	this->engine->get()->clearLogs();
}



void VisionHub::V1::Engine::MarkBreakPoint(int lineNumber) {
	this->engine->get()->markBreakPoint(lineNumber);
}

void VisionHub::V1::Engine::EraseBreakPoint(int lineNumber) {
	this->engine->get()->eraseBreakPoint(lineNumber);
}

void VisionHub::V1::Engine::EraseAllBreakPoints() {
	this->engine->get()->eraseAllBreakPoints();
}
#pragma endregion
