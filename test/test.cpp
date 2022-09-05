#define CATCH_CONFIG_MAIN

#include "../include/catch.hpp"
#include "../include/RBTree.h"

TEST_CASE("Red black tree initialization") {
    SECTION("Default constructor") {
        RBTree<int> tree;
        bool check = tree.begin() == tree.end();
        REQUIRE(check);
    }
}

TEST_CASE("Insertion") {
    SECTION("Root insertion") {
        RBTree<int> tree;
        tree.insert(3);
        bool check = *tree.begin() == 3;
        REQUIRE(check);
    }SECTION("Custom constructor") {
        RBTree<long> tree{-1, -2, 0, 1, 2, 3};
        long expected_value = -2;
        for (auto node_value: tree) {
            REQUIRE(node_value == expected_value);
            expected_value++;
        }
        RBTree<int> second_tree{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        expected_value = 0;
        for (auto node_value: second_tree) {
            REQUIRE(node_value == expected_value);
            expected_value++;
        }
    }SECTION("1000 nodes") {
        RBTree<int> tree;
        for (auto i = -500; i < 500; i++) {
            tree.insert(i);
        }
        int expected_value = -500;
        for (auto node_value: tree) {
            REQUIRE(node_value == expected_value);
            expected_value++;
        }
    }
}


TEST_CASE("Searching") {
    RBTree<int> tree;
    for (auto i = -500; i < 500; i++) {
        tree.insert(i);
    }
    SECTION("Find existing values") {
        REQUIRE(tree.contains(333));
        REQUIRE(tree.contains(-22));
        REQUIRE(tree.contains(499));
        REQUIRE(tree.contains(-500));
        REQUIRE(tree.contains(-77));
        REQUIRE(tree.contains(234));
        REQUIRE(tree.contains(400));
    }
    SECTION("Find existing values") {
        REQUIRE(!tree.contains(3333));
        REQUIRE(!tree.contains(-3322));
        REQUIRE(!tree.contains(500));
        REQUIRE(!tree.contains(-501));
        REQUIRE(!tree.contains(-7745));
        REQUIRE(!tree.contains(2333));
        REQUIRE(!tree.contains(-2234));
    }
}
