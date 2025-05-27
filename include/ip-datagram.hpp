#pragma once

#include <stdint.h>

#include <array>
#include <bitset>
#include <string>
#include <vector>

using IpAddr = std::array<uint8_t, 4>;

class IpDatagram
{
    public:
        IpDatagram(const std::vector<uint8_t> &buf);
        static auto str_to_ip_addr(const std::string &addr_str) -> IpAddr;

    private:
        std::bitset<4>  m_version;
        std::bitset<4>  m_ihl;
        uint8_t         m_tos;
        uint16_t        m_len;
        uint16_t        m_id;
        std::bitset<3>  m_flags;
        std::bitset<13> m_frag_offset;
        uint8_t         m_ttl;
        uint8_t         m_proto;
        uint16_t        m_csum;
        uint32_t        m_saddr;
        uint32_t        m_daddr;
        std::vector<uint8_t> m_data;
};
