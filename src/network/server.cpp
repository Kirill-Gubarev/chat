#include "server.h"
net::Server::Server(unsigned int port):
	socket(ioContext),
	port(port),
	acc(ioContext,asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)){}
void net::Server::run() {
	try {
		while (true){
			acc.accept(socket);
			std::cout << "client connected" << std::endl;

			std::thread thr(&Server::receiveMessage, this);
			thr.detach();

			while (true)
			{
				std::vector<char> buf(100);
				asio::error_code ec;
				size_t len = socket.read_some(asio::buffer(buf), ec);
				if (ec == asio::error::eof)
				{
					//break;
				}
				else if (ec) {
					throw asio::system_error(ec);
				}
				std::cout << "CLIENT: ";
				std::cout.write(buf.data(), len);
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
void net::Server::receiveMessage() {
	while (true) {
		std::string message = "";
		std::getline(std::cin, message);
		message += "\n";
		asio::error_code ec;
		asio::write(socket, asio::buffer(message), ec);
	}
}