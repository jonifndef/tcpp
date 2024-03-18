#pragma once

#include <linux/if.h>
#include <linux/if_tun.h>
#include <string>
#include <vector>

class TapDevice
{
public:
    TapDevice();
    ~TapDevice();

    auto initialize(const std::string dev) -> bool;
    auto read_data() -> int;

    // There should only be one instance of a tap interface at any given time
    TapDevice(const TapDevice &other)            = delete;
    TapDevice(TapDevice &&other)                 = delete;
    TapDevice& operator=(const TapDevice& other) = delete;
    TapDevice& operator=(TapDevice&& other)      = delete;
private:
    int m_tap_fd = 0;
};
