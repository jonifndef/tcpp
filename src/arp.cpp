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
    }

    const size_t arp_pkg_min_size = 10; // don't know the actual min size yet
}

ArpPacket::ArpPacket(std::vector<uint8_t> ethernet_payload)
{
    ethernet_payload.erase(ethernet_payload.begin());
    std::memcpy(&m_hardware_type, ethernet_payload.data(), sizeof(m_hardware_type));
    m_hardware_type = ntohs(m_hardware_type);

    std::memcpy(&m_protocol_type, ethernet_payload.data() + ArpPos::protocol_type, sizeof(m_protocol_type));
    m_protocol_type = ntohs(m_protocol_type);

    std::memcpy(&m_hardware_size, ethernet_payload.data() + ArpPos::hardware_size, sizeof(m_hardware_size));
    std::memcpy(&m_protocol_size, ethernet_payload.data() + ArpPos::protocol_size, sizeof(m_protocol_size));

    std::memcpy(&m_opcode, ethernet_payload.data() + ArpPos::opcode, sizeof(m_opcode));
    m_opcode = ntohs(m_opcode);

    m_payload.insert(m_payload.end(), ethernet_payload.begin() + ArpPos::payload, ethernet_payload.end());

    spdlog::debug("Complete arp packet: {}", spdlog::to_hex(ethernet_payload));
    spdlog::debug("m_hardware_type: {:04x}", m_hardware_type);
    spdlog::debug("m_protocol_type: {:04x}", m_protocol_type);
    spdlog::debug("m_hardware_size: {:02x}", m_hardware_size);
    spdlog::debug("m_protocol_size: {:02x}", m_protocol_size);
    spdlog::debug("m_opcode: {:04x}", m_opcode);
    spdlog::debug("m_payload: {}", spdlog::to_hex(m_payload));
}
