//
// Created by koso on 19/08/22.
//

#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H

#include <functional>

enum class node_color {
    red, black
};

template<typename T, typename CMP = std::less<T>>
class RBTree {
private:

    struct Node {
        Node *parent{nullptr};
        Node *right{nullptr};
        Node *left{nullptr};
        T key;
        node_color color{node_color::red};

        Node() {}

        Node(T value) :
                key{value} {}

        Node(node_color color) :
                color{color} {}
    };

    Node *root;
    Node *nil;
    CMP cmp;

    void left_rotate(Node *node);

    void right_rotate(Node *node);

    void insert_fixup(Node *node);

    void destroy(Node *node) {
        if (node && node != nil) {
            destroy(node->right);
            destroy(node->left);
            delete node;
        }
    }


public:

    RBTree() : root{nullptr}, nil{new Node{node_color::black}} {
        root = nil;
    }

    RBTree(const std::initializer_list<T>);

    struct const_iterator {
        Node *current;

        const_iterator(Node *node) : current{node} {}

        const T &operator*() const;

        const T *operator->() const;

        const_iterator &operator++();

        const_iterator &operator++(int);

        bool operator==(const const_iterator &);

        bool operator!=(const const_iterator &);

    };

    const_iterator begin() const;

    const_iterator end() const;

    void insert(const T &value);

    Node *get_root() const {
        return root;
    }

    Node *get_nil() const {
        return nil;
    }

    ~RBTree() {
        delete nil;
        destroy(root);
    }
};

// constructor
template<typename T, typename CMP>
RBTree<T, CMP>::RBTree(const std::initializer_list<T> list): root{nullptr}, nil{new Node{node_color::black}} {
    root = nil;
    for (auto element: list) {
        insert(element);
    }
}

// insertion
template<typename T, typename CMP>
void RBTree<T, CMP>::left_rotate(Node *x) {
    Node *y = x->right;
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
void RBTree<T, CMP>::right_rotate(Node *x) {
    Node *y = x->left;
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
    Node *z = new Node{value};
    Node *y = nil;
    Node *x = root;
    while (x != nil) {
        y = x;
        if (cmp(z->key, x->key)) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nil) {
        root = z;
    } else if (cmp(z->key, y->key)) {
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
void RBTree<T, CMP>::insert_fixup(Node *z) {
    while (z->parent->color == node_color::red) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
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
            Node *y = z->parent->parent->left;
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

// iterator
template<typename T, typename CMP>
typename RBTree<T, CMP>::const_iterator RBTree<T, CMP>::begin() const {
    Node *left_most_node = root;
    while (left_most_node->left != nil) {
        left_most_node = left_most_node->left;
    }
    return const_iterator{left_most_node};
}

template<typename T, typename CMP>
typename RBTree<T, CMP>::const_iterator RBTree<T, CMP>::end() const {
    return const_iterator{nullptr};
}

template<typename T, typename CMP>
const T& RBTree<T,CMP>::const_iterator::operator*() const {
    return current->key;
}

template<typename T, typename CMP>
const T* RBTree<T,CMP>::const_iterator::operator->() const {
    return &(current->key);
}

#endif //RED_BLACK_TREE_RBTREE_H
