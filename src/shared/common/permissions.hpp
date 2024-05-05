#pragma once

namespace net {
    enum permissions : unsigned char {
        none = 0,
        server_read = 1,   // you are allowed to read from the server
        server_write = 1 << 1,  // you are allowed to write to the server
        server_exec = 1 << 2,   // you are allowed to execute on the server
        full = 255
    };
}
