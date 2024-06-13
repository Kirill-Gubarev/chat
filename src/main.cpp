#include <iostream>
#include "network/client.h"
#include "network/server.h"
int main() {
	int input = 0;
	std::cout << "1. Connect to server\n2. Create a server\n";
	std::cin >> input;
	if (input == 1){
		std::string ip, port;
		std::cout << "Enter ip:\n";
		std::cin >> ip;
		std::cout << "Enter port:"<<std::endl;
		std::cin >> port;

		net::Client client(ip,port);
		client.run();
	}
	else if (input == 2)
	{
		unsigned int port;
		std::cout << "Enter port:" << std::endl;
		std::cin >> port;
		net::Server server(port);
		server.run();
	}
	system("pause");
	return 0;
}