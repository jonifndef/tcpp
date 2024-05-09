#include "arp-handler.hpp"

auto ArpHandler::handle_arp_packet(std::vector<uint8_t> &payload) -> bool
{
    ArpPacket arp_pkg{payload};
    if (!arp_pkg.handle())
        return false;
    
    m_arp_table.update_arp_table(arp_pkg);

    return true;
}
