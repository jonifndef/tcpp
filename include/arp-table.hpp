#pragma once

#include "arp.hpp"

#include <stdint.h>
#include <array>
#include <vector>
#include <unordered_map>
#include <map>
#include <optional>

class ArpTable
{
    public:
        ArpTable(const IpAddr &ip_addr);
        auto update_arp_table(const ArpPacket &packet) -> std::optional<ArpPacket>;

    private:
        IpAddr m_ip_addr;
        std::map<std::pair<uint16_t, IpAddr>, MacAddr> m_table;
};
