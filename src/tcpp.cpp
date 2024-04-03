#include "tcpp.hpp"
#include "tap-device.hpp"
#include "ethernet-frame.hpp"
#include "ether-types.hpp"

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
        int bytes_read = tap_dev.read_data(buffer); 

        if (bytes_read < EthernetSizes::frame_min_size ||
            bytes_read > EthernetSizes::frame_max_size)
        {
            // append to buffer if too small?
            continue;
        }

        EthernetFrame frame(buffer, bytes_read);

        if (frame.ether_type() == EtherTypes::IPV4)
        {
            num_packets_received++;

            spdlog::info("dst_addr: {}",   spdlog::to_hex(frame.dst_addr()));
            spdlog::info("src_addr: {}",   spdlog::to_hex(frame.src_addr()));
            spdlog::info("ether_type: {}", spdlog::to_hex(frame.ether_type()));
            spdlog::info("payload: {}",    spdlog::to_hex(frame.payload()));
        }
    }
}
