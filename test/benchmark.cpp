//
// Created by koso on 16/09/22.
//

#include "../include/RBTree.h"
#include <catch2/catch_all.hpp>

TEST_CASE("Benchmarking") {
    RBTree<int> my_tree;
    for (auto i = 0; i < 1000000; ++i) {
        my_tree.insert(i);
    }

    std::set<int> set;
    for (auto i = 0; i < 1000000; ++i) {
        set.insert(i);
    }

    BENCHMARK("Find 50000") {
                                return my_tree.contains(40);
                            };

    BENCHMARK("Find 100") {
                              return my_tree.contains(100);
                          };

    BENCHMARK("Find 50000") {
                                return set.find(40);
                            };

    BENCHMARK("Find 100") {
                              return set.find(100);
                          };

}