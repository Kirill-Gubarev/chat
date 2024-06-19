#define _WIN32_WINNT 0x0A00
#include <iostream>
#include <asio.hpp>
namespace net {
	class Client {
	private:
		asio::io_context ioContext;
		asio::ip::tcp::socket socket;

		asio::ip::tcp::resolver res;
		asio::ip::basic_resolver_results<asio::ip::tcp> endpoints;
		void sendMessage();
	public:
		Client(const std::string ip, const std::string port);
		void mainLoop();
	};
}