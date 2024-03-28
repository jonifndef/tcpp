#include "ethernet-frame.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/bin_to_hex.h"

namespace
{
    namespace Pos
    {
        size_t dst_mac    = 0;
        size_t src_mac    = 6;
        size_t ether_type = 12;
        size_t payload    = 14;
    }
}

EthernetFrame::EthernetFrame(const std::array<uint8_t, EthernetSizes::eth_frame_max_size> &buffer)
{
    std::array<uint8_t, EthernetSizes::eth_addr_size> dst_addr{};
    std::array<uint8_t, EthernetSizes::eth_addr_size> src_addr{};

    std::copy(std::begin(buffer), std::begin(buffer) + Pos::src_mac, std::begin(dst_addr));
    std::copy(std::begin(buffer) + Pos::src_mac, std::begin(buffer) + Pos::ether_type, std::begin(src_addr));

    spdlog::info("dst_addr: {}", spdlog::to_hex(dst_addr));
    spdlog::info("src_addr: {}", spdlog::to_hex(src_addr));
}

EthernetFrame::~EthernetFrame()
{

}
