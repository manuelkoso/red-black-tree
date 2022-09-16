//
// Created by koso on 16/09/22.
//

#include "../include/RBTree.h"
#include <catch2/catch_all.hpp>

TEST_CASE("Benchmarking") {

    RBTree<int> tree;
    for (auto i = 0; i < 1000000; ++i) {
        tree.insert(i);
    }

    auto value = GENERATE(take(10, random(0, 1000000)));
    std::string name = "Find node: ";
    name += std::to_string(value);
    BENCHMARK(std::move(name)) {
                                   return tree.contains(value);
                               };

}