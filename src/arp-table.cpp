#include "arp-table.hpp"

#include "spdlog/spdlog.h"

constexpr std::array<uint8_t, 4> my_ip{ 192, 168, 0, 1 };

auto ArpTable::update_arp_table(ArpPacket &packet) -> void
{
    auto table_entry = packet.m_arp_ipv4_payload;
    bool merge_flag{false};

    const auto key = std::pair<uint16_t, std::array<uint8_t, 4>>(packet.m_protocol_type, table_entry.src_ip);
    if (m_table.count(key))
    {
        m_table.at(key) = table_entry.src_mac;
        merge_flag = true;
    }

    if (table_entry.dst_ip != my_ip)
    {
        return;
    }

    if (!merge_flag)
    {
        m_table.emplace(std::pair<uint16_t, std::array<uint8_t, 4>>(packet.m_protocol_type, table_entry.src_ip), table_entry.src_mac);
    }

    //      ?Is the opcode ares_op$REQUEST?  (NOW look at the opcode!!)
    //      Yes:
    //        Swap hardware and protocol fields, putting the local
    //            hardware and protocol addresses in the sender fields.
    //        Set the ar$op field to ares_op$REPLY
    //        Send the packet to the (new) target hardware address on
    //            the same hardware on which the request was received.
    if (packet.m_opcode == Opcode::request)
    {
        spdlog::debug("Send arp reply");
    }
}
