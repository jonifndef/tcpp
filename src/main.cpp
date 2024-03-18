#include <iostream>
#include <unistd.h>

#include "tap-device.hpp"

int main(int argc, char **argv)
{
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
