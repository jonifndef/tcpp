#include "arp-table.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/bin_to_hex.h"

ArpTable::ArpTable(const MacAddr &mac, const IpAddr &ip) : m_mac_addr(mac), m_ip_addr(ip)
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

    if (packet.m_opcode == Opcode::request)
    {
        ArpPacket reply{std::move(packet)};
        reply.m_opcode = Opcode::reply;
        reply.m_arp_ipv4_payload = {
            .src_mac = m_mac_addr,
            .src_ip  = arp_payload.dst_ip,
            .dst_mac = arp_payload.src_mac,
            .dst_ip  = arp_payload.src_ip
        };

        return reply;
    }

    return {};
}
