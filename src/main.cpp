#include <iostream>
#include <asio.hpp>
void server() {
	try {
		asio::io_context ioContext;
		asio::ip::tcp::acceptor acc(ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 5667));

		while (true)
		{
			asio::ip::tcp::socket socket(ioContext);
			acc.accept(socket);
			std::cout << "client connected" << std::endl;

			std::thread thr([&socket]() {
				while (true) {
					std::string message = "";
					std::getline(std::cin, message);
					message += "\n";
					asio::error_code ec;
					asio::write(socket, asio::buffer(message), ec);
				}
				});
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
void client() {
	try {
		asio::io_context ioContext;
		asio::ip::tcp::resolver res(ioContext);
		auto endpoints = res.resolve("127.0.0.1", "5667");
		asio::ip::tcp::socket socket(ioContext);
		asio::connect(socket, endpoints);
		while (true)
		{
			std::thread thr([&socket]() {
				while (true) {
					std::string message = "";
					std::getline(std::cin, message);
					message += "\n";
					asio::error_code ec;
					asio::write(socket, asio::buffer(message), ec);
				}
				});
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
int main() {
	int input = 0;
	std::cout << "1. Connect to server\n2. Create a server\n";
	std::cin>> input;
	if (input == 1)
		client();
	else if(input == 2)
		server();
	system("pause");
	return 0;
}