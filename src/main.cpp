#include "tap-device.hpp"

int main(int argc, char **argv)
{
    TapDevice tapDevice;
    tapDevice.initialize_tap_device("tun1");

    return 0;
}
