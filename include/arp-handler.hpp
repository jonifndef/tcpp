#pragma once

#include <memory>
#include <deque>

#include "arp-table.hpp"

//class ArpPacket;

class ArpHandler
{
    public:
        ArpHandler(std::unique_ptr<std::deque<ArpPacket>> arp_out_queue);
        auto handle_arp_packet(std::vector<uint8_t> &payload) -> bool;

    private:
        ArpTable m_arp_table;
        std::unique_ptr<std::deque<ArpPacket>> m_arp_out_queue;
};
