// tcp/tcp_server.cpp
#include "tcp_server.hpp"

using boost::asio::ip::tcp;

namespace network {

	TCPServer::TCPServer(boost::asio::io_context& io_context, unsigned short port)
		: acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {}

	void TCPServer::start_accept() {
		tcp::socket socket(acceptor_.get_executor().context());
		acceptor_.async_accept(socket, [this, &socket](const boost::system::error_code& error) {
			handle_accept(error, std::move(socket));
		});
	}

	void TCPServer::handle_accept(const boost::system::error_code& error, tcp::socket socket) {
		if (!error) {
			// Handle new connection
			std::cout << "New connection accepted." << std::endl;
			// Here you might want to create a session and start communication
		}
		start_accept(); // Continue accepting new connections
	}

} // namespace network
