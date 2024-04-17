#pragma once

#include <array>
#include <vector>
#include <stdint.h>

namespace EthernetSizes
{
    // ARP package is 42 bytes long, smallest one we support right now
    const size_t frame_min_size = 42;
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

        auto handle() -> bool const;

        static auto invalid_frame_size(const size_t frame_size) -> bool const;

    private:
        std::array<uint8_t, EthernetSizes::addr_size> m_dst_addr{0};
        std::array<uint8_t, EthernetSizes::addr_size> m_src_addr{0};
        std::array<uint8_t, EthernetSizes::type_size> m_ether_type{0};
        std::vector<uint8_t> m_payload{0};
        // crc not implemented yet
};
