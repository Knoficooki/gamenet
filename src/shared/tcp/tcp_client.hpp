// tcp/tcp_client.hpp
#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP
#include <boost/asio.hpp>
#include <common/common.hpp>
#include <common/utils/flag.hpp>
#include <cstdint>
#include <string>

namespace net {
	class TCPClient : NetObject {
	protected:
		using PermissionFlag = flags::FlagManager<net::permissions>;
	private:
		boost::asio::ip::tcp::resolver resolver;
		boost::asio::ip::tcp::socket socket;
		net::permissions flag; // sx, sw, sr, w, r
	public:
		int connect(const std::string& ip, const std::string& port);
		int send(void* data, uint64_t size);
		void* recieve(uint64_t size);
	};
}

#endif // TCP_CLIENT_HPP
