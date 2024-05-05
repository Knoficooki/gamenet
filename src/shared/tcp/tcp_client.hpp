// tcp/tcp_client.hpp
#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP
#include <boost/asio.hpp>
#include <common/common.hpp>
#include <common/permissions.hpp>
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
		TCPClient(const std::string& ip, const std::string& port);

		template<typename T>
		int send(T* data);
		int send(void* data, uint64_t size);

		template<typename T>
		T* receive();
		template<typename T>
		T* receive(uint64_t count);
	};
}

#endif // TCP_CLIENT_HPP
