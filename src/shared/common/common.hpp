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

#ifdef NET_COMMON_IMPLEMENTATION
// common/common.cpp

// Implementation of common utilities
namespace net {
	
}

#undef NET_COMMON_IMPLEMENTATION
#endif // NET_COMMON_IMPLEMENTATION

