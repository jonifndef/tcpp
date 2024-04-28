#include "arp.hpp"
#include <arpa/inet.h>

#include "spdlog/spdlog.h"
#include "spdlog/fmt/bin_to_hex.h"

namespace
{
    namespace ArpPos
    {
        size_t hardware_type = 0;
        size_t protocol_type = 2;
        size_t hardware_size = 4;
        size_t protocol_size = 5;
        size_t opcode        = 6;
        size_t payload       = 8;
        size_t src_mac       = 0;
        size_t src_ip        = 6;
        size_t dst_mac       = 10;
        size_t dst_ip        = 16;
        size_t end_pos       = 20;
    }

    enum class HardwareType: uint16_t
    {
        Ethernet = 0x0001
    };

    enum class ProtocolType: uint16_t
    {
        IPV4 = 0x0800
    };
}

ArpPacket::ArpPacket(std::vector<uint8_t> ethernet_payload)
{
    std::memcpy(&m_hardware_type, ethernet_payload.data(), sizeof(m_hardware_type));
    m_hardware_type = ntohs(m_hardware_type);

    std::memcpy(&m_protocol_type, ethernet_payload.data() + ArpPos::protocol_type, sizeof(m_protocol_type));
    m_protocol_type = ntohs(m_protocol_type);

    std::memcpy(&m_hardware_size, ethernet_payload.data() + ArpPos::hardware_size, sizeof(m_hardware_size));
    std::memcpy(&m_protocol_size, ethernet_payload.data() + ArpPos::protocol_size, sizeof(m_protocol_size));

    std::memcpy(&m_opcode, ethernet_payload.data() + ArpPos::opcode, sizeof(m_opcode));
    m_opcode = ntohs(m_opcode);

    m_payload.insert(m_payload.end(), ethernet_payload.begin() + ArpPos::payload, ethernet_payload.end());

    spdlog::debug("m_hardware_type: {:04x}", m_hardware_type);
    spdlog::debug("m_protocol_type: {:04x}", m_protocol_type);
    spdlog::debug("m_hardware_size: {:02x}", m_hardware_size);
    spdlog::debug("m_protocol_size: {:02x}", m_protocol_size);
    spdlog::debug("m_opcode: {:04x}", m_opcode);
    spdlog::debug("m_payload: {}", spdlog::to_hex(m_payload));
}

auto ArpPacket::handle() -> bool
{
    // We only support ethernet for now
    if (m_hardware_type != static_cast<int>(HardwareType::Ethernet))
        return false;

    // We only support IPV4
    switch (m_protocol_type)
    {
        case static_cast<int>(ProtocolType::IPV4):
        {
            return (parse_arp_ipv4_payload());
        }

        // we only support Ethernet and IPV4 for now
        default:
        {
            return false;
        }
    }
}

auto ArpPacket::parse_arp_ipv4_payload() -> bool
{
    if (m_payload.size() < ArpPos::end_pos)
        return false;

    std::copy(m_payload.begin(),
              m_payload.begin() + ArpPos::src_ip,
              m_arp_ipv4_payload.src_mac.begin());
    std::copy(m_payload.begin() + ArpPos::src_ip,
              m_payload.begin() + ArpPos::dst_mac,
              m_arp_ipv4_payload.src_ip.begin());
    std::copy(m_payload.begin() + ArpPos::dst_mac,
              m_payload.begin() + ArpPos::dst_ip,
              m_arp_ipv4_payload.dst_mac.begin());
    std::copy(m_payload.begin() + ArpPos::dst_ip,
              m_payload.end(),
              m_arp_ipv4_payload.dst_ip.begin());
   
    spdlog::debug("Arp payload src_mac: {}", spdlog::to_hex(m_arp_ipv4_payload.src_mac));
    spdlog::debug("Arp payload src_ip: {}", spdlog::to_hex(m_arp_ipv4_payload.src_ip));
    spdlog::debug("Arp payload dst_mac: {}", spdlog::to_hex(m_arp_ipv4_payload.dst_mac));
    spdlog::debug("Arp payload dst_ip: {}", spdlog::to_hex(m_arp_ipv4_payload.dst_ip));

    return true;
}
