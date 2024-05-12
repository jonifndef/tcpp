#pragma once

#include <stdint.h>

#include <array>
#include <functional>
#include <map>
#include <deque>
//#include <iostream>

#include "arp-handler.hpp"
#include "tap-device.hpp"
#include "ethernet-frame.hpp"
//#include "ether-types.hpp"


class Tcpp
{
    public:
        Tcpp(const std::string &dev_name, const uint32_t num_packets);
        
        auto run() -> void;

    private:
        TapDevice m_tap_dev{"tap0"};
        uint32_t m_num_packets{};
        ArpHandler m_arp_handler;
        std::deque<ArpPacket> m_arp_out_queue;

        const std::map<std::array<uint8_t, EthernetSizes::type_size>, std::function<void(std::vector<uint8_t>)>> m_ether_proto_handlers;

        auto handle_frame(const EthernetFrame &frame) -> bool;
        auto send_reply() -> void;
};
