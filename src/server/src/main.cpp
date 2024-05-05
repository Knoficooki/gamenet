#include <boost/asio.hpp>
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

struct list {
    char* data;
    uint64_t len;
};

list get_message(tcp::socket& sender) {
    list data;
    struct msg_header* h = new struct msg_header;
    sender.read_some(boost::asio::buffer(h, sizeof(msg_header)));

    data.data = new char[h->length+1];
    data.data[h->length] = 0;
    sender.read_some(boost::asio::buffer(data.data, h->length));
    delete h;
    data.len = h->length;
    return data;
}


void handle_client(tcp::socket socket) {
    std::cout << "Client connected...\n";
    std::cout << get_message(socket).data << std::endl;
}

int main() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 1234));

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::thread(handle_client, std::move(socket)).detach();
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
