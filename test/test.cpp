#define CATCH_CONFIG_MAIN

#include "../include/catch.hpp"
#include "../include/RBTree.h"

TEST_CASE("Test") {
    REQUIRE(1 == 1);
}

/*
TEST_CASE("Red black tree initialization") {
    SECTION("Default constructor") {
        RBTree<int> tree;
        REQUIRE(tree.get_root() == tree.get_nil());
    }SECTION("Custom constructor - list of values") {
        RBTree<int> tree{10, 4, 18};
        REQUIRE(tree.get_root()->key == 10);
        REQUIRE(tree.get_root()->color == node_color::black);
        REQUIRE(tree.get_root()->left->key == 4);
        REQUIRE(tree.get_root()->left->color == node_color::red);
        REQUIRE(tree.get_root()->right->key == 18);
        REQUIRE(tree.get_root()->right->color == node_color::red);
    }
}

TEST_CASE("Insertion") {

    SECTION("Root insertion") {
        RBTree<int> tree;
        tree.insert(4);
        REQUIRE(tree.get_root()->key == 4);
        REQUIRE(tree.get_root()->color == node_color::black);
    }

    SECTION("Insertion of 3 nodes") {
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
}

TEST_CASE("Iterator") {
    RBTree<int> tree{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int count = 0;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        REQUIRE(*it == count);
        ++count;
    }
}

TEST_CASE("Searching nodes") {
    RBTree<int> tree{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SECTION("Search an existing node") {
        REQUIRE(tree.contains(3) == true);
    }
    SECTION("Search a not existing node") {
        REQUIRE(tree.contains(12) == false);
    }
}

TEST_CASE("Deletion") {
    RBTree<int> tree{0, 1, 2, 3, 4};
    SECTION("Erase an existing node") {
        tree.erase(4);
        REQUIRE(tree.get_root()->right->right == tree.get_nil());
        REQUIRE(tree.get_root()->right->left->key == 2);
        REQUIRE(tree.get_root()->right->key == 3);
        REQUIRE(tree.get_root()->key == 1);
        REQUIRE(tree.get_root()->left->key == 0);
    }
}

TEST_CASE("Insertion and deletion") {
    RBTree<int> tree{0, 1, 2, 3, 4};
    SECTION("Erase an existing node") {
        tree.erase(4);
        REQUIRE(tree.get_root()->right->right == tree.get_nil());
        REQUIRE(tree.get_root()->right->left->key == 2);
        REQUIRE(tree.get_root()->right->key == 3);
        REQUIRE(tree.get_root()->key == 1);
        REQUIRE(tree.get_root()->left->key == 0);
        tree.insert(4);
        REQUIRE(tree.get_root()->right->right->key == 4);
        REQUIRE(tree.get_root()->right->right->right == tree.get_nil());
        REQUIRE(tree.get_root()->right->right->left == tree.get_nil());
        REQUIRE(tree.get_root()->right->left->key == 2);
        REQUIRE(tree.get_root()->right->key == 3);
        REQUIRE(tree.get_root()->key == 1);
        REQUIRE(tree.get_root()->left->key == 0);
    }
}
 */