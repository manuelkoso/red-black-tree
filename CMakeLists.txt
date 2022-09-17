cmake_minimum_required(VERSION 3.10)
project(red-black-tree)

set(CMAKE_CXX_STANDARD 14)

add_executable(RBT-test test/test.cpp)
target_compile_options(RBT-test PRIVATE -Wall -pedantic)

add_executable(RBT-benchmark test/benchmark.cpp)
target_compile_options(RBT-benchmark PRIVATE -Wall -pedantic -DNDEBUG)