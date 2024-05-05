#include "tcp_client.hpp"
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

		net::permissions sp = *receive<net::permissions>();

		PermissionFlag::set(flag, sp);
	}

	template<typename T>
	int TCPClient::send(T* data)
	{
		try {
			socket.write_some(boost::asio::buffer(data, sizeof(T)));
		}
		catch (const boost::exception& e) {
			// Handle Boost-specific exceptions
			std::cerr << "Boost exception: " << boost::diagnostic_information(e);
		}
		catch (const std::exception& e) {
			// Handle standard exceptions
			throw std::exception();
		}
		catch (...) {
			// Handle all other types of exceptions
			throw std::exception("Unknown error occurred while trying to send data via TCP.");
		}
		return 0;
	}

	int TCPClient::send(void* data, uint64_t count)
	{
		try {
			socket.write_some(boost::asio::buffer(data, sizeof(char) * count));
		}
		catch (const boost::exception& e) {
			// Handle Boost-specific exceptions
			std::cerr << "Boost exception: " << boost::diagnostic_information(e);
		}
		catch (const std::exception& e) {
			// Handle standard exceptions
			throw std::exception();
		}
		catch (...) {
			// Handle all other types of exceptions
			throw std::exception("Unknown error occurred while trying to send data via TCP.");
		}
		return 0;
	}

	template<typename T>
	T* TCPClient::receive()
	{
		try {
			T* data = new T;
			socket.read_some(boost::asio::buffer(data, sizeof(T)));
			return data;
		}
		catch (const boost::exception& e) {
			// Handle Boost-specific exceptions
			std::cerr << "Boost exception: " << boost::diagnostic_information(e);
		}
		catch (const std::exception& e) {
			// Handle standard exceptions
			throw std::exception();
		}
		catch (...) {
			// Handle all other types of exceptions
			throw std::exception("Unknown error occurred while trying to receive data via TCP.");
		}
	}

	template<typename T>
	T* TCPClient::receive(uint64_t count)
	{
		try {
			T* data = new T[count];
			socket.read_some(boost::asio::buffer(data, sizeof(T) * count));
			return data;
		}
		catch (const boost::exception& e) {
			// Handle Boost-specific exceptions
			std::cerr << "Boost exception: " << boost::diagnostic_information(e);
		}
		catch (const std::exception& e) {
			// Handle standard exceptions
			throw std::exception();
		}
		catch (...) {
			// Handle all other types of exceptions
			throw std::exception("Unknown error occurred while trying to receive data via TCP.");
		}
	}
}