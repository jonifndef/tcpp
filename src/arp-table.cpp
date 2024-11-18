#include "arp-table.hpp"

#include "spdlog/spdlog.h"

ArpTable::ArpTable(const IpAddr &ip_addr) : m_ip_addr(ip_addr)
{

}

auto ArpTable::update_arp_table(const ArpPacket &packet) -> std::optional<ArpPacket>
{
    auto arp_payload{packet.m_arp_ipv4_payload};
    auto merge_flag{false};

    const auto key = std::pair<uint16_t, IpAddr>(packet.m_protocol_type, arp_payload.src_ip);
    if (m_table.count(key))
    {
        m_table.at(key) = arp_payload.src_mac;
        merge_flag = true;
    }

    if (arp_payload.dst_ip != m_ip_addr)
    {
        return {};
    }

    if (!merge_flag)
    {
        m_table.emplace(std::pair<uint16_t, IpAddr>(packet.m_protocol_type, arp_payload.src_ip), arp_payload.src_mac);
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
        ArpPacket reply{std::move(packet)};
        reply.m_opcode = Opcode::reply;
        reply.m_arp_ipv4_payload = {
            .src_mac = arp_payload.dst_mac,
            .src_ip  = arp_payload.dst_ip,
            .dst_mac = arp_payload.src_mac,
            .dst_ip  = arp_payload.src_ip
        };

        return reply;
    }

    return {};
}
