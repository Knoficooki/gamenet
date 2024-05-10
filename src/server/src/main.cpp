#include <boost/asio.hpp>
#include <iostream>


#include <implementation.h>

#include <common/permissions.hpp>

#include <tcp/tcp_server.hpp>

using boost::asio::ip::tcp;


enum msg_type {
	acii,
	binary,
	wchar,
};

struct msg_header {
	uint64_t length;
	uint8_t flags;
};

struct list {
	char* data;
	uint64_t len;
};

list get_message(tcp::socket& sender) {
	list data;
	struct msg_header* h = new struct msg_header;
	sender.read_some(boost::asio::buffer(h, sizeof(msg_header)));

	data.data = new char[h->length + 1];
	data.data[h->length] = 0;
	sender.read_some(boost::asio::buffer(data.data, h->length));
	data.len = h->length;
	delete h;
	return data;
}


void handle_client(net::TCPServer::client_state& state , tcp::socket& socket) {
	std::cout << "Client connected...\n";
	net::permissions sp = net::permissions::full;
	socket.write_some(boost::asio::buffer(&sp, sizeof(sp)));
	std::cout << get_message(socket).data << std::endl;
}

int main() {
	try {
		net::TCPServer(tcp::v4(), 1234, handle_client);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
