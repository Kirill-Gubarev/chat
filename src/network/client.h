#include <iostream>
#include <asio.hpp>
namespace net {
	class Client {
	private:
		asio::io_context ioContext;
		asio::ip::tcp::resolver res;
		asio::ip::tcp::socket socket;
		asio::ip::basic_resolver_results<asio::ip::tcp> endpoints;
		void receiveMessage();
	public:
		Client(std::string ip, std::string port);
		void run();
	};
}