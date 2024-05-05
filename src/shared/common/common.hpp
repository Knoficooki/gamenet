#ifndef COMMON_HPP
#define COMMON_HPP

#include <boost/asio.hpp>

// Common utilities for networking
namespace net {

    class NetObject {
    protected:
        boost::asio::io_context io_context;
    public:
        NetObject() = default;
    };
}

#endif // COMMON_HPP
