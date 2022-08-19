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

template<typename T, typename CMP>
void RBTree<T, CMP>::right_rotate(Node<T>* x) {
    Node<T>* y = x->left;
    x->left = y->right;
    if(y->right != nullptr) {
        y->right->parent = x;
    }
    y->parent = x->parent;

    if(x->parent == nullptr) {
        root = y;
    } else if(x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::insert(const T &value) {
    Node<T>* z = new Node{value};
    Node<T>* y = nullptr;
    Node<T>* x = root;
    while(x != nullptr) {
        y = x;
        if(value < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    if(y == nullptr) {
        root = z;
    } else if(z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = nullptr;
    z->right = nullptr;
    z->color = node_color::red;

    insert_fixup(z);

}