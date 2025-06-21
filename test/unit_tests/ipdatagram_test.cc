#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../include/ip-datagram.hpp"

TEST(EthernetframeTest, BasicAssertions) {
    const auto buf = std::vector<uint8_t>{ 0x7a, 0x31, 0x22, 0xbc, 0x5e, 0xb2, 0xc3, 0x19, 0x33, 0xa4, 0xde, 0x24, 0x11, 0x91, 0x6a, 0xdd, 0xee, 0x88, 0x99, 0x8a, 0xd5, 0x34, 0x77 };

    IpDatagram datagram{buf};

    EXPECT_EQ(datagram.version(), 0x07);
    EXPECT_EQ(datagram.ihl(), 0x0a);
    EXPECT_EQ(datagram.tos(), 0x31);
    EXPECT_EQ(datagram.len(), 0x22bc);
    EXPECT_EQ(datagram.id(), 0x5eb2);
    EXPECT_EQ(datagram.flags(), 0x06);
    EXPECT_EQ(datagram.frag_offset(), 0x319);
    EXPECT_EQ(datagram.ttl(), 0x33);
    EXPECT_EQ(datagram.proto(), 0xa4);
    EXPECT_EQ(datagram.csum(), 0xde24);

    const IpAddr expected_saddr{ 0x11, 0x6a, 0xdd, 0xee };
    EXPECT_EQ(datagram.saddr(), expected_saddr);

    const IpAddr expected_daddr{ 0x88, 0x99, 0x8a, 0xd5 };
    EXPECT_EQ(datagram.daddr(), expected_daddr);

    const std::vector<uint8_t> expected_data = { 0x34, 0x77 };
    EXPECT_EQ(datagram.data(), expected_data);
}
