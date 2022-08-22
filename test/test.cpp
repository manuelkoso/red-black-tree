#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"
#include "../include/RBTree.h"

TEST_CASE("Test") {
    REQUIRE(1 == 1);
}

TEST_CASE("Red black tree initialization") {
    SECTION("Default constructor") {
        RBTree<int> tree;
        REQUIRE(tree.get_root() == tree.get_nil());
    }
    SECTION("Custom constructor - list of values") {
        RBTree<int> tree {10, 4, 18};
        REQUIRE(tree.get_root()->key == 10);
        REQUIRE(tree.get_root()->color == node_color::black);
        REQUIRE(tree.get_root()->left->key == 4);
        REQUIRE(tree.get_root()->left->color == node_color::red);
        REQUIRE(tree.get_root()->right->key == 18);
        REQUIRE(tree.get_root()->right->color == node_color::red);
    }
}

TEST_CASE("Root insertion") {
    RBTree<int> tree;
    tree.insert(4);
    REQUIRE(tree.get_root()->key == 4);
    REQUIRE(tree.get_root()->color == node_color::black);
}

TEST_CASE("Insertion") {
    RBTree<int> tree;
    tree.insert(10);
    REQUIRE(tree.get_root()->key == 10);
    REQUIRE(tree.get_root()->color == node_color::black);
    tree.insert(4);
    REQUIRE(tree.get_root()->left->key == 4);
    REQUIRE(tree.get_root()->left->color == node_color::red);
    tree.insert(18);
    REQUIRE(tree.get_root()->right->key == 18);
    REQUIRE(tree.get_root()->right->color == node_color::red);
}

TEST_CASE("Iterator") {
    RBTree<int> tree {2, 5, 3, 5, 6, 9, 10};
    SECTION("Functions end and begin") {
        REQUIRE(tree.begin().current->key == 2);
        REQUIRE(tree.end().current == nullptr);
    }
}