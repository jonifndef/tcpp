#include "ip-datagram.hpp"

#include "spdlog/spdlog.h"
//#include "spdlog/fmt/bin_to_hex.h"

#include <array>
#include <sstream>
#include <stdexcept>

// std::bitset<4>  m_version; pos 0 > 4
// std::bitset<4>  m_ihl; pos 0 & 0x0f
// uint8_t         m_tos; pos 1
// uint16_t        m_len; pos 2
// uint16_t        m_id; pos 4
// std::bitset<3>  m_flags; pos 6 > 5
// std::bitset<13> m_frag_offset; pos 6 + 7 & 0x3fff
// uint8_t         m_ttl; pos 8
// uint8_t         m_proto; pos 9
// uint16_t        m_csum; pos 10
// uint32_t        m_saddr; pos 12
// uint32_t        m_daddr; pos 16
// std::vector<uint8_t> m_data; pos 20

namespace
{
    // Not needed, right?
    //namespace IpPos
    //{
    //    size_t version     = 0;
    //    size_t ihl         = 0;
    //    size_t tos         = 1;
    //    size_t len         = 2;
    //    size_t id          = 4;
    //    size_t flags       = 6;
    //    size_t frag_offset = 6;
    //    size_t ttl         = 8;
    //    size_t proto       = 9;
    //    size_t csum        = 10;
    //    size_t saddr       = 12;
    //    size_t daddr       = 16;
    //    size_t data        = 20;
    //}

    constexpr static size_t buf_min_size = 21; // 1 more than the header size, for the data
}

IpDatagram::IpDatagram(const std::vector<uint8_t> &buf)
{
    if (buf.size() < buf_min_size)
    {
        throw std::runtime_error("Buffer to small for ipv4 datagram");
    }

    // TBD: How to parse this? This method is more portable, and perhaps more "c++-esque", but it will be quite a hassle to serialize it again.
    // On the other hand, the "kernel way" of casting pointers is much more compact, but is not as portable and/or c++ compliant.

    m_version     = buf[0] >> 4;
    m_ihl         = buf[0] & 0x0f;
    m_tos         = buf[1];
    m_len         = (buf[2] << 8 | buf[3]);
    m_id          = (buf[4] << 8 | buf[5]);
    m_flags       = buf[6] >> 5;
    m_frag_offset = ((buf[6] << 8) & 0x1f) | buf[7];
    m_ttl         = buf[8];
    m_proto       = buf[9];
    m_csum        = (buf[10] << 8) | buf[11];
    std::copy(buf.begin() + 12, buf.begin() + 16, m_saddr.end());
    std::copy(buf.begin() + 16, buf.begin() + 20, m_daddr.end());
    m_data.insert(m_data.end(), buf.begin() + 20, buf.end());
}

auto IpDatagram::str_to_ip_addr(const std::string &addr_str) -> IpAddr
{
    IpAddr octets{};
    std::stringstream ss{addr_str};
    std::string segment{};
    uint8_t i = 0;

    while (getline(ss, segment, '.'))
    {
        auto num = std::stoi(segment);
        if (i >= 4 || num < 0 || num > 255)
        {
            throw std::invalid_argument("Invalid IP address");
        }

        octets[i++] = static_cast<uint8_t>(num);
    }

    return octets;
}
