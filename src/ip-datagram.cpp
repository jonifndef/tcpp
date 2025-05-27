#include "ip-datagram.hpp"

#include "spdlog/spdlog.h"
//#include "spdlog/fmt/bin_to_hex.h"

#include <array>
#include <sstream>
#include <stdexcept>

namespace
{
    namespace IpPos
    {
        size_t dst_mac    = 0;
        size_t src_mac    = 6;
        size_t ether_type = 12;
        size_t payload    = 14;
    }
}

IpDatagram::IpDatagram(const std::vector<uint8_t> &buf)
{

}

auto IpDatagram::str_to_ip_addr(const std::string &addr_str) -> IpAddr
{
    IpAddr octets{};
    std::stringstream ss{addr_str};
    std::string segment{};
    uint8_t i = 0;

    while (getline(ss, segment, '.'))
    {
        auto num = std::stoi(segment);
        if (i >= 4 || num < 0 || num > 255)
        {
            throw std::invalid_argument("Invalid IP address");
        }

        octets[i++] = static_cast<uint8_t>(num);
    }

    return octets;
}
