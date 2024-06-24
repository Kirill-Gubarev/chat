#ifndef SERVER_H
#define SERVER_H

#define _WIN32_WINNT 0x0A00
#include "common.h"

namespace net {
	class Server
	{
	private:
		class Connection : public std::enable_shared_from_this<Connection>
		{
		public:
			typedef std::shared_ptr<Connection> pointer;
		private:
			asio::ip::tcp::socket socket;
			std::string message[1000];
			Connection(asio::io_context& io_context);
			void handle_write(const std::error_code& ec, size_t);
		public:
			static pointer create(asio::io_context& io_context);
			asio::ip::tcp::socket& getSocket();
			void sendMessage(std::string message);
		};
		asio::io_context io_context;
		asio::ip::tcp::acceptor acceptor;
	public:
		Server(uint32_t port);
		void start_accept();
		void handleAccept(Connection::pointer new_connection, const std::error_code& ec);
	};
}

#endif //END FILE