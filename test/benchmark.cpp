#include "../include/RBTree.h"

#include <random>
#include <chrono>
#include <set>
#include <algorithm>

#define number_of_search 1000

void test_tree(int number_of_nodes, const std::vector<int> &random_values) {
    RBTree<int> tree;
    for (int i = 1; i <= number_of_nodes; ++i) {
        tree.insert(i);
    }
    auto begin = std::chrono::high_resolution_clock::now();
    for (auto value_to_find: random_values) {
        tree.contains(value_to_find);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::cout << total / double(number_of_search);
}

void test_set(int number_of_nodes, const std::vector<int> &random_values) {
    std::set<int> set;
    for (int i = 1; i <= number_of_nodes; ++i) {
        set.insert(i);
    }
    auto begin = std::chrono::high_resolution_clock::now();
    for (auto value_to_find: random_values) {
        set.find(value_to_find);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::cout << total / double(number_of_search);
}

std::vector<int> get_random_values(int number_of_nodes) {
    std::random_device rnd_device;
    std::mt19937 mersenne_engine{rnd_device()};
    std::vector<int> random_values(number_of_search);
    std::uniform_int_distribution<int> dist{1, number_of_nodes};
    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };
    generate(begin(random_values), end(random_values), gen);
    return random_values;
}

int main() {

    std::vector<int> numbers_of_nodes {1000, 2000, 3000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000};
    std::cout << "**** Searching nodes (values are in microseconds) ****" << std::endl;
    std::cout << "[Number of nodes] | [Tree] | [Set]" << std::endl;
    for(auto number_of_nodes : numbers_of_nodes) {
        std::cout << number_of_nodes << " | ";
        std::vector<int> random_values = get_random_values(number_of_nodes);
        test_tree(number_of_nodes, random_values);
        std::cout << " | ";
        test_set(number_of_nodes, random_values);
        std::cout << std::endl;
    }
}