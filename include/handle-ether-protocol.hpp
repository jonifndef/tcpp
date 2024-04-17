#pragma once

#include "arp.hpp"
#include "ethernet-frame.hpp"

#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <stdint.h>

const std::map<std::array<uint8_t, EthernetSizes::type_size>, std::function<void(std::vector<uint8_t>)>> ETHER_PROTO_HANDLERS = {
    {{ 0x08, 0x00 }, [](std::vector<uint8_t> payload) {
            std::cout << "Handle IPV4!" << std::endl;
        }
    },
    {{ 0x08, 0x06 }, [](std::vector<uint8_t> payload) {
            ArpPacket arp_pkg{payload};
        }
    }
};
