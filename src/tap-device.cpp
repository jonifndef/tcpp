#include "tap-device.hpp"

#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <linux/string.h>
#include <sys/ioctl.h>

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
    int buffer[1000];

    const int len = read(m_tap_fd, buffer, sizeof(buffer));
    if (len > 0)
    {
        for (const auto byte : buffer)
        {
            std::cout << std::hex << std::uppercase << byte;
        }
        std::cout << std::endl;
    }

    return len;
}
