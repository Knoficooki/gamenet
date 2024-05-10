// tcp/tcp_server.hpp
#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <boost/asio.hpp>

#include "../common/common.hpp"
#include "../common/exception/exception.hpp"
#include "../common/permissions.hpp"
#include "../common/utils/flag.hpp"
#include "../common/thread.hpp"
#include <stdint.h>
#include <string>
#include <vector>
#include <thread>

namespace net {
	typedef uint_least16_t port_type;

	class TCPServer : public NetObject {
	public:
		using client = std::pair<boost::asio::ip::tcp::socket*, net::thread<>*>;
		using tcp = boost::asio::ip::tcp;
		using client_state = std::atomic<net::thread<>::thread_state>;
		typedef void(*handle_client_func)(client_state&, boost::asio::ip::tcp::socket&);
	protected:
		/*
		* Variables
		*/
		tcp::acceptor acceptor;
		std::vector<client> clients;
		handle_client_func client_function;
		
		bool running = false;
		
		/*
		* Functions
		*/
		void cleanup();

	public:
		virtual void run();
		TCPServer(	tcp type, 
					port_type port, 
					handle_client_func handle_client);

		~TCPServer();
	};
}

#ifdef TCP_SERVER_IMPLEMENTATION
// tcp/tcp_server.cpp

net::TCPServer::TCPServer(
		tcp type,
		port_type port, 
		handle_client_func handle_client )
	:	acceptor(io_context, tcp::endpoint(type, port)),
		client_function(handle_client)
{
}

void net::TCPServer::run() {
	running = true;
	while (running) {
		client c(new tcp::socket(io_context), nullptr);
		acceptor.accept(*c.first);
		c.second = new net::thread<>(client_function, std::move(*c.first));
		
		clients.push_back(c);
	}
}

void net::TCPServer::cleanup()
{
	while (!clients.empty()) {
		clients.back().second->stop();
		clients.back().first->shutdown(boost::asio::socket_base::shutdown_both);
		clients.back().first->close();
		delete clients.back().first;
		delete clients.back().second;
		clients.pop_back();
	}
}

net::TCPServer::~TCPServer()
{
	cleanup();
	acceptor.close();
}


#undef TCP_SERVER_IMPLEMENTATION
#endif // TCP_SERVER_IMPLEMENTATION

#endif // TCP_SERVER_HPP
