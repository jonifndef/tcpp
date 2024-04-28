#include "tcpp.hpp"
#include "tap-device.hpp"
#include "ethernet-frame.hpp"
#include "ether-types.hpp"

#include <stdint.h>
#include <array>
#include <functional>
#include <map>
#include <stdint.h>
#include <iostream>

#include "tap-device.hpp"
#include "ether-types.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/bin_to_hex.h"

Tcpp::Tcpp(const std::string &dev_name, const uint32_t num_packets) :
    m_tap_dev(dev_name),
    m_num_packets(num_packets), 
    m_ether_proto_handlers(
        {
            {EtherTypes::IPV4, [](std::vector<uint8_t> payload) {
                    std::cout << "Handle IPV4!" << std::endl;
                }
            },
            {EtherTypes::ARP, [this](std::vector<uint8_t> payload) {
                    m_arp_handler.handle_arp_packet(payload);
                }
            }
        }
    )
{

}

auto Tcpp::run() -> void
{
    std::array<uint8_t, EthernetSizes::frame_max_size> buffer{};
    uint32_t num_packets_received{0};

    // TODO: Add timeout, infinite loop
    while (num_packets_received < m_num_packets)
    {
        uint32_t bytes_read = m_tap_dev.read_data(buffer);

        if (EthernetFrame::invalid_frame_size(bytes_read))
            continue;

        EthernetFrame frame(buffer, bytes_read);
        if (handle_frame(frame))
            num_packets_received++;
    }
}

auto Tcpp::handle_frame(const EthernetFrame &frame) -> bool
{
    if (m_ether_proto_handlers.count(frame.ether_type()))
    {
        m_ether_proto_handlers.at(frame.ether_type())(frame.payload());

        return true;
    }
    else
    {
        spdlog::debug("Ethertype {} is not supported!", spdlog::to_hex(frame.ether_type()));

        return false;
    }

}
