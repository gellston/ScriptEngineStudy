#include "engine/engine.h"


#include "engine/engineMacro/error.h"
#include "engine/engineException/suspendException.h"
#include "engine/engineException/execException.h"
#include "engine/engineException/abortException.h"


//Facade
#include "engine/facade/facadeEngine.h"


//Adapter
#include "engine/adapter/var.h"

//Helper
#include "engine/helper/helper_vector.h"
#include "engine/helper/helper_smart_ptr.h"
#include "engine/helper/helper_value.h"
#include "engine/helper/helper_stack.h"
#include "engine/helper/helper_queue.h"

#include <core/types/runtime.h>
#include <core/types/execMode.h>
#include <core/binding/binder.h>
#include <core/binding/binderHelper.h>

//Default Datas
#include <core/object.h>
#include <core/rect.h>
#include <core/image.h>
#include <core/test.h>
#include <core/types/colorType.h>
#include <core/types/coreVersion.h>


//SnapShot
#include <core/snapShot/snapValue.h>
#include <core/snapShot/snapShot.h>



//Collection
#include <core/collection/raii.h>


#include <mutex>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <deque>
#include <filesystem>
#include <Windows.h>


#include <angelscript.h>
#include <angelscript/scriptstdstring/scriptstdstring.h>
#include <angelscript/scriptarray/scriptarray.h>
#include <angelscript/scriptdictionary/scriptdictionary.h>
#include <angelscript/scripthelper/scripthelper.h>




#pragma region Impl

namespace visionhub {
	namespace v1 {
		class impl_engine {

#pragma region Private Property
		public:

			std::mutex script_lock;
		

			asIScriptEngine* engine = nullptr;
			asIScriptModule* script_module = nullptr;
			asIScriptFunction* func_run = nullptr;
			asIScriptFunction* func_setup = nullptr;
			asIScriptFunction* func_shutdown = nullptr;

			asIScriptContext* ctx = nullptr;

			bool libraryLoaded = false;
			bool enableStoreLog = false;
			std::string script_content = "";
			std::string script_name = "";
			std::unordered_set<int> breakPointLines;
			visionhub::v1::execMode execMode = visionhub::v1::execMode::run;
			

			std::deque<visionhub::v1::traceMessage> logs;
			std::size_t maxLogCount = 1000;
			bool drainCompileLog = false;
			std::string compileLogs = "";
			visionhub::v1::traceCallback traceCallback = nullptr;



			visionhub::v1::lineCallback lineCallbackLD = nullptr;

			//Facade
			std::unique_ptr<facadeEngine> facadeEngine;


			//exportTable
			exportObjTable exportObjTableInfo;
			visionhub::v1::snapShotCallback snapShotCallback = nullptr;


			//plugins
			std::string pluginPath = "";
			std::vector<visionhub::v1::pluginInfo> plugins;
			std::vector<void*> modules;
			std::unordered_set<std::string> pluginNames;



#pragma endregion

			
#pragma region Public Constructor
		public:
			impl_engine() : facadeEngine(new visionhub::v1::facadeEngine()) {
				try {

					this->engine = asCreateScriptEngine();
					if (this->engine == nullptr) {
						throw std::exception("Invalid engine pointer");
					}

					this->engine->SetTranslateAppExceptionCallback(asMETHOD(impl_engine, translateException), this, asCALL_THISCALL);
					this->engine->SetMessageCallback(asMETHOD(impl_engine, messageCallback), this, asCALL_THISCALL);

					RegisterStdString(this->engine);
					RegisterScriptArray(this->engine, true);
					RegisterScriptDictionary(this->engine);
					RegisterExceptionRoutines(this->engine);



				}
				catch (std::exception ex) {
					throw;
				}
			}
#pragma endregion

#pragma region Public Destructor
			~impl_engine() {

				if (ctx) {
					ctx->Release();
					ctx = nullptr;
				}

				if (this->engine != nullptr) {
					this->engine->ShutDownAndRelease();
				}
			}
#pragma endregion


#pragma region SnapShot Functions
			std::shared_ptr<visionhub::v1::snapValue> capturePrim(int typeId, void* addr) {
				auto v = std::make_shared<snapValue>();
				using namespace visionhub::v1;
				switch (typeId)
				{
				case asTYPEID_BOOL: {snapValueAtt::setValue(v, *reinterpret_cast<bool*>(addr));return v;}
				case asTYPEID_INT8: {snapValueAtt::setValue(v, *reinterpret_cast<int8_t*>(addr));return v;}
				case asTYPEID_INT16: {snapValueAtt::setValue(v, *reinterpret_cast<int16_t*>(addr));return v;}
				case asTYPEID_INT32: {snapValueAtt::setValue(v, *reinterpret_cast<int32_t*>(addr)); return v;}
				case asTYPEID_INT64: { snapValueAtt::setValue(v, *reinterpret_cast<int64_t*>(addr)); return v; }
				case asTYPEID_UINT8: { snapValueAtt::setValue(v, *reinterpret_cast<uint8_t*>(addr)); return v; }
				case asTYPEID_UINT16: { snapValueAtt::setValue(v, *reinterpret_cast<uint16_t*>(addr)); return v; }
				case asTYPEID_UINT32: { snapValueAtt::setValue(v, *reinterpret_cast<uint32_t*>(addr)); return v; }
				case asTYPEID_UINT64: { snapValueAtt::setValue(v, *reinterpret_cast<uint64_t*>(addr)); return v; }
				case asTYPEID_FLOAT: { snapValueAtt::setValue(v, *reinterpret_cast<float*>(addr)); return v; }
				case asTYPEID_DOUBLE: { snapValueAtt::setValue(v, *reinterpret_cast<double*>(addr)); return v; }
				}
				return nullptr;
			}

			snapValue_ptr captureValue(asIScriptEngine* eng, 
										 int typeId, void* addr, 
										 exportObjTable& exporters, 
										 std::unordered_set<uintptr_t>& seen)
			{
				auto makeUnk = [&](const char* tname) {
					auto v = std::make_shared<visionhub::v1::snapValue>();
					auto kind = visionhub::v1::snapKind::_unidentified_;
					auto type = tname ? tname : "<unknown>";
					visionhub::v1::snapValueAtt::setKind(v, kind);
					visionhub::v1::snapValueAtt::setType(v, type);
					return v;
				};

				if (!addr) { 
					auto v = std::make_shared<visionhub::v1::snapValue>(); 
					snapValueAtt::setKind(v, visionhub::v1::snapKind::_null_); 
					return v; 
				}

				// 핸들 역참조
				if (typeId & asTYPEID_OBJHANDLE) {
					void* obj = *reinterpret_cast<void**>(addr);
					return captureValue(eng, typeId & ~asTYPEID_OBJHANDLE, obj, exporters, seen);
				}

				// 프리미티브
				if (!(typeId & asTYPEID_MASK_OBJECT)) {
					if (auto v = capturePrim(typeId, addr)) 
						return v;
					return makeUnk("<primitive>");
				}

				asITypeInfo* ti = eng->GetTypeInfoById(typeId);
				const char* tname = ti ? ti->GetName() : "<unknown>";

				// 사이클 방지
				uintptr_t key = (uintptr_t)addr ^ ((uintptr_t)typeId << 1);
				if (!seen.insert(key).second) return makeUnk(tname);

				// string (scriptstdstring)
				if (std::strcmp(tname, "string") == 0) {
					auto v = std::make_shared<visionhub::v1::snapValue>();
					snapValueAtt::setValue(v, *reinterpret_cast<std::string*>(addr));
					return v;
				}

				// array<T>
				if (std::strcmp(tname, "array") == 0) {
					auto* arr = reinterpret_cast<CScriptArray*>(addr);
					auto v = std::make_shared<visionhub::v1::snapValue>();

					snapValueAtt::setKind(v, snapKind::_array_);
					snapValueAtt::setType(v, "array");

					asITypeInfo* sub = arr->GetArrayObjectType()->GetSubType();
					int subId = sub->GetTypeId();
					for (asUINT i = 0; i < arr->GetSize(); ++i) {
						void* elem = arr->At(i);
						auto value = captureValue(eng, subId, elem, exporters, seen);
						snapValueAtt::addElement(v, value);
					}
					return v;
				}

				// dictionary
				if (std::strcmp(tname, "dictionary") == 0) {
					auto* dict = reinterpret_cast<CScriptDictionary*>(addr);
					auto v = std::make_shared<visionhub::v1::snapValue>();

					snapValueAtt::setKind(v, visionhub::v1::snapKind::_map_);
					snapValueAtt::setType(v, "dictionary");

					for (auto it = const_cast<CScriptDictionary*>(dict)->begin(); it != dict->end(); ++it) {
						auto key = it.GetKey();
						int   vid = it.GetTypeId();
						void* vaddr = (void*)it.GetAddressOfValue();   // 내부 참조
						auto value = captureValue(eng, vid, vaddr, exporters, seen);
						snapValueAtt::addField(v, key, value);
					}
					return v;
				}


				// 스크립트 객체
				// ?? 모르것네
				if (ti->GetFlags() & asOBJ_SCRIPT_OBJECT) {
					auto* so = reinterpret_cast<asIScriptObject*>(addr);
					auto v = std::make_shared<visionhub::v1::snapValue>();

					snapValueAtt::setKind(v, visionhub::v1::snapKind::_script_);
					snapValueAtt::setType(v, tname);

					for (asUINT i = 0; i < so->GetPropertyCount(); ++i) {
						const char* pname = so->GetPropertyName(i);
						int pType = so->GetPropertyTypeId(i);
						void* pAddr = so->GetAddressOfProperty(i);
						auto value = captureValue(eng, pType, pAddr, exporters, seen);
						snapValueAtt::addField(v, pname, value);
					}
					return v;
				}

				// 네이티브 타입 → 당신의 object로 복제
				if (auto it = exporters.find(tname); it != exporters.end()) {

					auto obj = it->second(addr);
					if (!obj) {
						auto v = std::make_shared<visionhub::v1::snapValue>();
						snapValueAtt::setKind(v, visionhub::v1::snapKind::_null_);
						snapValueAtt::setType(v, tname);
						return v;
					}

					auto v = obj->snap();   // 내부에서 snap() 포함하도록 구현
					snapValueAtt::setType(v, tname);
					return v;
				}

				return makeUnk(tname);
			}


			visionhub::v1::snapShot_ptr makeSnapshot() {
				
				if (!ctx) return nullptr;

				asEContextState st = ctx->GetState();
				if (st != asEXECUTION_ACTIVE &&
					st != asEXECUTION_SUSPENDED &&
					st != asEXECUTION_EXCEPTION) {
					// FINISHED, PREPARED, UNINITIALIZED, ABORTED 등에서는 캡처 금지
					return nullptr;
				}

				auto* eng = ctx->GetEngine();
				auto shot = std::make_shared<visionhub::v1::snapShot>();

				// 1) 스택 프레임들
				asUINT frames = ctx->GetCallstackSize();
				for (asUINT lvl = 0; lvl < frames; ++lvl) {
					auto f = std::make_shared<visionhub::v1::snapFrame>();
					int col = 0; const char* sec = nullptr;
					auto line = ctx->GetLineNumber(lvl, &col, &sec);
					auto column = col;
					auto section = sec ? sec : "";

					visionhub::v1::snapFrameAtt::setLine(f, line);

					if (auto* fn = ctx->GetFunction(lvl)) {
						auto function = fn->GetDeclaration(true, true, true);
						visionhub::v1::snapFrameAtt::setFuncName(f, function);
					}
	

					std::unordered_set<uintptr_t> seen;

					// this
					if (int thisId = ctx->GetThisTypeId(lvl); thisId != 0) {
						void* thisPtr = ctx->GetThisPointer(lvl);
						auto e = std::make_shared<visionhub::v1::snapEntry>();

						visionhub::v1::snapEntryAtt::setName(e, "this");
						auto value  = this->captureValue(eng, thisId, thisPtr, exportObjTableInfo, seen);
						visionhub::v1::snapEntryAtt::setValue(e, value);
						visionhub::v1::snapFrameAtt::setThisObj(f, e);
					}

					// locals
					int varCount = ctx->GetVarCount(lvl);
					for (int i = 0; i < varCount; ++i) {

						if (!ctx->IsVarInScope(i, lvl)) continue;

						int   vType = 0;
						const char* vName = nullptr;


						if (ctx->GetVar(i, lvl, &vName, &vType) < 0) continue;



						// 선언 문자열로 const 판별(handle - to - const까지 포함)
						const char* vDecl = ctx->GetVarDeclaration(i, lvl, /*includeNamespace*/true);
						std::string decl = vDecl ? vDecl : "";
						std::string name = vName ? vName : "";

						// 1) 이름 없는 임시(temporary) 스킵
						if (name.empty()) continue;

						// 2) const 변수 스킵 (원하면 플래그로 허용)
						bool isConstDecl =
							(decl.rfind("const ", 0) == 0) ||                 // "const int a"
							(decl.find("const @") != std::string::npos) ||    // "const T@"
							(decl.find("@ const") != std::string::npos);      // "T@ const"
						if (isConstDecl) continue;


						// 3) null 핸들 스킵 (원하면 표시)
						void* vAddr = ctx->GetAddressOfVar(i, lvl);
						if ((vType & asTYPEID_OBJHANDLE) != 0) {
							void* obj = *reinterpret_cast<void**>(vAddr);
							if (obj == nullptr) continue;
						}

						// 통과한 것만 캡처
						auto e = std::make_shared<visionhub::v1::snapEntry>();

						visionhub::v1::snapEntryAtt::setName(e, name);
						auto value = this->captureValue(eng, vType, vAddr, exportObjTableInfo, seen);

						visionhub::v1::snapEntryAtt::setValue(e, value);
						visionhub::v1::snapFrameAtt::addLocals(f, e);
					}

					visionhub::v1::snapShotAtt::addFrame(shot, f);
				}

				// 2) 전역 변수(현재 프레임의 모듈을 우선)
				asIScriptModule* mod = nullptr;
				for (asUINT lvl = 0; lvl < frames && !mod; ++lvl) {
					if (auto* fn = ctx->GetFunction(lvl)) mod = fn->GetModule();
				}
				if (!mod) { /* 필요 시 fallback: 이름으로 모듈 찾기 */ }

				if (mod) {
					std::unordered_set<uintptr_t> seenG;
					asUINT gcount = mod->GetGlobalVarCount();
					for (asUINT i = 0; i < gcount; ++i) {
						void* gAddr = mod->GetAddressOfGlobalVar(i);
						int   gType = 0; const char* name = nullptr; const char* ns = nullptr;
						mod->GetGlobalVar(i, &name, &ns, &gType);
						auto e = std::make_shared<visionhub::v1::snapEntry>(); 
						auto fullName = (ns && ns[0] ? std::string(ns) + "::" : std::string{}) + (name && name[0] ? std::string(name) : (std::string("g") + std::to_string(i)));
						auto value = this->captureValue(eng, gType, gAddr, exportObjTableInfo, seenG);

						visionhub::v1::snapEntryAtt::setName(e, fullName);
						visionhub::v1::snapEntryAtt::setValue(e, value);

						visionhub::v1::snapShotAtt::addGlobal(shot, e);
					}
				}

				// 이 시점의 shot을 JSON/바이너리로 직렬화해서 UI로 전달
				return shot;
			}
#pragma endregion


#pragma region Public Functions



			void compileFromSource() {

				THROW_ERROR(this->script_content.empty(), "No script source loaded")

				// 임시 모듈명(기존과 분리해서 실패 시 롤백 쉬움)
				asIScriptModule* tmp = engine->GetModule("engine", asGM_ALWAYS_CREATE);

				int r = tmp->AddScriptSection(this->script_name.c_str(), 
											  this->script_content.c_str(),
											  (unsigned)this->script_content.size());

				THROW_ERROR(r < 0, "Add script section failed");

				drainCompileLog = true;
				compileLogs = "";
				r = tmp->Build();  // 실제 컴파일/링크
				drainCompileLog = false;
				THROW_ERROR(r < 0, compileLogs.c_str())

				// 여기까지 오면 빌드 성공 → 실행 캐시 무효화 후 교체
				invalidateExecCache();

				// 이전 모듈 날리기
				script_module = tmp;
			}

			void bindFunc() {
				if (!this->script_module) {
					// 현 구조에선 compileFromSource()가 script_module을 항상 채워줌.
					// 혹시나를 위해 남겨둠:
					this->script_module = engine->GetModule("engine", asGM_ONLY_IF_EXISTS);
					THROW_ERROR(!this->script_module, "Module : engine not found")
				}

				this->func_run = this->script_module->GetFunctionByDecl("void run()");
				THROW_ERROR(!this->func_run, "Entry not found: void run()")

				this->func_setup = this->script_module->GetFunctionByDecl("void setup()");
				THROW_ERROR(!this->func_setup, "Entry not found: void setup()")

				this->func_shutdown = this->script_module->GetFunctionByDecl("void shutdown()");
				THROW_ERROR(!this->func_shutdown, "Entry not found: void shutdown()")
			}

			void invalidateExecCache() {
				if (ctx) ctx->Unprepare();
				this->func_run = nullptr;
				this->func_shutdown = nullptr;
				this->func_setup = nullptr;
			}

			void ensureContext() {
				if (!ctx) {
					ctx = engine->CreateContext();
					ctx->SetLineCallback(asMETHOD(impl_engine, lineCallback), this, asCALL_THISCALL);
				}
				THROW_ERROR(!ctx, "Failed to create context");
			}
#pragma endregion

#pragma region Callback

			void translateException(asIScriptContext* ctx) {
				try { 
					throw; 
				}
				catch (const std::exception& e) { 
					ctx->SetException(e.what()); 
				}
				catch (...) { 
					ctx->SetException("Unhandled C++ exception"); 
				}
			}


			void lineCallback(asIScriptContext* ctx)
			{
				int col = 0; 
				const char* sec = nullptr;
				int line = ctx->GetLineNumber(0, &col, &sec);
				std::string section(sec);
				
				bool inSection = section == this->script_name;


				visionhub::v1::raii reset([&]() {
					try {
						auto snapShot = this->makeSnapshot();
						
						if (this->snapShotCallback != nullptr && snapShot != nullptr)
							this->snapShotCallback(snapShot);
					}
					catch (...) {

					}
				});


				switch (this->execMode)
				{
				case execMode::stepOnce: {
					this->execMode = execMode::run;
					ctx->Suspend();
					if (this->lineCallbackLD != nullptr)
						this->lineCallbackLD(col, line, section);

					return;
				}


				case execMode::runToBreakPoint:
					if (inSection && this->breakPointLines.count(line) > 0) {
						ctx->Suspend();
						if (this->lineCallbackLD != nullptr)
							this->lineCallbackLD(col, line, section);
					}
					return;

				case execMode::run: {
					return;
				}

				default:
					return;
				}
			}

			void messageCallback(const asSMessageInfo* msg, void* param) {
				const char* t = msg->type == asMSGTYPE_ERROR ? "ERROR" :
								msg->type == asMSGTYPE_WARNING ? "WARN " : "INFO ";


				if (this->traceCallback != nullptr){
					this->traceCallback(
						static_cast<visionhub::v1::traceType>(msg->type),
						msg->row,
						msg->col,
						std::string(msg->section),
						std::string(msg->message)
					);
				}

				if (this->drainCompileLog == true) {
					std::ostringstream oss;
					oss << "[" << t << "] "
						<< (msg->section ? msg->section : "<section>")
						<< "(" << msg->row << "," << msg->col << "): "
						<< (msg->message ? msg->message : "");
					std::string text = oss.str();

					compileLogs += text;
					compileLogs += "\n";
				}

				if (this->enableStoreLog == true) {

					if (logs.size() >= maxLogCount) logs.pop_front();
					this->logs.push_back({
						static_cast<visionhub::v1::traceType>(msg->type),
						msg->row,
						msg->col,
						std::string(msg->section),
						std::string(msg->message)
					});

				}
				

				


			}
#pragma endregion


		};
	}
}

#pragma endregion


#pragma region Constructor
visionhub::v1::engine::engine() : impl(new impl_engine()) {
	
}
#pragma endregion

#pragma region Destructor
visionhub::v1::engine::~engine() {

}
#pragma endregion

#pragma region Private Functions
void visionhub::v1::engine::loadInternals() {

	try {

		visionhub::v1::runtime runtime;
		runtime.engine = this->impl->engine;




		visionhub::v1::binder binder(runtime,
									 this->impl->facadeEngine->globalPool());

		//Type declaration
		binder
			.nameSpace("core")

			.addEnum("depthType")
			.addAutoEnumValue(depthType, bit8)

			.addEnum("colorType")
			.addAutoEnumValue(colorType, color)
			.addAutoEnumValue(colorType, grayscale)

			.addEnum("valueKind")
			.addAutoEnumValue(valueKind, _null_)
			.addAutoEnumValue(valueKind, _bool_)
			.addAutoEnumValue(valueKind, _int8_)
			.addAutoEnumValue(valueKind, _int16_)
			.addAutoEnumValue(valueKind, _int32_)
			.addAutoEnumValue(valueKind, _int64_)
			.addAutoEnumValue(valueKind, _uint8_)
			.addAutoEnumValue(valueKind, _uint16_)
			.addAutoEnumValue(valueKind, _uint32_)
			.addAutoEnumValue(valueKind, _uint64_)
			.addAutoEnumValue(valueKind, _float_)
			.addAutoEnumValue(valueKind, _double_)
			.addAutoEnumValue(valueKind, _string_)
			.addAutoEnumValue(valueKind, _array_)
			.addAutoEnumValue(valueKind, _map_)
			.addAutoEnumValue(valueKind, _blob_)

			.addAutoGlobalMethod2(visionhub::v1::facadeEngine, cout, (const std::string&), void, "void cout(const string &in)", this->impl->facadeEngine.get())

			.addObject("object")
			//.addObject("test")
			.addObject("rect")
			.addObject("image");

			
		//Value Registeration
		RegisterValue(this->impl->engine);

		//Smart pointer Declareation
		RegisterSmartPointer<image>(this->impl->engine, binder,"image");
		RegisterSmartPointer<object>(this->impl->engine, binder, "object");
		RegisterSmartPointer<rect>(this->impl->engine, binder, "rect");
		//RegisterSmartPointer<test>(this->impl->engine, binder, "test");

		RegisterSmartPointerCast<image, object>(this->impl->engine, "image", "object");
		RegisterSmartPointerCast<rect, object>(this->impl->engine, "rect", "object");
		//RegisterSmartPointerCast<test, object>(this->impl->engine, "test", "object");

		//Vector 
		RegisterVector<object_ptr>(this->impl->engine, "object_ptr");
		RegisterVector<image_ptr>(this->impl->engine, "image_ptr");
		RegisterVector<rect_ptr>(this->impl->engine, "rect_ptr");

		RegisterVector<int8_t>(this->impl->engine, "int8");
		RegisterVector<int16_t>(this->impl->engine, "int16");
		RegisterVector<int32_t>(this->impl->engine, "int32");
		RegisterVector<int64_t>(this->impl->engine, "int64");
		RegisterVector<uint8_t>(this->impl->engine, "uint8");
		RegisterVector<uint16_t>(this->impl->engine, "uint16");
		RegisterVector<uint32_t>(this->impl->engine, "uint32");
		RegisterVector<uint64_t>(this->impl->engine, "uint64");
		RegisterVector<float>(this->impl->engine, "float");
		RegisterVector<double>(this->impl->engine, "double");
		RegisterVector<std::string>(this->impl->engine, "string");

		//Stack
		RegisterStack<object_ptr>(this->impl->engine, "object_ptr");
		RegisterStack<image_ptr>(this->impl->engine, "image_ptr");
		RegisterStack<rect_ptr>(this->impl->engine, "rect_ptr");

		RegisterStack<int8_t>(this->impl->engine, "int8");
		RegisterStack<int16_t>(this->impl->engine, "int16");
		RegisterStack<int32_t>(this->impl->engine, "int32");
		RegisterStack<int64_t>(this->impl->engine, "int64");
		RegisterStack<uint8_t>(this->impl->engine, "uint8");
		RegisterStack<uint16_t>(this->impl->engine, "uint16");
		RegisterStack<uint32_t>(this->impl->engine, "uint32");
		RegisterStack<uint64_t>(this->impl->engine, "uint64");
		RegisterStack<float>(this->impl->engine, "float");
		RegisterStack<double>(this->impl->engine, "double");
		RegisterStack<std::string>(this->impl->engine, "string");


		//Queue
		RegisterQueue<object_ptr>(this->impl->engine, "object_ptr");
		RegisterQueue<image_ptr>(this->impl->engine, "image_ptr");
		RegisterQueue<rect_ptr>(this->impl->engine, "rect_ptr");
				
		RegisterQueue<int8_t>(this->impl->engine, "int8");
		RegisterQueue<int16_t>(this->impl->engine, "int16");
		RegisterQueue<int32_t>(this->impl->engine, "int32");
		RegisterQueue<int64_t>(this->impl->engine, "int64");
		RegisterQueue<uint8_t>(this->impl->engine, "uint8");
		RegisterQueue<uint16_t>(this->impl->engine, "uint16");
		RegisterQueue<uint32_t>(this->impl->engine, "uint32");
		RegisterQueue<uint64_t>(this->impl->engine, "uint64");
		RegisterQueue<float>(this->impl->engine, "float");
		RegisterQueue<double>(this->impl->engine, "double");
		RegisterQueue<std::string>(this->impl->engine, "string");


		// Class definition
		binder


			.addAutoGlobalMethod2(visionhub::v1::facadeEngine, argument, (), visionhub::v1::value, "core::value argument()", this->impl->facadeEngine.get())
			.addAutoGlobalMethod2(visionhub::v1::facadeEngine, output, (const visionhub::v1::value & value), void, "void output(const core::value&in)", this->impl->facadeEngine.get())
			.addAutoGlobalMethod2(visionhub::v1::facadeEngine, output, (const std::string& text, const object_ptr & _object), void, "void output(const string&in, const core::object_ptr&in)", this->impl->facadeEngine.get())

			.addAutoGlobalMethod2(visionhub::v1::facadeEngine, make_image, (unsigned int, unsigned int, unsigned int, depthType), image_ptr, "core::image_ptr make_image(uint width, uint height, uint channel, core::depthType depth)", this->impl->facadeEngine.get())
			.addAutoMethod2(image, width, (), unsigned int, "uint width()")
			.addAutoMethod2(image, height, (), unsigned int, "uint height()")
			.addAutoMethod2(image, channel, (), unsigned int, "uint channel()")
			.addAutoMethod2(image, depth, (), visionhub::v1::depthType, "core::depthType depth()")
			.addAutoMethod2(image, size, (), std::size_t, "uint64 size()")
			.addAutoMethod2(image, stride, (), std::size_t, "uint64 stride()")


			.addAutoGlobalFunction2(rect, make_rect, (double, double, double, double), rect_ptr, "core::rect_ptr make_rect(double, double, double, double)")
			.addAutoMethod2(rect, x, (), double, "double x()")
			.addAutoMethod2(rect, x, (double), void, "void x(double)")
			.addAutoMethod2(rect, y, (), double, "double y()")
			.addAutoMethod2(rect, y, (double), void, "void y(double)")
			.addAutoMethod2(rect, width, (), double, "double width()")
			.addAutoMethod2(rect, width, (double), void, "void width(double)")
			.addAutoMethod2(rect, height, (), double, "double height()")
			.addAutoMethod2(rect, height, (double), void, "void height(double)")

			.addAutoGlobalFunction2(test, make_test, (double, double, double, double), test_ptr, "core::test_ptr make_test(double, double, double, double)")
			.addAutoMethod2(test, x, (), double, "double x()")
			.addAutoMethod2(test, x, (double), void, "void x(double)")
			.addAutoMethod2(test, y, (), double, "double y()")
			.addAutoMethod2(test, y, (double), void, "void y(double)")
			.addAutoMethod2(test, width, (), double, "double width()")
			.addAutoMethod2(test, width, (double), void, "void width(double)")
			.addAutoMethod2(test, height, (), double, "double height()")
			.addAutoMethod2(test, get, (), std::vector<test_ptr>, "vector_test_ptr get()")
			.addAutoMethod2(test, height, (double), void, "void height(double)");

			
			

		binder.appendObjExportTable(this->impl->exportObjTableInfo);
			
	










	}
	catch (...) {
		throw;
	}
}


#pragma endregion

#pragma region Factory
std::shared_ptr<visionhub::v1::engine> visionhub::v1::engine::create() {
	try {
		return std::shared_ptr<visionhub::v1::engine>(new visionhub::v1::engine());
	}
	catch (...) {
		throw;
	}
}
#pragma endregion



#pragma region Public Functions

void visionhub::v1::engine::addLibrary(std::vector<std::string> names) {
	try {

		std::scoped_lock lock(this->impl->script_lock);

		THROW_ERROR(this->impl->libraryLoaded == true, "Library is loaded");

		for (auto name : names) {
			this->impl->pluginNames.insert(name);
		}
		
	}
	catch (std::exception ex) {
		throw;
	}
}

void visionhub::v1::engine::loadLibrary(std::string path) {
	try {

		std::scoped_lock lock(this->impl->script_lock);

		THROW_ERROR(this->impl->libraryLoaded == true, "Library is loaded");

		//Internal 기본 타입등을 등록
		this->loadInternals();


		for (auto& p : std::filesystem::recursive_directory_iterator(path)) {
			if (!p.is_regular_file() || p.path().extension() != ".dll") {
				continue;
			}
		
			auto dllPath = p.path().string();
			auto dllFileName = p.path().filename().string();

			if (this->impl->pluginNames.count(dllFileName) <= 0) {
				continue;
			}


			auto handle = LoadLibraryA(dllPath.c_str());
			if (handle == nullptr) continue;


			auto coreMajorFunc = (int (*)()) GetProcAddress(handle, "coreMajorVersion");
			auto coreMinorFunc = (int (*)()) GetProcAddress(handle, "coreMinorVersion");
			auto corePatchFunc = (int (*)())  GetProcAddress(handle, "corePatchVersion");

			auto pluginMajorFunc = (int (*)()) GetProcAddress(handle, "pluginMajorVersion");
			auto pluginMinorFunc = (int (*)()) GetProcAddress(handle, "pluginMinorVersion");
			auto pluginPatchFunc = (int (*)()) GetProcAddress(handle, "pluginPatchVersion");

			auto sanitycheck = (bool (*)())GetProcAddress(handle, "sanityCheck");
			
			auto pluginInitFunc = (int (*)(visionhub::v1::binder&)) GetProcAddress(handle, "pluginInit");


			if (coreMajorFunc == nullptr || 
				coreMinorFunc == nullptr || 
				corePatchFunc == nullptr || 
				pluginMajorFunc == nullptr || 
				pluginMinorFunc == nullptr || 
				pluginPatchFunc == nullptr ||
				pluginInitFunc == nullptr || 
				sanitycheck == nullptr) {

				FreeLibrary(handle);
				continue;
			}

#ifdef _DEBUG

			if (sanitycheck() == false) {
				FreeLibrary(handle);
				continue;
			}
#endif




			auto coreMajor = coreMajorFunc();
			auto coreMinor = coreMinorFunc();
			auto corePatch = corePatchFunc();

			if (coreMajor != visionhub::v1::coreVersion::major ||
				coreMinor != visionhub::v1::coreVersion::minor ||
				corePatch != visionhub::v1::coreVersion::patch) {

				FreeLibrary(handle);
				continue;
			}

			visionhub::v1::runtime runtime;
			runtime.engine = this->impl->engine;
			visionhub::v1::binder binder(runtime,
									     this->impl->facadeEngine->globalPool());

			auto result = pluginInitFunc(binder);
			if (result == 1) {
				FreeLibrary(handle);
				continue;
			}



			auto pluginMajor = pluginMajorFunc();
			auto pluginMinor = pluginMinorFunc();
			auto pluginPatch = pluginPatchFunc();

			this->impl->plugins.push_back(
				{
					pluginMajor,
					pluginMinor,
					pluginPatch,
					dllFileName
				}
			);
			binder.appendObjExportTable(this->impl->exportObjTableInfo);
			this->impl->modules.push_back(handle);
		}


		this->impl->libraryLoaded = true;
	}
	catch (std::exception ex) {
		throw;
	}
}

void visionhub::v1::engine::loadScript(std::string scriptName, std::string content) {

	try {

		std::scoped_lock lock(this->impl->script_lock);

		this->impl->script_content = content;
		this->impl->script_name = scriptName;
	}
	catch (...) {
		throw;
	}

}

void visionhub::v1::engine::compile() {
	try {

		std::scoped_lock lock(this->impl->script_lock);

		this->impl->compileFromSource();
		this->impl->bindFunc();
		this->impl->ensureContext();

		this->impl->libraryLoaded = true;
	}
	catch (...) {

		

		throw;
	}
}

void visionhub::v1::engine::gc() {
	try {

		std::scoped_lock lock(this->impl->script_lock);

		THROW_ERROR(this->impl->libraryLoaded == false, "Library is not loaded");

		// 2) 스크립트 전역 변수 초기화(상태 리셋)
		if (this->impl->script_module) {
			int r = this->impl->script_module->ResetGlobalVars();
			THROW_ERROR(r < 0, "Reset global variable failed");
		}

		// 3) 가비지 컬렉션 수행(풀 사이클)
		int r = this->impl->engine->GarbageCollect(); // 기본: full cycle
		THROW_ERROR(r < 0, "GC failed");

	}
	catch (std::exception ex) {
		throw;
	}
}

void visionhub::v1::engine::abort() {
	try {
		THROW_ERROR(this->impl->libraryLoaded == false, "Library is not loaded");
		this->impl->ensureContext();
		this->impl->ctx->Abort();
	}
	catch (std::exception ex) {
		throw;
	}
}

void visionhub::v1::engine::argument(visionhub::v1::sharedValue data) {
	try {

		std::scoped_lock lock(this->impl->script_lock);

		this->impl->facadeEngine->argument(data);

	}
	catch (std::exception ex) {
		throw;
	}
}

visionhub::v1::sharedValue visionhub::v1::engine::output() {
	try {

		std::scoped_lock lock(this->impl->script_lock);



		return this->impl->facadeEngine->output();

	}
	catch (std::exception ex) {
		throw;
	}
}

void visionhub::v1::engine::resetOutput() {
	try {

		std::scoped_lock lock(this->impl->script_lock);

		this->impl->facadeEngine->resetOutput();

	}
	catch (std::exception ex) {
		throw;
	}
}

void visionhub::v1::engine::mode(visionhub::v1::execMode mode) {
	try {

		std::scoped_lock lock(this->impl->script_lock);

		THROW_ERROR(this->impl->libraryLoaded == false, "Library is not loaded");

		this->impl->ensureContext();

		this->impl->execMode = mode;

	}
	catch (...) {
		throw;
	}
}


void visionhub::v1::engine::setup() {
	try {

		std::scoped_lock lock(this->impl->script_lock);

		THROW_ERROR(this->impl->libraryLoaded == false, "Library is not loaded");

		this->impl->ensureContext();


		int r = 0;
		int state = this->impl->ctx->GetState();

		if (state != asEXECUTION_SUSPENDED) {
			// 준비 → 실행
			this->impl->ctx->Unprepare();
			r = this->impl->ctx->Prepare(this->impl->func_setup);
			THROW_ERROR(r < 0, "Context preparation failed");
		}

		//this->impl->execMode = mode;
		r = this->impl->ctx->Execute();

		if (r == asEXECUTION_FINISHED) {
			this->impl->ctx->Unprepare();
		}
		else if (r == asEXECUTION_EXCEPTION) {
			asIScriptFunction* f = this->impl->ctx->GetExceptionFunction();
			int line = this->impl->ctx->GetExceptionLineNumber();
			const char* msg = this->impl->ctx->GetExceptionString();
			std::string where = f ? f->GetDeclaration() : "<unknown>";
			std::string err = "Script exception at " + where + ":" + std::to_string(line) + " - " + (msg ? msg : "");
			this->impl->ctx->Unprepare(); // 예외 시에는 정리 권장
			throw visionhub::v1::execException(err, line);
		}
		else if (r == asEXECUTION_SUSPENDED) {
			throw visionhub::v1::suspendException("script suspended");
		}
		else {
			this->impl->ctx->Unprepare(); //옵션..
			throw visionhub::v1::abortException("script aborted.");
		}

	}
	catch (...) {
		throw;
	}
}

void visionhub::v1::engine::run() {
	try {

		std::scoped_lock lock(this->impl->script_lock);

		THROW_ERROR(this->impl->libraryLoaded == false, "Library is not loaded");

		this->impl->ensureContext();


		int r = 0;
		int state = this->impl->ctx->GetState();

		if (state != asEXECUTION_SUSPENDED) {
			// 준비 → 실행
			this->impl->ctx->Unprepare();
			r = this->impl->ctx->Prepare(this->impl->func_run);
			THROW_ERROR(r < 0, "Context preparation failed");
		}

		//this->impl->execMode = mode;
		r = this->impl->ctx->Execute();

		if (r == asEXECUTION_FINISHED) {
			this->impl->ctx->Unprepare();
		}
		else if (r == asEXECUTION_EXCEPTION) {
			asIScriptFunction* f = this->impl->ctx->GetExceptionFunction();
			int line = this->impl->ctx->GetExceptionLineNumber();
			const char* msg = this->impl->ctx->GetExceptionString();
			std::string where = f ? f->GetDeclaration() : "<unknown>";
			std::string err = "Script exception at " + where + ":" + std::to_string(line) + " - " + (msg ? msg : "");
			this->impl->ctx->Unprepare(); // 예외 시에는 정리 권장
			throw visionhub::v1::execException(err, line);
		}
		else if (r == asEXECUTION_SUSPENDED) {
			throw visionhub::v1::suspendException("script suspended");
		}
		else {
			this->impl->ctx->Unprepare(); //옵션..
			throw visionhub::v1::abortException("script aborted.");
		}

	}
	catch (...) {
		throw;
	}
}

void visionhub::v1::engine::shutdown() {
	try {

		std::scoped_lock lock(this->impl->script_lock);

		THROW_ERROR(this->impl->libraryLoaded == false, "Library is not loaded");

		this->impl->ensureContext();


		int r = 0;
		int state = this->impl->ctx->GetState();

		if (state != asEXECUTION_SUSPENDED) {
			// 준비 → 실행
			this->impl->ctx->Unprepare();
			r = this->impl->ctx->Prepare(this->impl->func_shutdown);
			THROW_ERROR(r < 0, "Context preparation failed");
		}

		//this->impl->execMode = mode;
		r = this->impl->ctx->Execute();

		if (r == asEXECUTION_FINISHED) {
			this->impl->ctx->Unprepare();
		}
		else if (r == asEXECUTION_EXCEPTION) {
			asIScriptFunction* f = this->impl->ctx->GetExceptionFunction();
			int line = this->impl->ctx->GetExceptionLineNumber();
			const char* msg = this->impl->ctx->GetExceptionString();
			std::string where = f ? f->GetDeclaration() : "<unknown>";
			std::string err = "Script exception at " + where + ":" + std::to_string(line) + " - " + (msg ? msg : "");
			this->impl->ctx->Unprepare(); // 예외 시에는 정리 권장
			throw visionhub::v1::execException(err, line);
		}
		else if (r == asEXECUTION_SUSPENDED) {
			throw visionhub::v1::suspendException("script suspended");
		}
		else {
			this->impl->ctx->Unprepare(); //옵션..
			throw visionhub::v1::abortException("script aborted.");
		}

	}
	catch (...) {
		throw;
	}
}

void visionhub::v1::engine::storeLogs(bool enable) {
	std::scoped_lock lock(this->impl->script_lock);


	this->impl->enableStoreLog = enable;
}



std::deque<visionhub::v1::traceMessage> & visionhub::v1::engine::getLogs() {
	std::scoped_lock lock(this->impl->script_lock);
	return this->impl->logs;
}

void visionhub::v1::engine::clearLogs() {
	std::scoped_lock lock(this->impl->script_lock);

	this->impl->logs.clear();
}

void visionhub::v1::engine::setMaxLog(std::size_t count) {
	std::scoped_lock lock(this->impl->script_lock);

	this->impl->maxLogCount = count;

	if (this->impl->maxLogCount < 0)
		this->impl->maxLogCount = 1000;
}

void visionhub::v1::engine::setTraceCallback(visionhub::v1::traceCallback callback) {
	std::scoped_lock lock(this->impl->script_lock);
	this->impl->traceCallback = callback;
}

visionhub::v1::traceCallback& visionhub::v1::engine::getTraceCallback() {
	std::scoped_lock lock(this->impl->script_lock);
	return this->impl->traceCallback;
}

void visionhub::v1::engine::setLineCallback(visionhub::v1::lineCallback callback) {
	std::scoped_lock lock(this->impl->script_lock);
	this->impl->lineCallbackLD = callback;
}

visionhub::v1::lineCallback& visionhub::v1::engine::getLineCallback() {
	std::scoped_lock lock(this->impl->script_lock);
	return this->impl->lineCallbackLD;
}


void visionhub::v1::engine::setSnapshotCallback(visionhub::v1::snapShotCallback callback) {
	std::scoped_lock lock(this->impl->script_lock);
	this->impl->snapShotCallback = callback;
}

visionhub::v1::snapShotCallback& visionhub::v1::engine::getSnapShotCallback() {
	std::scoped_lock lock(this->impl->script_lock);
	return this->impl->snapShotCallback;
}


void visionhub::v1::engine::markBreakPoint(int lineNumber) {
	std::scoped_lock lock(this->impl->script_lock);

	this->impl->breakPointLines.insert(lineNumber);
}

void visionhub::v1::engine::eraseBreakPoint(int lineNumber) {
	std::scoped_lock lock(this->impl->script_lock);

	this->impl->breakPointLines.erase(lineNumber);
}


void visionhub::v1::engine::eraseAllBreakPoints() {
	std::scoped_lock lock(this->impl->script_lock);

	this->impl->breakPointLines.clear();
}



std::vector<visionhub::v1::pluginInfo> visionhub::v1::engine::plugins() {
	std::scoped_lock lock(this->impl->script_lock);

	return this->impl->plugins;
}

#pragma endregion

