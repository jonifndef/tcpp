#include "ip-packet.hpp"

#include "spdlog/spdlog.h"
//#include "spdlog/fmt/bin_to_hex.h"

#include <array>
#include <sstream>
#include <stdexcept>

auto IpPacket::str_to_ip_addr(const std::string &addr_str) -> IpAddr
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
