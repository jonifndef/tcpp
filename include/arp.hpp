#pragma once

#include <array>
#include <vector>
#include <stdint.h>

struct ArpIPV4Payload
{
    std::array<uint8_t, 6> src_mac{};
    std::array<uint8_t, 4> src_ip{};
    std::array<uint8_t, 6> dst_mac{};
    std::array<uint8_t, 4> dst_ip{};
};

class ArpPacket
{
    public:
        ArpPacket(const std::vector<uint8_t> ethernet_payload);
        auto handle() -> bool;
        auto arp_ipv4_payload() { return m_arp_ipv4_payload; }

    private:
        uint16_t             m_hardware_type{0};
        uint16_t             m_protocol_type{0}; // pos 2
        uint8_t              m_hardware_size{0}; // pos 4
        uint8_t              m_protocol_size{0}; // pos 5
        uint16_t             m_opcode{0};        // pos 6
        std::vector<uint8_t> m_payload{};        // pos 8 <-- change this to ArpPayload object

        ArpIPV4Payload       m_arp_ipv4_payload{};

        auto parse_arp_ipv4_payload() -> bool;
};
