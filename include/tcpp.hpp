#pragma once

#include <algorithm>
#include <stdint.h>

#include <array>
#include <functional>
#include <map>
#include <deque>

#include "arp-handler.hpp"
#include "tap-device.hpp"
#include "ethernet-frame.hpp"

class Tcpp
{
    public:
        Tcpp(const std::string &dev_name,
             const uint32_t num_packets,
             const std::string &mac_address,
             const std::string &ip_address);

        auto run() -> void;

    private:
        TapDevice m_tap_dev;
        uint32_t m_num_packets{};
        std::shared_ptr<std::deque<ArpPacket>> m_arp_out_queue;
        MacAddr m_mac_addr;
        IpAddr m_ip_addr;
        ArpHandler m_arp_handler;

        const std::map<std::array<uint8_t, EthernetSizes::type_size>, std::function<void(std::vector<uint8_t>)>> m_ether_proto_handlers;

        auto handle_frame(const EthernetFrame &frame) -> bool;
        auto send_reply() -> void;
};
