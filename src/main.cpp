#include <iostream>
#include <unistd.h>

#include "argparse/argparse.hpp"

#include "tcpp.hpp"

struct MyArgs : public argparse::Args
{
    int &num_packets =
        kwarg("n,num_packets", "Number of packet to receive before exiting").set_default(10);
};

int main(int argc, char **argv)
{
    auto args = argparse::parse<MyArgs>(argc, argv);

    Tcpp tcpp_app(args.num_packets);

    tcpp_app.run();

    return 0;
}
