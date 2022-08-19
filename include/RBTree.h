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

    Node<T>* get_root();

    void insert(const T& value);
};

// implementation
template<typename T, typename CMP>
Node<T> *RBTree<T, CMP>::get_root() {
    return root;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::left_rotate(Node<T> *x) {
    Node<T> *y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->left = y;
    }

    y->left = x;
    x->parent = y;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::right_rotate(Node<T> *x) {
    Node<T> *y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::insert(const T &value) {
    Node<T> *z = new Node{value};
    Node<T> *y = nullptr;
    Node<T> *x = root;
    while (x != nullptr) {
        y = x;
        if (value < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nullptr) {
        root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = nullptr;
    z->right = nullptr;
    z->color = node_color::red;

    insert_fixup(z);
}

template<typename T, typename CMP>
void RBTree<T, CMP>::insert_fixup(Node<T> *z) {
    while (z->parent->color == node_color::red) {
        if (z->parent == z->parent->parent->left) {
            Node<T> *y = z->parent->parent->left;
            if (y->color == node_color::red) {
                z->parent->color = node_color::black;
                y->color = node_color::black;
                z->parent->parent->color = node_color::red;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(z);
                }
                z->parent->color = node_color::black;
                z->parent->parent->color = node_color::red;
                right_rotate(z->parent->parent);
            }
        } else {
            Node<T> *y = z->parent->parent->right;
            if (y->color == node_color::red) {
                z->parent->color = node_color::black;
                y->color = node_color::black;
                z->parent->parent->color = node_color::red;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(z);
                }
                z->parent->color = node_color::black;
                z->parent->parent->color = node_color::red;
                left_rotate(z->parent->parent);
            }
        }
    }
}

#endif //RED_BLACK_TREE_RBTREE_H
