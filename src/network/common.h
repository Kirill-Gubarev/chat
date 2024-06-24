#ifndef COMMON_H
#define COMMON_H

#define _WIN32_WINNT 0x0A00
#include <iostream>
#include <stdint.h>
#include <asio.hpp>

namespace net {
	void exitProgram(int code, std::string message);
	void exitProgram(int code, std::exception ex);
}

#endif //END FILE