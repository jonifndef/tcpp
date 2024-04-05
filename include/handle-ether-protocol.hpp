#pragma once

#include "ethernet-frame.hpp"

#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <stdint.h>

const std::map<std::array<uint8_t, EthernetSizes::type_size>, std::function<void()>> ETHER_PROTO_HANDLERS = {
    { { 0x08, 0x00 }, [](){ std::cout << "Handle IPV4!" << std::endl; } },
    { { 0x08, 0x06 }, [](){ std::cout << "Handle ARP!" << std::endl; } }
};
