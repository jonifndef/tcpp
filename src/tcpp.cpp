#include "tcpp.hpp"

#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <stdint.h>

#include "ether-types.hpp"
#include "ethernet-frame.hpp"
#include "ip-datagram.hpp"
#include "tap-device.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/bin_to_hex.h"

Tcpp::Tcpp(const std::string &dev_name,
           const uint32_t num_packets,
           const std::string &mac_address,
           const std::string &ip_address) :
    m_tap_dev(dev_name, mac_address, ip_address),
    m_num_packets(num_packets),
    m_arp_out_queue(std::make_shared<std::deque<ArpPacket>>()),
    m_mac_addr(EthernetFrame::str_to_mac_addr(mac_address)),
    m_ip_addr(IpDatagram::str_to_ip_addr(ip_address)),
    m_arp_handler(m_arp_out_queue, m_mac_addr, m_ip_addr),
    m_ether_proto_handlers(
        {
            {EtherTypes::IPV4, [](std::vector<uint8_t> payload) {
                    std::cout << "Handle IPV4!" << std::endl;
                    auto datagram = IpDatagram(payload);
                }
            },
            {EtherTypes::ARP, [this](std::vector<uint8_t> payload) {
                    std::cout << "Handle arp!" << std::endl;
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

        send_reply();
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

auto Tcpp::send_reply() -> void
{
    if (m_arp_out_queue->empty())
    {
        return;
    }

    auto packet = m_arp_out_queue->front();
    m_arp_out_queue->pop_front();

    const EthernetFrame frame{std::move(packet)};

    m_tap_dev.send_data(std::move(frame));
}
