#pragma once

#include <vector>
#include <stdint.h>

class ArpPacket
{
    public:
        ArpPacket(const std::vector<uint8_t> ethernet_payload);

    private:
        uint16_t             m_hardware_type{0};
        uint16_t             m_protocol_type{0}; // pos 2
        uint8_t              m_hardware_size{0}; // pos 4
        uint8_t              m_protocol_size{0}; // pos 5
        uint16_t             m_opcode{0};        // pos 6
        std::vector<uint8_t> m_payload{};        // pos 8
};
