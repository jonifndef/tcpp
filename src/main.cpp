#include <iostream>
#include <unistd.h>

#include "argparse/argparse.hpp"

#include "tap-device.hpp"

struct MyArgs : public argparse::Args
{
    int &num_packets = kwarg("n,num_packets", "Number of packet to receive before exiting").set_default(5);
};

int main(int argc, char **argv)
{
    auto args = argparse::parse<MyArgs>(argc, argv);

    TapDevice tap_dev{};
    tap_dev.initialize("tap0");

    int len = 0;
    while (len < 4000)
    {
        len += tap_dev.read_data();

        usleep(2);
    }

    return 0;
}
