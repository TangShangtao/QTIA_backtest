#!/bin/bash
if [ ! -d "build" ]; then
    mkdir build
fi
if [ ! -d "bin" ]; then
    mkdir bin
fi
if [ ! -d "bin/config" ]; then
    mkdir bin/config
fi
cp ./Backtest/Common/apiconfig.json ./bin/config
cp ./Backtest/Common/backtestconfig.yaml ./bin/config

cd build && cmake ..
make -j

cd ../bin
./Crypto_backtest_cpp