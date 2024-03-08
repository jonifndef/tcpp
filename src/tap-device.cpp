#include "tap-device.hpp"

#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <linux/string.h>
#include <sys/ioctl.h>

TapDevice::TapDevice()
{

}

auto TapDevice::initialize_tap_device(std::string dev) -> bool
{
    struct ifreq interface_request;

    if ((m_tap_fd = open("/dev/net/tun", O_RDWR)) < 0)
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

TapDevice::~TapDevice()
{

}
