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
    }SECTION("100 nodes") {
        RBTree<int> tree;
        for (auto i = -50; i < 50; i++) {
            tree.insert(i);
        }
        int expected_value = -50;
        for (auto node_value: tree) {
            REQUIRE(node_value == expected_value);
            expected_value++;
        }
    }
}

TEST_CASE("Searching") {
    RBTree<int> tree;
    for (auto i = -50; i < 50; i++) {
        tree.insert(i);
    }
    SECTION("Find existing nodes") {
        REQUIRE(tree.contains(33));
        REQUIRE(tree.contains(-22));
        REQUIRE(tree.contains(49));
        REQUIRE(tree.contains(-50));
        REQUIRE(tree.contains(-7));
        REQUIRE(tree.contains(23));
        REQUIRE(tree.contains(40));
    }
    SECTION("Find not existing nodes") {
        REQUIRE(!tree.contains(333));
        REQUIRE(!tree.contains(-332));
        REQUIRE(!tree.contains(50));
        REQUIRE(!tree.contains(-51));
        REQUIRE(!tree.contains(-774));
        REQUIRE(!tree.contains(233));
        REQUIRE(!tree.contains(-2234));
    }
}

SCENARIO("Deletion") {

    RBTree<int> tree;
    for (auto i = -50; i < 50; i++) {
        tree.insert(i);
    }
    tree.erase(40);
    tree.erase(33);
    tree.erase(-40);
    tree.erase(49);
    tree.erase(0);
    SECTION("Remove existing nodes") {
        REQUIRE(!tree.contains(40));
        REQUIRE(!tree.contains(33));
        REQUIRE(!tree.contains(-40));
        REQUIRE(!tree.contains(49));
        REQUIRE(!tree.contains(0));
    } SECTION("Remove not existing nodes") {
        REQUIRE(!tree.erase(40));
        REQUIRE(!tree.erase(33));
        REQUIRE(!tree.erase(-40));
        REQUIRE(!tree.erase(49));
        REQUIRE(!tree.erase(0));
    }
}

TEST_CASE("Copy semantics") {
    RBTree<int> tree;
    for (auto i = -50; i < 50; i++) {
        tree.insert(i);
    }

    RBTree<int> copy_ass_tree = tree;
    RBTree<int> copy_constructor_tree {tree};

    int expected_value = -50;
    for (auto node_value: tree) {
        REQUIRE(node_value == expected_value);
        expected_value++;
    }

    expected_value = -50;
    for (auto node_value: copy_ass_tree) {
        REQUIRE(node_value == expected_value);
        expected_value++;
    }

    expected_value = -50;
    for (auto node_value: copy_constructor_tree) {
        REQUIRE(node_value == expected_value);
        expected_value++;
    }

}

TEST_CASE("Move semantics") {

    RBTree<int> tree;
    for (auto i = -50; i < 50; i++) {
        tree.insert(i);
    }

    int expected_value = -50;
    for (auto node_value: tree) {
        REQUIRE(node_value == expected_value);
        expected_value++;
    }

    RBTree<int> move_ass_tree = std::move(tree);

    expected_value = -50;
    for (auto node_value: move_ass_tree) {
        REQUIRE(node_value == expected_value);
        expected_value++;
    }

    RBTree<int> move_constructor_tree {std::move(move_ass_tree)};

    expected_value = -50;
    for (auto node_value: move_constructor_tree) {
        REQUIRE(node_value == expected_value);
        expected_value++;
    }
}
