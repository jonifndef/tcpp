#pragma once

#include <stdint.h>

#include "tap-device.hpp"

class Tcpp
{
    public:
        Tcpp(const std::string &dev_name, const uint32_t num_packets);
        ~Tcpp();
        
        auto run() -> void;

    private:
        TapDevice m_tap_dev{"tap0"};
        uint32_t m_num_packets{};
};
