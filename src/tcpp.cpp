#include "tcpp.hpp"
#include "tap-device.hpp"
#include "ethernet-frame.hpp"

Tcpp::Tcpp(const uint32_t num_packets) : m_num_packets(num_packets) 
{

}

Tcpp::~Tcpp()
{

}

auto Tcpp::run() -> void
{
    TapDevice tap_dev{};
    tap_dev.initialize("tap0");

    std::array<uint8_t, EthernetSizes::frame_max_size> buffer{};
    uint32_t num_packets_received = 0;

    // TODO: Add timeout, infinite loop
    while (num_packets_received < m_num_packets)
    {
        int bytes_read = tap_dev.read_data(buffer); 

        if (bytes_read >= EthernetSizes::frame_min_size)
        {
            EthernetFrame frame(buffer, bytes_read);

            num_packets_received++;
        }
    }
}
