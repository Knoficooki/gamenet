#include <boost/asio.hpp>
#include <array>
#include <iostream>

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

int send_message(tcp::socket& sender, const void* msg, uint64_t size) {
	struct msg_header* h = new struct msg_header;
	h->flags = binary;
	h->length = size;

	sender.write_some(boost::asio::buffer(h, sizeof(struct msg_header)));

	sender.write_some(boost::asio::buffer(msg, size));
	delete h;
	return 0;
}


int main() {
	try {
		boost::asio::io_context io_context;
		tcp::resolver resolver(io_context);
		auto endpoints = resolver.resolve("localhost", "1234");
		tcp::socket socket(io_context);
		boost::asio::connect(socket, endpoints);

		boost::system::error_code error;

		const char* msg = "You gay bitch?";
		send_message(socket, (const void*)msg, strlen(msg));

		if (error == boost::asio::error::eof)
			std::cout << "Connection closed cleanly by peer." << std::endl;
		else if (error)
			throw boost::system::system_error(error);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
