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

    namespace Pos
    {
        size_t dst_mac    = 0;
        size_t src_mac    = 6;
        size_t ether_type = 12;
        size_t payload    = 14;
    }
}

TapDevice::TapDevice()
{

}

TapDevice::~TapDevice()
{
    close(m_tap_fd);
}

auto TapDevice::initialize(std::string dev) -> bool
{
    struct ifreq interface_request;

    if ((m_tap_fd = open(TUN_DEVICE.c_str(), O_RDWR)) < 0)
    {
        std::cout << "Cannot open tap device" << std::endl;

        return false;
    }

    memset(&interface_request, 0, sizeof(interface_request));

    interface_request.ifr_flags = IFF_TAP | IFF_NO_PI;

    if (!dev.empty())
    {
	    strncpy(interface_request.ifr_name, dev.c_str(), IFNAMSIZ);
    }

    if (ioctl(m_tap_fd, TUNSETIFF, (void*) &interface_request) < 0)
    {
	    close(m_tap_fd);

	    return false;
    }

    dev = interface_request.ifr_name;

    return true;
}

auto TapDevice::read_data() -> int
{
    std::array<uint8_t, EthernetSizes::eth_frame_max_size> buffer{};

    const int len = read(m_tap_fd, buffer.data(), sizeof(buffer));

    if (len > 0)
    {
        spdlog::info("Read {} bytes", len);

        EthernetFrame frame(buffer);
    }

    return len;
}
