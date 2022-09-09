//
// Created by koso on 09/09/22.
//

#ifndef RED_BLACK_TREE_RBTNODE_H
#define RED_BLACK_TREE_RBTNODE_H

#include "RBTree.h"

template <typename T, typename CMP>
struct RBTree<T, CMP>::Node {
    Node *parent;
    std::unique_ptr<Node> right;
    std::unique_ptr<Node> left;
    T key;
    node_color color{node_color::red};
    explicit Node(const T &value) :
            key{value} {}
    // explicit Node(T &&value) : key{std::move(value)} {}
};


#endif //RED_BLACK_TREE_RBTNODE_H
