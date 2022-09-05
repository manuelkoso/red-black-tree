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