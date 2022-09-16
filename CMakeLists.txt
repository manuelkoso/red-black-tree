cmake_minimum_required(VERSION 3.10)
project(red-black-tree)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)

find_package(Catch2 3 REQUIRED)

add_executable(RBT-test test/test.cpp)
target_link_libraries(RBT-test PRIVATE Catch2::Catch2WithMain)
target_compile_options(RBT-test PRIVATE -Wall -pedantic -std=c++17)

add_executable(RBT-benchmark test/benchmark.cpp)
target_link_libraries(RBT-benchmark PRIVATE Catch2::Catch2WithMain)
target_compile_options(RBT-benchmark PRIVATE -Wall -pedantic -std=c++17)