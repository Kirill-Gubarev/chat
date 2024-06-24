#include "server.h"
net::Server::Server(uint32_t port) :
	acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
	start_accept();
	io_context.run();
}
void net::Server::start_accept() {
	Connection::pointer new_connection = Connection::create(io_context);
	acceptor.async_accept(new_connection->getSocket(),
		std::bind(&Server::handleAccept, this, new_connection, asio::placeholders::error));
}
void net::Server::handleAccept(Connection::pointer new_connection, const std::error_code& ec) {
	start_accept();
	if (!ec)
	{
		std::cout << "client connected" << std::endl;
		new_connection->sendMessage("hi");
	}
}
net::Server::Connection::Connection(asio::io_context& io_context) : socket(io_context) {}
void net::Server::Connection::handle_write(const std::error_code& ec, size_t) {}
net::Server::Connection::pointer net::Server::Connection::create(asio::io_context& io_context) {
	return pointer(new Connection(io_context));
}
asio::ip::tcp::socket& net::Server::Connection::getSocket() {
	return socket;
}
void net::Server::Connection::sendMessage(std::string message) {
	asio::async_write(socket, asio::buffer(message),
		std::bind(&Connection::handle_write, shared_from_this(),
			asio::placeholders::error,
			asio::placeholders::bytes_transferred));
}