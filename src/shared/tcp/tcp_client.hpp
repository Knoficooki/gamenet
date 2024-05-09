// tcp/tcp_client.hpp
#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP
#include "../common/common.hpp"
#include "../common/exception/exception.hpp"
#include "../common/permissions.hpp"
#include "../common/utils/flag.hpp"

#include <boost/asio.hpp>
#include <stdint.h>
#include <string>

namespace net {
	class TCPClient : public NetObject {
	protected:
		using PermissionFlag = flags::FlagManager<net::permissions>;
	private:
		boost::asio::ip::tcp::resolver resolver;
		boost::asio::ip::tcp::socket socket;
		net::permissions flag; // sx, sw, sr, w, r
	public:
		exception::level error_level = exception::level::fatal;

		TCPClient(const std::string& ip, const std::string& port);

		int send(const void* data, uint64_t size);

		int receive(void* data, uint64_t size);
	};
}


#ifdef TCP_CLIENT_IMPLEMENTATION
#include <common/permissions.hpp>
#include <iostream>
#include <boost/exception/all.hpp> 

using boost::asio::ip::tcp;

namespace net {
	TCPClient::TCPClient(const std::string& ip, const std::string& port)
		: resolver(io_context), socket(io_context)
	{
		auto endpoints = resolver.resolve(ip, port);
		boost::asio::connect(socket, endpoints);

		net::permissions sp;
		if (receive(&sp, sizeof(sp))) {
			throw netexcept("Could not receive permission flags.", net::exception::level::fatal);
		}

		PermissionFlag::set(flag, sp);
	}

	int TCPClient::send(const void* data, uint64_t size)
	{
		try {
			socket.write_some(boost::asio::buffer(data, sizeof(char) * size));
			return 0;
		}
		catch (const boost::exception& e) {
			// Handle Boost-specific exceptions
			throw netexcept(boost::diagnostic_information(e).c_str(), error_level);
		}
		catch (const std::exception& e) {
			// Handle standard exceptions
			throw netexcept(e.what(), error_level);
		}
		catch (...) {
			// Handle all other types of exceptions
			throw netexcept("An unexpected error occurred.", error_level);
		}
		return -1;
	}


	int TCPClient::receive(void* data, uint64_t size)
	{
		try {
			if (!data) {
				data = new char[size];
			}
			socket.read_some(boost::asio::buffer(data, sizeof(char) * size));
			return 0;
		}
		catch (const boost::exception& e) {
			// Handle Boost-specific exceptions
			throw netexcept(boost::diagnostic_information(e).c_str(), error_level);
		}
		catch (const std::exception& e) {
			// Handle standard exceptions
			throw netexcept(e.what(), error_level);
		}
		catch (...) {
			// Handle all other types of exceptions
			throw netexcept("An unexpected error occurred.", error_level);
		}
		return -1;
	}
}

#undef TCP_CLIENT_IMPLEMENTATION
#endif // TCP_CLIENT_IMPLEMENTATION

#endif // tcp_client_hpp
