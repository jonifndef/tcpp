#pragma once

#include "ethernet-frame.hpp"
#include "ip-datagram.hpp"

#include <array>
#include <vector>
#include <stdint.h>

class EthernetFrame;

struct ArpIPV4Payload
{
    MacAddr src_mac{};
    IpAddr  src_ip{};
    MacAddr dst_mac{};
    IpAddr  dst_ip{};

    bool operator==(ArpIPV4Payload const &other) const
    {
        return ((src_mac == other.src_mac) &&
                (src_ip  == other.src_ip)  &&
                (dst_mac == other.dst_mac) &&
                (dst_ip  == other.dst_ip)
               );
    }
};

namespace Opcode
{
    const uint16_t request   = 0x01;
    const uint16_t reply     = 0x02;
    const uint16_t r_request = 0x03;
    const uint16_t r_reply   = 0x04;
}

class ArpPacket
{
    public:
        ArpPacket(const std::vector<uint8_t> ethernet_payload);
        ArpPacket(const ArpIPV4Payload &&payload);
        auto handle() -> bool;

        auto arp_ipv4_payload() { return m_arp_ipv4_payload; };
        auto protocol_type()    { return m_protocol_type; };
        auto opcode()           { return m_opcode; };
        auto serialize() const -> std::vector<uint8_t>;

        friend class ArpTable;

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
