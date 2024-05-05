#include "tcp_client.hpp"
#include <string>
#include <cstdint>
#include <exception>


using boost::asio::ip::tcp;


namespace net {
	int net::TCPClient::connect(const std::string& ip, const std::string& port)
	{
		tcp::resolver resolver(io_context);
		auto endpoints = resolver.resolve(ip, port);
		tcp::socket socket(io_context);
		boost::asio::connect(socket, endpoints);

		net::permissions sp = *((net::permissions*)recieve(sizeof(net::permissions)));

		PermissionFlag::set(flag, sp);
		PermissionFlag::rem(flag, net::permissions::read);
		PermissionFlag::rem(flag, net::permissions::write);
		
		
		
		return 0;
	}

	int TCPClient::send(void* data, uint64_t size)
	{
		throw std::exception("Unimplemented!");
		return 0;
	}

	void* TCPClient::recieve(uint64_t size)
	{
		char* data = new char[size];
		socket.read_some(boost::asio::buffer(data, size));
		return nullptr;
	}
}