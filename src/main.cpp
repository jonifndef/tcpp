#include <iostream>
#include <unistd.h>

#include "argparse/argparse.hpp"
#include "spdlog/spdlog.h"

#include "tcpp.hpp"

struct MyArgs : public argparse::Args
{
    int &num_packets =
        kwarg("n,num_packets", "Number of packet to receive before exiting").set_default(10);
    int &log_level =
        kwarg("l,log_level", "Log level for application, levels 0-6 are available").set_default(2);
};

int main(int argc, char **argv)
{
    auto args = argparse::parse<MyArgs>(argc, argv);

    spdlog::set_level(static_cast<spdlog::level::level_enum>(args.log_level));

    Tcpp tcpp_app("tap0", args.num_packets);
    tcpp_app.run();

    return 0;
}
