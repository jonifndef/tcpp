#pragma once

#include <linux/if.h>
#include <linux/if_tun.h>
#include <string>

#include "ethernet-frame.hpp"

class TapDevice
{
    public:
        TapDevice(const std::string &devname, const std::string &ip_addr);
        ~TapDevice();

        auto read_data(std::array<uint8_t, EthernetSizes::frame_max_size> &buffer) -> int const;

        // There should only be one instance of a tap interface at any given time
        TapDevice(const TapDevice &other)            = delete;
        TapDevice(TapDevice &&other)                 = delete;
        TapDevice& operator=(const TapDevice& other) = delete;
        TapDevice& operator=(TapDevice&& other)      = delete;

    private:
        int m_tap_fd = 0;
};
