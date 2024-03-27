#include "tap-device.hpp"

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

TapDevice::TapDevice()
{

}

TapDevice::~TapDevice()
{
    std::cout << "Calling TapDevice destructor!" << std::endl;

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
    std::array<uint8_t, 1000> buffer{};

    const int len = read(m_tap_fd, buffer.data(), sizeof(buffer));

    if (len > 0)
    {
        spdlog::info("Read {} bytes", len);

        std::array<uint8_t, 6> dst_addr{};
        std::array<uint8_t, 6> src_addr{};

        std::copy(std::begin(buffer), std::begin(buffer) + 6, std::begin(dst_addr));
        std::copy(std::begin(buffer) + 6, std::begin(buffer) + 12, std::begin(src_addr));

        spdlog::info("dst_addr: {}", spdlog::to_hex(dst_addr));
        spdlog::info("src_addr: {}", spdlog::to_hex(src_addr));
    }

    return len;
}
