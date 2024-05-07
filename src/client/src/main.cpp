#include <iostream>

#include <tcp/tcp_client.hpp>


enum msg_type {
	acii,
	binary,
	wchar,
};

struct msg_header {
	uint64_t length;
	uint8_t flags;
};

int main() {
	try {
		net::TCPClient client("localhost", "1234");
		const char* msg = "Hello World!\n";
		msg_header h = { strlen(msg), 0 };
		client.send(&h, sizeof(h));
		client.send(msg, h.length);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
