// tcp/tcp_server.hpp
#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <boost/asio.hpp>

#include "../common/common.hpp"
#include "../common/exception/exception.hpp"
#include "../common/permissions.hpp"
#include "../common/utils/flag.hpp"
#include <stdint.h>
#include <string>
#include <vector>
#include <thread>

namespace net {
	typedef uint_least16_t port_type;

	class TCPServer : public NetObject {
	protected:
		/*
		* Variables
		*/
		boost::asio::ip::tcp::acceptor acceptor;
		std::vector<boost::asio::ip::tcp::socket> clients;
		void(*handle_client)(boost::asio::ip::tcp::socket&);
		
		bool running;
		
		/*
		* Functions
		*/
		virtual void cleanup();

	public:
		virtual void run();
		TCPServer(boost::asio::ip::tcp type, port_type port, void(*handle_client)(boost::asio::ip::tcp::socket&));
	};
}

#define TCP_SERVER_IMPLEMENTATION

#ifdef TCP_SERVER_IMPLEMENTATION
// tcp/tcp_server.cpp

net::TCPServer::TCPServer(
	boost::asio::ip::tcp type,
	port_type port, 
	void(*handle_client)(boost::asio::ip::tcp::socket&) )
	: acceptor(io_context, boost::asio::ip::tcp::endpoint(type, port)), handle_client(handle_client)
{
	
}


#undef TCP_SERVER_IMPLEMENTATION
#endif // TCP_SERVER_IMPLEMENTATION

#endif // TCP_SERVER_HPP
