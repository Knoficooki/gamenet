#pragma once 

namespace net {
    enum class message_types {
        none = 0,
        data = 1,

        error = 1 << 2,
    };
}