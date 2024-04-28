#pragma once

#include "arp-table.hpp"

class ArpHandler
{
    public:
        ArpHandler() = default;

        auto handle_arp_packet(std::vector<uint8_t> &payload) -> bool;

    private:
        ArpTable m_arp_table{};
};
