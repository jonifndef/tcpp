#include <iostream>
#include <unistd.h>

#include "tap-device.hpp"

int main(int argc, char **argv)
{
    TapDevice::instance().initialize_tap_device("tap0");

    int len = 0;
    while (len < 100)
    {
        len += TapDevice::instance().read_data();

        usleep(2);
    }

    TapDevice::instance().close_tap_device();

    return 0;
}
