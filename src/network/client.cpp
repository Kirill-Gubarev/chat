#include "client.h"
net::Client::Client(std::string ip, std::string port):
	res(ioContext), 
	socket(ioContext) {
	endpoints = res.resolve(ip,port);
	asio::connect(socket, endpoints);
}
void net::Client::run(){
	try {
		while (true)
		{
			std::thread thr(&Client::receiveMessage,this);
			thr.detach();
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
			std::cout << "SERVER: ";
			std::cout.write(buf.data(), len);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
void net::Client::receiveMessage(){
	while (true) {
		std::string message = "";
		std::getline(std::cin, message);
		message += "\n";
		asio::error_code ec;
		asio::write(socket, asio::buffer(message), ec);
	}
}