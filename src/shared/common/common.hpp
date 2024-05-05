#ifndef COMMON_HPP
#define COMMON_HPP

#include <boost/asio.hpp>

// Common utilities for networking
namespace net {

    enum permissions : uint8_t {
        none = 0,
        read = 1,               
        write = 1 << 1,
        server_read = 1 << 2,   // you are allowed to read from the server
        server_write = 1 << 3,  // you are allowed to write to the server
        server_exec = 1 << 4,   // you are allowed to execute on the server
        full = 255
    };

    enum class message_types {
        none = 0,
        data = 1,

        error = 1 << 2,
    };

    class NetObject {
    protected:
        boost::asio::io_context io_context;
    };
}

#endif // COMMON_HPP
