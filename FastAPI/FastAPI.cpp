#include "crow.h"
#include <iostream>
#include <thread>

#if defined(_WIN32) || defined(_WIN64)
const char* os = "Windows";
#elif defined(__linux__)
const char* os = "Linux";
#elif defined(__APPLE__) || defined(__MACH__)
const char* os = "MacOS";
#else
const char* os = "Unknown";
#endif

int max_thread_count = std::thread::hardware_concurrency(); // Get number of CPU cores

// Configure server
//========================================================================================================
int web_port = 8080;
int thread_count = max_thread_count; // Can be set to anything from 1 to max_thread_count
//========================================================================================================

int main() {
	std::cout << "=====================================================" << std::endl;
	std::cout << "FAST API PROJECT 0.a Alpha" << std::endl;
	std::cout << "Operating System: " << os << std::endl;
	std::cout << "Web Port: " << web_port << std::endl;
	std::cout << "Thread Count: " << thread_count << " / " << max_thread_count << std::endl;
	std::cout << "=====================================================" << std::endl;

	crow::SimpleApp app;

	if (thread_count == 0) {
		thread_count = 4;
	}

	CROW_ROUTE(app, "/")([](const crow::request&, crow::response& res) {
		if (os == "Windows")
			res.set_header("Connection", "close");  // Force connection to close -- POSSIBLE WINDOWS HOST O/S PROBLEM  
		res.write("Hello, Crow!");
		res.end();  // Ensure response is sent properly  
		});

	CROW_ROUTE(app, "/large")([](const crow::request&, crow::response& res) {
		if (os == "Windows")
			res.set_header("Connection", "close");  // Force connection to close -- POSSIBLE WINDOWS HOST O/S PROBLEM  
		res.write(std::string(512 * 1024, 'A'));
		res.end();  // Ensure response is sent properly  
		});

	app.port(web_port).multithreaded().concurrency(thread_count).run();  // Explicit concurrency  

	return 0;
}
