#include "tap-device.hpp"

#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <linux/string.h>
#include <sys/ioctl.h>
#include <iomanip>

#include <net/ethernet.h>
#include <netinet/ether.h>

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
    uint8_t buffer[1000];
    std::ostream hexout(std::cout.rdbuf());
    hexout << std::hex << std::uppercase;

    const int len = read(m_tap_fd, buffer, sizeof(buffer));
    if (len > 0)
    {
        std::cout << "len is: " << len << std::endl;

        //for (const auto byte : buffer)
        //{
        //    hexout << static_cast<int>(byte);
        //}

        int i = 0;
        for (; i < 6; i++)
        {
            hexout << static_cast<int>(buffer[i]);
        }
        std::cout << std::endl << std::endl;

        for (; i < 12; i++)
        {
            hexout << static_cast<int>(buffer[i]);
        }
        std::cout << std::endl << std::endl;

        for (; i < 14; i++)
        {
            hexout << static_cast<int>(buffer[i]);
        }
        std::cout << std::endl;

        struct ether_addr des_eth_addr = {};
        struct ether_addr src_eth_addr = {};
        uint8_t des_addr[6];
        uint8_t src_addr[6];
        memcpy(des_addr, buffer, 6 * sizeof(uint8_t));
        memcpy(src_addr, buffer + 6, 6 * sizeof(uint8_t));
        for (int j = 0; j < 6; j++)
        {
            hexout << static_cast<int>(des_addr[j]);
        }
        std::cout << std::endl << std::endl;
        for (int k = 0; k < 6; k++)
        {
            hexout << static_cast<int>(src_addr[k]);
        }
        std::cout << std::endl << std::endl;

        memcpy(des_eth_addr.ether_addr_octet, des_addr, 6 * sizeof(uint8_t));
        memcpy(src_eth_addr.ether_addr_octet, src_addr, 6 * sizeof(uint8_t));

        std::cout << "hej" << std::endl;
        hexout << static_cast<int>(des_eth_addr.ether_addr_octet[0]) << static_cast<int>(des_eth_addr.ether_addr_octet[1]) << std::endl;
        hexout << static_cast<int>(src_eth_addr.ether_addr_octet[0]) << static_cast<int>(src_eth_addr.ether_addr_octet[1]) << std::endl;
        std::cout << "hej då" << std::endl;

        auto des_str = ether_ntoa(&des_eth_addr);
        std::cout << "eth header formatted: " << des_str << std::endl;
        auto src_str = ether_ntoa(&src_eth_addr);
        std::cout << "eth header formatted: " << src_str << std::endl;

        std::cout << std::endl << std::endl;
    }

    return len;
}
