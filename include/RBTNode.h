//
// Created by koso on 09/09/22.
//

#ifndef RED_BLACK_TREE_RBTNODE_H
#define RED_BLACK_TREE_RBTNODE_H

#include "RBTree.h"

template<typename T, typename CMP>
struct RBTree<T, CMP>::Node {

    Node *parent {nullptr};
    std::unique_ptr<Node> right {nullptr};
    std::unique_ptr<Node> left {nullptr};
    T key;
    node_color color{node_color::red};

    Node() = default;
    explicit Node(const T &value) :
            key{value} {}

    bool parent_exist() const;

    bool check_color(const node_color color) const;

    bool is_left_child() const;

    bool is_right_child() const;

    bool left_child_exist() const;

    bool right_child_exist() const;

    bool has_black_children() const;

    ~Node() noexcept = default;

};

template<typename T, typename CMP>
bool RBTree<T, CMP>::Node::parent_exist() const {
    if (parent) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::Node::check_color(const node_color col) const {
    if (color == col) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::Node::is_left_child() const {
    if (parent_exist() && parent->left.get() == this) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::Node::is_right_child() const {
    if (parent_exist() && parent->right.get() == this) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::Node::left_child_exist() const {
    if (left) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::Node::right_child_exist() const {
    if (left) return true;
    return false;
}


template<typename T, typename CMP>
bool RBTree<T, CMP>::Node::has_black_children() const {
    if (right_child_exist() && right->check_color(node_color::red)) return false;
    if (left_child_exist() && left->check_color(node_color::red)) return false;
    return true;
}

#endif //RED_BLACK_TREE_RBTNODE_H
