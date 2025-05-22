#include "arp-handler.hpp"

ArpHandler::ArpHandler(std::shared_ptr<std::deque<ArpPacket>> arp_out_queue,
                       const MacAddr &mac,
                       const IpAddr &ip) :
                       m_arp_out_queue(arp_out_queue),
                       m_arp_table(mac, ip)
{

}

auto ArpHandler::handle_arp_packet(std::vector<uint8_t> &payload) -> bool
{
    ArpPacket arp_pkg{payload};
    if (!arp_pkg.handle())
        return false;

    auto reply_pkg = m_arp_table.update_arp_table(arp_pkg);
    if (reply_pkg)
    {
        m_arp_out_queue->push_back(reply_pkg.value());
    }

    return true;
}
