cmake_minimum_required(VERSION 3.10)

project(red-black-tree)

add_subdirectory(test)
add_test(Test COMMAND RBT-Test)
enable_testing()
