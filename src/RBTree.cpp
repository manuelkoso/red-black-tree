//
// Created by koso on 19/08/22.
//

#include "../include/RBTree.h"

template<typename T, typename CMP>
void RBTree<T, CMP>::left_rotate(Node<T>* x) {
    Node<T>* y = x->right;
    x->right = y->left;
    if(y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;

    if(x->parent == nullptr) {
        root = y;
    } else if(x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->left = y;
    }

    y->left = x;
    x->parent = y;
}
