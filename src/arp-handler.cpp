#include "arp-handler.hpp"

ArpHandler::ArpHandler(std::unique_ptr<std::deque<ArpPacket>> arp_out_queue) :
    m_arp_out_queue(std::move(arp_out_queue))
{

}

auto ArpHandler::handle_arp_packet(std::vector<uint8_t> &payload) -> bool
{
    ArpPacket arp_pkg{payload};
    if (!arp_pkg.handle())
        return false;
    
    auto reply_payload = m_arp_table.update_arp_table(arp_pkg);
    if (reply_payload)
    {
        auto packet = ArpPacket(std::move(reply_payload.value()));
        //m_arp_out_queue->push_back(reply)
    }

    return true;
}
