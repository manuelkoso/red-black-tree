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

    Node<T> *root;
    Node<T> *nil;

    void left_rotate(Node<T> *node);

    void right_rotate(Node<T> *node);

    void insert_fixup(Node<T> *node);

    void destroy(Node<T> *node) {
        if (node) {
            destroy(node->right);
            destroy(node->left);
            delete node;
        }
    }


public:

    struct const_iterator {
        Node<T> *current;

        const_iterator(Node<T> *node) : current{node} {}

        const T &operator*() const;

        const T *operator->() const;

        const_iterator &operator++();

        const_iterator &operator++(int);

        bool operator==(const const_iterator &);

        bool operator!=(const const_iterator &);

    };

    const_iterator begin() const {
        Node<T> *left_most_node = root;
        while (left_most_node->left) {
            left_most_node = left_most_node->left;
        }
        return const_iterator{left_most_node};
    }

    const_iterator end() const {
        return const_iterator{nullptr};
    }

    RBTree() : root{nullptr}, nil{new Node<T>{node_color::black}} {
        root = nil;
    }

    RBTree(const std::initializer_list<T>);

    ~RBTree() {
        destroy(root);
    }

    Node<T> *get_root() const;

    void insert(const T &value);
};

template<typename T, typename CMP>
RBTree<T, CMP>::RBTree(const std::initializer_list<T> list): root{nullptr}, nil{new Node<T>{node_color::black}} {
    root = nil;
    for (auto element: list) {
        insert(element);
    }
}

template<typename T, typename CMP>
Node<T> *RBTree<T, CMP>::get_root() const {
    return root;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::left_rotate(Node<T> *x) {
    Node<T> *y = x->right;
    x->right = y->left;
    if (y->left != nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::right_rotate(Node<T> *x) {
    Node<T> *y = x->left;
    x->left = y->right;
    if (y->right != nil) {
        y->right->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == nil) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::insert(const T &value) {
    Node<T> *z = new Node{value, node_color::none};
    Node<T> *y = nil;
    Node<T> *x = root;
    while (x != nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nil) {
        root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = nil;
    z->right = nil;
    z->color = node_color::red;

    insert_fixup(z);
}

template<typename T, typename CMP>
void RBTree<T, CMP>::insert_fixup(Node<T> *z) {
    while (z->parent->color == node_color::red) {
        if (z->parent == z->parent->parent->left) {
            Node<T> *y = z->parent->parent->right;
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
            Node<T> *y = z->parent->parent->left;
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

    root->color = node_color::black;
}


#endif //RED_BLACK_TREE_RBTREE_H
