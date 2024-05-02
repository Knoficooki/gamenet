// tcp/tcp_server.hpp
#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include "../common/common.hpp"

namespace network {
	class TCPServer {
	public:
		TCPServer(boost::asio::io_context& io_context, unsigned short port);
		void start_accept();
		void handle_accept(const boost::system::error_code& error);

	private:
		boost::asio::ip::tcp::acceptor acceptor_;
	};
}

#endif // TCP_SERVER_HPP
