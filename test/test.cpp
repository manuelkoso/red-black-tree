#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"
#include "../include/Node.h"
#include "../include/RBTree.h"


TEST_CASE("Test") {
    REQUIRE(1 == 1);
}

TEST_CASE("Node initialization") {
    Node<int>* node = new Node<int>{5};
    REQUIRE(node->key == 5);
    REQUIRE(node->parent == nullptr);
    REQUIRE(node->right == nullptr);
    REQUIRE(node->left == nullptr);
    REQUIRE(node->color == node_color::none);
}

TEST_CASE("Red black tree initialization") {
    RBTree<int> tree;
    REQUIRE(tree.get_root() == nullptr);
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