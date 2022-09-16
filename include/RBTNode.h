//
// Created by koso on 09/09/22.
//

#ifndef RED_BLACK_TREE_RBTNODE_H
#define RED_BLACK_TREE_RBTNODE_H

#include "RBTree.h"

template<typename T, typename CMP>
struct RBTree<T, CMP>::Node {
    Node *parent;
    std::unique_ptr<Node> right;
    std::unique_ptr<Node> left;
    T key;
    node_color color{node_color::red};

    explicit Node(const T &value) :
            key{value} {}

    bool parentExist() const;

    bool checkColor(node_color color) const;

    bool isLeftChild() const;

    bool isRightChild() const;

    bool leftChildExist() const;

    bool rightChildExist() const;

    bool hasBlackChildren() const;

};

template<typename T, typename CMP>
bool RBTree<T, CMP>::Node::hasBlackChildren() const {
    if (rightChildExist() && right->checkColor(node_color::red)) return false;
    if (leftChildExist() && left->checkColor(node_color::red)) return false;
    return true;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::Node::leftChildExist() const {
    if (left) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::Node::rightChildExist() const {
    if (left) return true;
    return false;
}


template<typename T, typename CMP>
bool RBTree<T, CMP>::Node::parentExist() const {
    if (parent) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::Node::isRightChild() const {
    if (parentExist() && parent->right.get() == this) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::Node::isLeftChild() const {
    if (parentExist() && parent->left.get() == this) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::Node::checkColor(node_color node_color) const {
    if (color == node_color) return true;
    return false;
}


#endif //RED_BLACK_TREE_RBTNODE_H
