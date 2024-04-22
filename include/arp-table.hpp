#pragma once

#include <stdint.h>
#include <array>
#include <vector>

struct ArpTableEntry
{
    uint16_t protocol_type{};
    std::array<uint8_t, 6> mac{};
    std::array<uint8_t, 4> ip{};
};

class ArpTable
{
    public:
        auto update_arp_table() -> void;

    private:
        std::vector<ArpTableEntry> m_table;
};
