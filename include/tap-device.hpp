#pragma once

#include <linux/if.h>
#include <linux/if_tun.h>
#include <string>
#include <vector>

class TapDevice
{
public:
    TapDevice(const TapDevice &other)            = delete;
    TapDevice(TapDevice &&other)                 = delete;
    TapDevice& operator=(const TapDevice& other) = delete;
    TapDevice& operator=(TapDevice&& other)      = delete;

    static TapDevice& instance()
    {
        static TapDevice tapdevice;
        return tapdevice;
    }
    auto initialize_tap_device(const std::string dev) -> bool;
    auto read_data() -> int;
    auto close_tap_device() -> void;
private:
    TapDevice();
    ~TapDevice();
    int m_tap_fd = 0;
};
