//
// Created by koso on 19/08/22.
//

#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H

#include <functional>
#include "Node.h"

template<typename T, typename CMP = std::less<T>>
class RBTree {
private:
    Node<T>* root;

    void left_rotate(Node<T>* node);
    void right_rotate(Node<T>* node);
    void insert_fixup(Node<T>* node);

public:

    RBTree(): root{nullptr} {}

    ~RBTree() {
        delete[] root;
    }

    Node<T>* getRoot();

    void insert(const T& value);
};

#endif //RED_BLACK_TREE_RBTREE_H
