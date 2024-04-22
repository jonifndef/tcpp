#pragma once

#include "arp.hpp"
#include "ethernet-frame.hpp"
#include "ether-types.hpp"

#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <stdint.h>

const std::map<std::array<uint8_t, EthernetSizes::type_size>, std::function<void(std::vector<uint8_t>)>> ETHER_PROTO_HANDLERS = {
    {EtherTypes::IPV4, [](std::vector<uint8_t> payload) {
            std::cout << "Handle IPV4!" << std::endl;
        }
    },
    {EtherTypes::ARP, [](std::vector<uint8_t> payload) {
            ArpPacket arp_pkg{payload};
            arp_pkg.handle();
        }
    }
};
