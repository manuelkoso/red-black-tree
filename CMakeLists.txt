cmake_minimum_required(VERSION 3.10)

project(red-black-tree)

add_subdirectory(test)
add_test(Test COMMAND RBT-Test)
enable_testing()

add_subdirectory(src)

add_executable(red-black-tree main.cpp)

target_link_libraries(red-black-tree PUBLIC RBTree)