#pragma once

#include <stdint.h>

class TapDevice;

class Tcpp
{
    public:
        Tcpp(const uint32_t num_packets);
        ~Tcpp();
        
        auto run() -> void;

    private:
        uint32_t m_num_packets{};
};
