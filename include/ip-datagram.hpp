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

        auto version()     const { return m_version; }
        auto ihl()         const { return m_ihl; }
        auto tos()         const { return m_tos; }
        auto len()         const { return m_len; }
        auto id()          const { return m_id; }
        auto flags()       const { return m_flags; }
        auto frag_offset() const { return m_frag_offset; }
        auto ttl()         const { return m_ttl; }
        auto proto()       const { return m_proto; }
        auto csum()        const { return m_csum; }
        auto saddr()       const { return m_saddr; }
        auto daddr()       const { return m_daddr; }
        auto data()        const { return m_data; }

        static auto str_to_ip_addr(const std::string &addr_str) -> IpAddr;

    private:
        uint8_t  m_version;
        uint8_t  m_ihl;
        uint8_t  m_tos;
        uint16_t m_len;
        uint16_t m_id;
        uint8_t  m_flags;
        uint16_t m_frag_offset;
        uint8_t  m_ttl;
        uint8_t  m_proto;
        uint16_t m_csum;
        IpAddr m_saddr;
        IpAddr m_daddr;
        std::vector<uint8_t> m_data;
};
