#pragma once

#include <linux/if.h>
#include <linux/if_tun.h>
#include <string>

class TapDevice
{
public:
    TapDevice();
    ~TapDevice();
    bool initialize_tap_device(const std::string dev);
private:
    int m_tap_fd = 0;
};
