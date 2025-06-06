#pragma once

#include <memory>
#include <deque>

#include "arp-table.hpp"

//class ArpPacket;

class ArpHandler
{
    public:
        ArpHandler(std::shared_ptr<std::deque<ArpPacket>> arp_out_queue, const MacAddr &mac, const IpAddr &ip);
        auto handle_arp_packet(std::vector<uint8_t> &payload) -> bool;

    private:
        std::shared_ptr<std::deque<ArpPacket>> m_arp_out_queue;
        ArpTable m_arp_table;
};
