#include "arp-table.hpp"

#include "spdlog/spdlog.h"

constexpr std::array<uint8_t, 4> my_ip{ 192, 168, 0, 1 };

auto ArpTable::update_arp_table(ArpPacket &packet) -> void
{
    //Merge_flag := false
    //    If the pair <protocol type, sender protocol address> is
    //        already in my translation table, update the sender
    //        hardware address field of the entry with the new
    //        information in the packet and set Merge_flag to true.
    //    ?Am I the target protocol address?
    //    Yes:
    //      If Merge_flag is false, add the triplet <protocol type,
    //          sender protocol address, sender hardware address> to
    //          the translation table.
    //      ?Is the opcode ares_op$REQUEST?  (NOW look at the opcode!!)
    //      Yes:
    //        Swap hardware and protocol fields, putting the local
    //            hardware and protocol addresses in the sender fields.
    //        Set the ar$op field to ares_op$REPLY
    //        Send the packet to the (new) target hardware address on
    //            the same hardware on which the request was received.

    spdlog::debug("Updating arp table!");

    auto table_entry = packet.arp_ipv4_payload();
    bool merge_flag{false};

    const auto key = std::pair<uint16_t, std::array<uint8_t, 4>>(packet.protocol_type(), table_entry.src_ip);
    if (!m_table.count(key))
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
        m_table.emplace(std::pair<uint16_t, std::array<uint8_t, 4>>(packet.protocol_type(), table_entry.src_ip), table_entry.src_mac);
    }

    if (packet.opcode() == Opcode::request)
    {

    }
}
