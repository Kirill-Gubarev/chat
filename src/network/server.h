#include <iostream>
#include <asio.hpp>
namespace net {
	class Server {
	private:
		asio::io_context ioContext;
		int port;
		asio::ip::tcp::acceptor acc;
		asio::ip::tcp::socket socket;

		void receiveMessage();
	public:
		Server(unsigned int port);
		void run();
	};
}