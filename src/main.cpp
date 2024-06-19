#include <iostream>
#include <stdint.h>
#include "network/client.h"
#include "network/server.h"
uint32_t readNumber() {
	std::string line;
	while (true) {
		std::getline(std::cin, line);
		try {
			return std::stoul(line);
		}
		catch (std::exception& e) {
			continue;
		}
	}
}
void runClient() {
	std::string ip, port;
	std::cout << "Enter ip:\n";
	std::getline(std::cin, ip);
	if (ip == "") {
		ip = "127.0.0.1";
		std::cout << ip << std::endl;
	}
	std::cout << "Enter port:" << std::endl;
	std::getline(std::cin, port);
	if (port == "") {
		port = "5667";
		std::cout << port << std::endl;
	}
	net::Client client(ip, port);
	client.mainLoop();
}
void runServer() {
	uint32_t port;
	std::cout << "Enter port:" << std::endl;
	port = readNumber();
	net::Server server(port);
	server.mainLoop();
}

int main() {
    uint32_t input = 0;
	do {
		std::cout << "1. Connect to server\n2. Create a server\n";
		input = readNumber();
		if (input == 1)
			runClient();
		else if (input == 2)
			runServer();
	} while (input != 1 && input != 2);
	system("pause");
	return 0;
}