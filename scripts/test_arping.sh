#!/bin/bash

cleanup()
{
    kill "${TCPP_PID}" > /dev/null 2>&1
    kill "${ARPING_PID}" > /dev/null 2>&1
}

trap cleanup INT TERM EXIT

if [ ! -d "build" ]; then
    cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -G Ninja
fi

cmake --build build
sudo setcap CAP_NET_ADMIN=eip build/tcpp

./build/tcpp --log_level 1 &
TCPP_PID=$!

sudo ip link set tap0 up
sudo ip addr add 10.0.1.5/24 dev tap0
sudo arping -I tap0 10.0.1.5 &
ARPING_PID=$!

sleep 5
