#pragma once

#include "arp.hpp"

#include <stdint.h>
#include <array>
#include <vector>
#include <unordered_map>

struct ArpTableEntry
{
    uint16_t protocol_type{};
    std::array<uint8_t, 6> mac{};
    std::array<uint8_t, 4> ip{};
};

class ArpTable
{
    public:
        ArpTable() = default;
        auto update_arp_table(const ArpIPV4Payload &table_entry) -> void;

    private:
        //std::unordered_map<std::pair<uint16_t, std::array<uint8_t, 4>>, std::array<uint8_t, 6>> m_table;
};
