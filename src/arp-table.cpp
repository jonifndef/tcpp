#include "arp-table.hpp"

#include "spdlog/spdlog.h"

auto ArpTable::update_arp_table(const ArpIPV4Payload &table_entry) -> void
{
    spdlog::debug("Updating arp table!");
//    //Merge_flag := false
//    //    If the pair <protocol type, sender protocol address> is
//    //        already in my translation table, update the sender
//    //        hardware address field of the entry with the new
//    //        information in the packet and set Merge_flag to true.
//    //    ?Am I the target protocol address?
//    //    Yes:
//    //      If Merge_flag is false, add the triplet <protocol type,
//    //          sender protocol address, sender hardware address> to
//    //          the translation table.
//    //      ?Is the opcode ares_op$REQUEST?  (NOW look at the opcode!!)
//    //      Yes:
//    //        Swap hardware and protocol fields, putting the local
//    //            hardware and protocol addresses in the sender fields.
//    //        Set the ar$op field to ares_op$REPLY
//    //        Send the packet to the (new) target hardware address on
//    //            the same hardware on which the request was received.
//    bool merge_flag{false};
//
//    if (m_table.count(std::make_pair<uint16_t, std::array<uint8_t, 4>>())
//
//
//
//    return;
}
