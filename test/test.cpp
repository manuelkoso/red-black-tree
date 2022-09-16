#define CATCH_CONFIG_MAIN

#include "../include/catch.hpp"
#include "../include/RBTree.h"

TEST_CASE("Red black tree initialization") {
    SECTION("Default constructor") {
        RBTree<int> tree;
        bool check = tree.begin() == tree.end();
        REQUIRE(check);
    }
    SECTION("Custom constructor") {
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
    }
}

TEST_CASE("Insertion") {
    SECTION("Root insertion") {
        RBTree<int> tree;
        tree.insert(3);
        bool check = *tree.begin() == 3;
        REQUIRE(check);
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
    } SECTION("1000 nodes") {
        RBTree<long> tree;
        for (auto i = -1000; i < 1000; i++) {
            tree.insert(i);
        }
        int expected_value = -1000;
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
    }SECTION("Find not existing nodes") {
        REQUIRE_FALSE(tree.contains(333));
        REQUIRE_FALSE(tree.contains(-332));
        REQUIRE_FALSE(tree.contains(50));
        REQUIRE_FALSE(tree.contains(-51));
        REQUIRE_FALSE(tree.contains(-774));
        REQUIRE_FALSE(tree.contains(233));
        REQUIRE_FALSE(tree.contains(-2234));
    }
}

TEST_CASE("Deletion") {

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
        REQUIRE_FALSE(tree.contains(40));
        REQUIRE_FALSE(tree.contains(33));
        REQUIRE_FALSE(tree.contains(-40));
        REQUIRE_FALSE(tree.contains(49));
        REQUIRE_FALSE(tree.contains(0));
    } SECTION("Remove not existing nodes") {
        REQUIRE_FALSE(tree.erase(40));
        REQUIRE_FALSE(tree.erase(33));
        REQUIRE_FALSE(tree.erase(-40));
        REQUIRE_FALSE(tree.erase(49));
        REQUIRE_FALSE(tree.erase(0));
    }
}

TEST_CASE("Copy semantics") {
    RBTree<int> tree;
    for (auto i = -50; i < 50; i++) {
        tree.insert(i);
    }

    RBTree<int> copy_assignment_tree = tree;
    RBTree<int> copy_constructor_tree{tree};

    int expected_value = -50;
    for (auto node_value: tree) {
        REQUIRE(node_value == expected_value);
        expected_value++;
    }

    expected_value = -50;
    for (auto node_value: copy_assignment_tree) {
        REQUIRE(node_value == expected_value);
        expected_value++;
    }

    expected_value = -50;
    for (auto node_value: copy_constructor_tree) {
        REQUIRE(node_value == expected_value);
        expected_value++;
    }

    tree.insert(200);
    REQUIRE_FALSE(copy_assignment_tree.contains(200));
    REQUIRE_FALSE(copy_constructor_tree.contains(200));
    REQUIRE(tree.contains(200));

    copy_assignment_tree.insert(300);
    REQUIRE_FALSE(tree.contains(300));
    REQUIRE_FALSE(copy_constructor_tree.contains(300));
    REQUIRE(copy_assignment_tree.contains(300));

    copy_constructor_tree.insert(400);
    REQUIRE_FALSE(tree.contains(400));
    REQUIRE_FALSE(copy_assignment_tree.contains(400));
    REQUIRE(copy_constructor_tree.contains(400));

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

    RBTree<int> move_assignment_tree = std::move(tree);

    expected_value = -50;
    for (auto node_value: move_assignment_tree) {
        REQUIRE(node_value == expected_value);
        expected_value++;
    }

    RBTree<int> move_constructor_tree{std::move(move_assignment_tree)};

    expected_value = -50;
    for (auto node_value: move_constructor_tree) {
        REQUIRE(node_value == expected_value);
        expected_value++;
    }

}

TEST_CASE("Output operator <<") {
    RBTree<int> tree;
    for (auto i = 0; i < 10; i++) {
        tree.insert(i);
    }
    std::stringstream out;
    out << tree;
    REQUIRE(out.str() == "0 1 2 3 4 5 6 7 8 9");
}

TEST_CASE("Iterator") {
    RBTree<int> tree = {1, 2, 3, 4, 5};
    SECTION("Begin") {
        auto it = tree.begin();
        REQUIRE(*it == 1);
    } SECTION("End") {
        auto it = tree.end();
        RBTree<int>::const_iterator null_it {nullptr};
        bool check = null_it == it;
        REQUIRE(check);
    } SECTION("Post increment") {
        auto it = tree.begin();
        REQUIRE(*(it) == 1);
        REQUIRE(*(it++) == 1);
        REQUIRE(*it == 2);
    } SECTION("Pre increment") {
        auto it = tree.begin();
        REQUIRE(*(it) == 1);
        REQUIRE(*(++it) == 2);
        REQUIRE(*it == 2);
    } SECTION("Equal and not equal") {
        auto it_one = tree.begin();
        auto it_second = tree.begin();
        bool check_equal = it_one == it_second;
        bool check_not_equal = it_one != it_second;
        REQUIRE(check_equal);
        REQUIRE_FALSE(check_not_equal);
        it_one++;
        check_equal = it_one == it_second;
        check_not_equal = it_one != it_second;
        REQUIRE_FALSE(check_equal);
        REQUIRE(check_not_equal);
    }
}