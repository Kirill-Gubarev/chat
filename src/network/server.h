#define _WIN32_WINNT 0x0A00
#include <iostream>
#include <asio.hpp>
namespace net {
	class Server {
	private:
		asio::io_context ioContext;
		asio::ip::tcp::socket socket;

		asio::ip::tcp::acceptor acc;
		int port;
		void sendMessage();
	public:
		Server(const unsigned int port);
		void mainLoop();
	};
}