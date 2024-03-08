#include "tap-device.hpp"

#include <iostream>

int main(int argc, char **argv)
{
    TapDevice::instance().initialize_tap_device("tap0");

    return 0;
}
