#include "server.h"
net::Server::Server(const unsigned int port) :
	socket(ioContext),
	port(port),
	acc(ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
	ioContext.run();
}
void net::Server::mainLoop() {
	try {
		while (true) {
			acc.accept(socket);
			std::cout << "client connected" << std::endl;
			std::thread thr(&Server::sendMessage, this);
			thr.detach();
			while (true)
			{
				std::vector<char> buf(100);
				asio::error_code ec;
				size_t len = socket.read_some(asio::buffer(buf), ec);
				if (ec) {
					throw asio::system_error(ec);
				}
				(std::cout << "CLIENT: ").write(buf.data(), len) << std::endl;
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
void net::Server::sendMessage() {
	while (true) {
		std::string message = "";
		std::getline(std::cin, message);
		asio::error_code ec;
		asio::write(socket, asio::buffer(message), ec);
	}
}