#pragma once

#include "arp.hpp"

#include <stdint.h>
#include <array>
#include <vector>
#include <unordered_map>
#include <map>
#include <optional>

struct ArpTableEntry
{
    uint16_t protocol_type{};
    std::array<uint8_t, 6> mac{};
    std::array<uint8_t, 4> ip{};
};

class ArpTable
{
    public:
        ArpTable(const IpAddr &ip_addr);
        auto update_arp_table(ArpPacket &packet) -> std::optional<ArpIPV4Payload>;

    private:
        IpAddr m_ip_addr;
        std::map<std::pair<uint16_t, std::array<uint8_t, 4>>, std::array<uint8_t, 6>> m_table;
};
