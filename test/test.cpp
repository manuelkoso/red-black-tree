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
    REQUIRE(node->color == node_color::red);
}

TEST_CASE("Red black tree initialization") {
    RBTree<int> tree;
    REQUIRE(tree.get_root() == nullptr);
}