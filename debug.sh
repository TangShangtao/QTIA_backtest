#!/bin/bash

# 检查 build 目录是否存在，如果不存在则创建并进入
if [ ! -d "build" ]; then
    mkdir build
fi
cd build

# 运行 CMake 和 Make
cmake ..
make

# 切换到 bin 目录并执行可执行文件
cd ../bin
./Crypto_backtest_cpp