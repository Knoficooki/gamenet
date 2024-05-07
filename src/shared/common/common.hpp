#pragma once

#include <boost/asio.hpp>

#ifndef NET_EXCEPTION_INCLUDE
#define netexcept(msg, level) 
#endif

// Common utilities for networking
namespace net {
    class NetObject {
    protected:
        boost::asio::io_context io_context;
    public:
        NetObject() = default;
    };
}

#ifdef NET_COMMON_IMPLEMENTATION
// common/common.cpp

// Implementation of common utilities
namespace net {
	
}

#undef NET_COMMON_IMPLEMENTATION
#endif // NET_COMMON_IMPLEMENTATION

