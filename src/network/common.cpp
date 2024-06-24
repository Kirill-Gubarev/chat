#include "common.h"
void net::exitProgram(int code, std::string message) {
	std::cout <<"\n=== END OF THE PROGRAM ===\nMESSAGE: " << message << std::endl;
	system("pause");
	std::exit(code);
}
void net::exitProgram(int code, std::exception ex) {
	std::cerr << "\n=== END OF THE PROGRAM ===\nEXCEPTION: " << ex.what() << std::endl;
	system("pause");
	std::exit(code);
}