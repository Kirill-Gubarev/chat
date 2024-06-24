#ifndef CLIENT_H
#define CLIENT_H

#include "common.h"

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

#endif //END FILE