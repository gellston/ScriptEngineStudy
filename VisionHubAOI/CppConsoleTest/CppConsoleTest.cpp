// CppConsoleTest.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <future>
#include <ostream>
#include <stack>
#include <queue>

#include <core/collection/memoryPool.h>
#include <core/collection/memoryBlock.h>
#include <core/collection/value.h>

#include <core/reflection/typeRegistry.h>

#include <core/rect.h>
#include <core/image.h>



#include <engine/engine.h>
#include <engine/engineException/suspendException.h>


int main()
{

	std::queue<int> test;
	

	auto engine = visionhub::v1::engine::create();



	engine->addLibrary({
		"VisionHubAOI.Plugin.OpenCV.dll"
	});
	engine->loadLibrary("E:\\Github\\visionhubaoi\\VisionHubAOI\\x64\\Release\\Plugins");

	engine->setTraceCallback([&](visionhub::v1::traceType type, int row, int col, std::string section, std::string message) {
		std::string errorType = type == visionhub::v1::traceType::error ? "ERROR" :
							    type == visionhub::v1::traceType::warning ? "WARN " : "INFO";

		std::cout << "[" << errorType << "]" << "[" << section << "](" << row << "," << col << "):";
		std::cout << message << std::endl;
	});

	engine->setLineCallback([&](int row, int col, std::string section) {
		//std::cout << "Break:[" << section << "](" << row << "," << col << "):" << std::endl;
	});

	engine->setSnapshotCallback([&](visionhub::v1::snapShot_ptr snap) {
		//std::cout << "==================" << std::endl;
		//std::cout << "snapshot triggered" << std::endl;
		//snap->print();
	
		//std::cout << "==================" << std::endl;
	});


	engine->loadScript("test_script(bong)",
		R"(
void run(){

}

void setup(){

}

void shutdown(){

}
)");









	try {
		engine->compile();
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
	}

	try {

		auto start = std::chrono::high_resolution_clock::now();
		int count = 0;
		while (true) {


			try {

				engine->mode(visionhub::v1::execMode::run);
				engine->run();
			


				auto output = engine->output();

				std::cout << "check : " << (int)output->kind() << std::endl;

				unsigned int testValue = 0;

				if ((*output)["test"]["width"].get(testValue) == true) {
					std::cout << "test" << std::endl;
				}


			}
			catch (visionhub::v1::suspendException ex) {
				std::cout << ex.what() << std::endl;
				continue;
			}
			catch (std::exception ex) {
				std::cout << ex.what() << std::endl;
			}
		

			count++;
			auto end = std::chrono::high_resolution_clock::now();

			auto duration = end - start;


			if (std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() > 1000) {
				std::cout << "fps : " << count << std::endl;
				start = std::chrono::high_resolution_clock::now();
				count = 0;
			}
			//std::cout << "test" << std::endl;
			// 
			// 
			//std::cout << "test" << std::endl;
			//std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

	}
	catch (visionhub::v1::suspendException ex) {
		std::cout << ex.what() << std::endl;
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
	}

}
