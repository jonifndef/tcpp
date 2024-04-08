#include "tap-device.hpp"
#include "ethernet-frame.hpp"

#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <linux/string.h>
#include <sys/ioctl.h>

#include "spdlog/fmt/bin_to_hex.h"
#include "spdlog/spdlog.h"

namespace
{
    const std::string TUN_DEVICE = "/dev/net/tun";
}

TapDevice::TapDevice(const std::string &devname)
{
    struct ifreq interface_request;

    if ((m_tap_fd = open(TUN_DEVICE.c_str(), O_RDWR)) < 0)
    {
        throw std::runtime_error("Cannot open tap interface");
    }

    memset(&interface_request, 0, sizeof(interface_request));

    interface_request.ifr_flags = IFF_TAP | IFF_NO_PI;

    if (!devname.empty())
    {
	    strncpy(interface_request.ifr_name, devname.c_str(), IFNAMSIZ);
    }

    if (ioctl(m_tap_fd, TUNSETIFF, (void*) &interface_request) < 0)
    {
	    close(m_tap_fd);

        throw std::runtime_error("Cannot run ioctl on tap file descriptor");
    }
}

TapDevice::~TapDevice()
{
    close(m_tap_fd);
}

auto TapDevice::read_data(std::array<uint8_t, EthernetSizes::frame_max_size> &buffer) -> int const
{
    const size_t len = read(m_tap_fd, buffer.data(), sizeof(buffer));

    spdlog::trace("Read {} bytes", len);

    return len;
}
