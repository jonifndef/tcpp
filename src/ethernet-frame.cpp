#include "ethernet-frame.hpp"

namespace
{
    namespace EthPos
    {
        size_t dst_mac    = 0;
        size_t src_mac    = 6;
        size_t ether_type = 12;
        size_t payload    = 14;
    }
}

EthernetFrame::EthernetFrame(const std::array<uint8_t, EthernetSizes::frame_max_size> &buffer,
                             const size_t len)
{
    std::copy(buffer.begin(), buffer.begin() + EthPos::src_mac, m_dst_addr.begin());
    std::copy(buffer.begin() + EthPos::src_mac, buffer.begin() + EthPos::ether_type, m_src_addr.begin());
    std::copy(buffer.begin() + EthPos::ether_type, buffer.begin() + EthPos::payload, m_ether_type.begin());
    m_payload.insert(m_payload.end(), buffer.begin() + 14, buffer.begin() + len);
}

EthernetFrame::~EthernetFrame()
{

}
