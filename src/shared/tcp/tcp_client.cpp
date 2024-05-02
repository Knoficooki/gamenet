#include "tcp_client.hpp"
#include <iostream>

using boost::asio::ip::tcp;

namespace network {

	TCPClient::TCPClient(boost::asio::io_context& io_context)
		: socket_(io_context) {}

	void TCPClient::connect(const std::string& host, const std::string& service) {
		tcp::resolver resolver(socket_.get_executor().context());
		auto endpoints = resolver.resolve(host, service);
		boost::asio::async_connect(socket_, endpoints, [](const boost::system::error_code& error, const tcp::endpoint& endpoint) {
			if (!error) {
				std::cout << "Connected to the server." << std::endl;
				// Communication with server can start here
			}
		});
	}

} // namespace network
