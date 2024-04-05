#include "tcpp.hpp"
#include "tap-device.hpp"
#include "ethernet-frame.hpp"
#include "ether-types.hpp"
#include "handle-ether-protocol.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/bin_to_hex.h"

Tcpp::Tcpp(const uint32_t num_packets) : m_num_packets(num_packets) 
{

}

Tcpp::~Tcpp()
{

}

auto Tcpp::run() -> void
{
    TapDevice tap_dev{};
    tap_dev.initialize("tap0");

    std::array<uint8_t, EthernetSizes::frame_max_size> buffer{};
    uint32_t num_packets_received = 0;

    // TODO: Add timeout, infinite loop
    while (num_packets_received < m_num_packets)
    {
        uint32_t bytes_read = tap_dev.read_data(buffer);

        if (EthernetFrame::invalid_frame_size(bytes_read))
            continue;

        EthernetFrame frame(buffer, bytes_read);

        if (ETHER_PROTO_HANDLERS.count(frame.ether_type()))
        {
            ETHER_PROTO_HANDLERS.at(frame.ether_type())(); 
        }

        //if (frame.ether_type() == EtherTypes::IPV4)
        //{
        //    num_packets_received++;

        //    spdlog::info("dst_addr: {}",   spdlog::to_hex(frame.dst_addr()));
        //    spdlog::info("src_addr: {}",   spdlog::to_hex(frame.src_addr()));
        //    spdlog::info("ether_type: {}", spdlog::to_hex(frame.ether_type()));
        //    spdlog::info("payload: {}",    spdlog::to_hex(frame.payload()));
        //}
    }
}
