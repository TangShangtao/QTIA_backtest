cmake_minimum_required(VERSION 3.10)
project(Crypto_backtest_cpp)
set(CMAKE_CXX_STANDARD 17)

include_directories(Backtest/Include/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
add_executable(Crypto_backtest_cpp main.cpp)
