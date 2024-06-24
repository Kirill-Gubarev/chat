#include "client.h"
net::Client::Client(const std::string ip, const  std::string port) :
	res(ioContext),
	socket(ioContext) {
	endpoints = res.resolve(ip, port);
	asio::connect(socket, endpoints);
}
void net::Client::mainLoop() {
	try {
		std::cout << "connected to server" << std::endl;
		while (true) {
			std::thread thr(&Client::sendMessage, this);
			thr.detach();
			std::vector<char> buf(100);
			asio::error_code ec;
			size_t len = socket.read_some(asio::buffer(buf), ec);
			if (ec) {
				throw asio::system_error(ec);
			}
			(std::cout << "SERVER: ").write(buf.data(), len) << std::endl;
		}
	}
	catch (std::exception& ex) {
		net::exitProgram(-1, ex);
	}
}
void net::Client::sendMessage() {
	while (true) {
		std::string message = "";
		std::getline(std::cin, message);
		asio::error_code ec;
		asio::write(socket, asio::buffer(message), ec);
	}
}