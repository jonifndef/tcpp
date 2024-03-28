#pragma once

#include <array>
#include <vector>
#include <stdint.h>

//const static size_t eth_frame_max_size = 1514;

//inline const size_t eth_addr_size = 6;
namespace EthernetSizes
{
    const size_t eth_frame_max_size = 1514;
    const size_t eth_addr_size      = 6;
    const size_t ether_type_size    = 2;
}

class EthernetFrame
{
    public:
        EthernetFrame(const std::array<uint8_t, EthernetSizes::eth_frame_max_size>& buffer);
        ~EthernetFrame();

    private:
        std::array<uint8_t, 6> m_dst_addr;
        std::array<uint8_t, 6> m_src_addr;
        std::array<uint8_t, 2> m_ether_type;
        std::vector<uint8_t> m_payload;
        // crc not implemented yet
};
