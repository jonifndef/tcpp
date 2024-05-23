#pragma once

#include <stdint.h>

#include <array>
#include <string>

using IpAddr = std::array<uint8_t, 4>;

class IpPacket
{
    public:
        static auto str_to_ip_addr(const std::string &addr_str) -> IpAddr;
};
