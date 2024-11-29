#include "arp.hpp"
#include "ether-types.hpp"
#include "ethernet-frame.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/bin_to_hex.h"

#include <stdexcept>

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
    if (len < EthernetSizes::frame_min_size)
    {
        throw std::invalid_argument("Received a buffer too small to construct a valid ethernet frame!");
    }

    std::copy(buffer.begin(), buffer.begin() + EthPos::src_mac, m_dst_addr.begin());
    std::copy(buffer.begin() + EthPos::src_mac, buffer.begin() + EthPos::ether_type, m_src_addr.begin());
    std::copy(buffer.begin() + EthPos::ether_type, buffer.begin() + EthPos::payload, m_ether_type.begin());
    m_payload.insert(m_payload.end(), buffer.begin() + EthPos::payload, buffer.begin() + len);

    spdlog::debug("Received frame with the following fields: ");
    spdlog::debug("dst_addr: {}",   spdlog::to_hex(m_dst_addr));
    spdlog::debug("src_addr: {}",   spdlog::to_hex(m_src_addr));
    spdlog::debug("ether_type: {}", spdlog::to_hex(m_ether_type));
}

EthernetFrame::EthernetFrame(ArpPacket &&packet)
{
    const auto ipv4_payload = packet.arp_ipv4_payload();

    m_dst_addr   = ipv4_payload.dst_mac;
    m_src_addr   = ipv4_payload.src_mac;
    m_ether_type = EtherTypes::ARP;

    m_payload = packet.serialize();
}

EthernetFrame::~EthernetFrame()
{

}

auto EthernetFrame::handle() const -> bool
{
    return true;
}

auto EthernetFrame::serialize() const -> std::vector<uint8_t>
{
    auto size = EthernetSizes::addr_size * 2 +
                EthernetSizes::type_size +
                m_payload.size();

    std::vector<uint8_t> bytes{};
    bytes.reserve(size);
    bytes.insert(bytes.end(), m_dst_addr.begin(), m_dst_addr.end());
    bytes.insert(bytes.end(), m_src_addr.begin(), m_src_addr.end());
    bytes.insert(bytes.end(), m_ether_type.begin(), m_ether_type.end());
    bytes.insert(bytes.end(), m_payload.begin(), m_payload.end());

    return bytes;
}

auto EthernetFrame::invalid_frame_size(const size_t frame_size) -> bool const
{
    return (frame_size < EthernetSizes::frame_min_size ||
            frame_size > EthernetSizes::frame_max_size);
}
