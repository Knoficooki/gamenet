// tcp/tcp_client.hpp
#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include "../common/common.hpp"

namespace network {
	class TCPClient {
	public:
		TCPClient(boost::asio::io_context& io_context);
		void connect(const std::string& host, const std::string& service);

	private:
		boost::asio::ip::tcp::socket socket_;
	};
}

#endif // TCP_CLIENT_HPP
