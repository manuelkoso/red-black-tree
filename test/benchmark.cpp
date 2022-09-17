#define CATCH_CONFIG_MAIN

#include "../include/RBTree.h"
#include "../include/catch.hpp"

#include <random>
#include <chrono>
#include <set>
#include <algorithm>

void test_tree(int number_of_nodes, std::mt19937 mersenne_engine) {
    int number_of_searching = 500;
    RBTree<int> tree;
    std::vector<int> random_values(number_of_searching);
    for (int i = 1; i <= number_of_nodes; ++i) {
        tree.insert(i);
    }
    std::uniform_int_distribution<int> dist{1, number_of_nodes};
    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };
    generate(begin(random_values), end(random_values), gen);

    auto begin = std::chrono::high_resolution_clock::now();
    for (auto value_to_find: random_values) {
        tree.contains(value_to_find);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::cout << number_of_nodes << " nodes: " << total / double(number_of_searching) << std::endl;
}

void test_set(int number_of_nodes, std::mt19937 mersenne_engine) {
    int number_of_searching = 500;
    std::set<int> set;
    std::vector<int> random_values(number_of_searching);
    for (int i = 1; i <= number_of_nodes; ++i) {
        set.insert(i);
    }
    std::uniform_int_distribution<int> dist{1, number_of_nodes};
    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };
    generate(begin(random_values), end(random_values), gen);

    auto begin = std::chrono::high_resolution_clock::now();
    for (auto value_to_find: random_values) {
        set.find(value_to_find);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::cout << number_of_nodes << " nodes: " << total / double(number_of_searching) << std::endl;
}

TEST_CASE("Benchmarking") {

    std::random_device rnd_device;
    std::mt19937 mersenne_engine{rnd_device()};  // Generates random integers

    SECTION("Searching nodes") {
        SECTION("My tree") {
            std::cout << "My tree" << std::endl;
            test_tree(1000, mersenne_engine);
            test_tree(2000, mersenne_engine);
            test_tree(5000, mersenne_engine);
            test_tree(10000, mersenne_engine);
            test_tree(50000, mersenne_engine);
            test_tree(100000, mersenne_engine);
            test_tree(200000, mersenne_engine);
            test_tree(500000, mersenne_engine);
        }

        SECTION("Set") {
            std::cout << "Set" << std::endl;
            test_set(1000, mersenne_engine);
            test_set(2000, mersenne_engine);
            test_set(5000, mersenne_engine);
            test_set(10000, mersenne_engine);
            test_set(50000, mersenne_engine);
            test_set(100000, mersenne_engine);
            test_set(200000, mersenne_engine);
            test_set(500000, mersenne_engine);
        }
    }
}