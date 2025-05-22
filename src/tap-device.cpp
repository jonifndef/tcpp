#include "tap-device.hpp"
#include "ethernet-frame.hpp"

#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <linux/string.h>
#include <sys/ioctl.h>
#include <netinet/in.h>

#include "spdlog/fmt/bin_to_hex.h"
#include "spdlog/spdlog.h"

namespace
{
    const std::string TUN_DEVICE = "/dev/net/tun";
}

TapDevice::TapDevice(const std::string &devname,
                     const std::string &mac_addr,
                     const std::string &ip_addr)
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

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        throw std::runtime_error("Cannot create socket while setting interface up");
    }

    if (ioctl(fd, SIOCGIFFLAGS, &interface_request) != -1)
    {
        interface_request.ifr_flags |= (IFF_UP | IFF_RUNNING);
        if (ioctl(fd, SIOCSIFFLAGS, &interface_request) == -1)
        {
            close(fd);

            throw std::runtime_error("Cannot run ioctl on socket to set interface up");
        }
    }
    else
    {
        close(fd);

        throw std::runtime_error("Cannot run ioctl on socket to get flags");
    }

    struct sockaddr_in* addr = (struct sockaddr_in*)&interface_request.ifr_addr;
    addr->sin_family = AF_INET;
    inet_pton(AF_INET, ip_addr.c_str(), &addr->sin_addr);

    if (ioctl(fd, SIOCSIFADDR, &interface_request) == -1)
    {
        close(fd);

        throw std::runtime_error("Cannot run ioctl on socket to set ip addr");
    }

    struct sockaddr_in netmask;
    netmask.sin_family = AF_INET;
    inet_pton(AF_INET, "255.255.255.0", &netmask.sin_addr);

    memcpy(&interface_request.ifr_netmask, &netmask, sizeof(struct sockaddr_in));

    if (ioctl(fd, SIOCSIFNETMASK, &interface_request) == -1)
    {
        close(fd);

        throw std::runtime_error("Cannot run ioctl on socket to set netmask");
    }

    MacAddr mac_addr_bytes = EthernetFrame::str_to_mac_addr(mac_addr);

    struct sockaddr sa;
    sa.sa_family = AF_LOCAL;
    memcpy(sa.sa_data, mac_addr_bytes.data(), 6);

    memcpy(&interface_request.ifr_hwaddr, &sa, sizeof(sa));
    if (ioctl(fd, SIOCSIFHWADDR, &interface_request) == -1) {
        close(fd);

        throw std::runtime_error("Failed to set MAC address");
    }

    close(fd);
}

TapDevice::~TapDevice()
{
    close(m_tap_fd);
}

auto TapDevice::read_data(std::array<uint8_t, EthernetSizes::frame_max_size> &buffer) const -> int
{
    const size_t len = read(m_tap_fd, buffer.data(), sizeof(buffer));

    spdlog::trace("Read {} bytes", len);

    return len;
}

auto TapDevice::send_data(const EthernetFrame &&frame) const -> void
{
    const auto bytes = frame.serialize();
    const size_t len = write(m_tap_fd, bytes.data(), bytes.size());

    spdlog::debug("Wrote {} bytes:", len);
    spdlog::debug("{}", spdlog::to_hex(bytes));
}

