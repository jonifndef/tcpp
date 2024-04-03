#pragma once

#include <array>
#include <vector>
#include <stdint.h>

//const static size_t eth_frame_max_size = 1514;

//inline const size_t eth_addr_size = 6;
namespace EthernetSizes
{
    const size_t frame_min_size = 64;
    const size_t frame_max_size = 1514;
    const size_t addr_size      = 6;
    const size_t type_size      = 2;
}

class EthernetFrame
{
    public:
        EthernetFrame(const std::array<uint8_t, EthernetSizes::frame_max_size>& buffer,
                      const size_t len);
        ~EthernetFrame();

        auto dst_addr()   const { return m_dst_addr; }
        auto src_addr()   const { return m_src_addr; }
        auto ether_type() const { return m_ether_type; }
        auto payload()    const { return m_payload; }

    private:
        std::array<uint8_t, EthernetSizes::addr_size> m_dst_addr{0};
        std::array<uint8_t, EthernetSizes::addr_size> m_src_addr{0};
        std::array<uint8_t, 2> m_ether_type{0};
        std::vector<uint8_t> m_payload;
        // crc not implemented yet
};
