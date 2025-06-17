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

cmake --build build || exit -1
sudo setcap CAP_NET_ADMIN=eip build/src/tcpp

./build/src/tcpp --log_level 1 --num_packets 20 &
TCPP_PID=$!

sleep 0.5

sudo arping -I tap0 10.0.1.5 &
ARPING_PID=$!

sleep 5
