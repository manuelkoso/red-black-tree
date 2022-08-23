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

        Node() = default;

        explicit Node(T value) :
                key{value} {}

        explicit Node(node_color color) :
                color{color} {}
    };

    Node *root;
    Node *nil;
    CMP cmp;

    void left_rotate(Node *x);

    void right_rotate(Node *x);

    void insert_fixup(Node *z);

    void transplant(Node *u, Node *v);

    void delete_fixup(Node *x);

    Node *tree_minimum(Node *x);

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

    RBTree(std::initializer_list<T>);

    class const_iterator;

    const_iterator begin() const;

    const_iterator end() const;

    void insert(const T &value);

    bool contains(const T &value) const;

    bool erase(const T &value);

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

// custom constructor
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
    return const_iterator{nil};
}

// iterator
template<typename T, typename CMP>
class RBTree<T, CMP>::const_iterator {

private:
    Node *current;

public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = const T;
    using pointer = const T *;
    using reference = const T &;

    const_iterator() : current{nullptr} {}

    explicit const_iterator(Node *node) : current{node} {}

    reference operator*() const {
        return current->key;
    }

    pointer operator->() const {
        return &(current->key);
    }

    const_iterator &operator++();

    const_iterator operator++(int);

    bool operator==(const const_iterator &it) {
        return (current == it.current);
    }

    bool operator!=(const const_iterator &it) {
        return (current != it.current);
    }

};

template<typename T, typename CMP>
typename RBTree<T, CMP>::const_iterator &RBTree<T, CMP>::const_iterator::operator++() {

    if (current->right->left) {
        Node *z = current->right;
        while (z->left->left) {
            z = z->left;
        }
        current = z;
        return *this;
    }
    Node *y = current->parent;
    while ((y->left) && (current == y->right)) {
        current = y;
        y = y->parent;
    }
    current = y;
    return *this;
}

template<typename T, typename CMP>
typename RBTree<T, CMP>::const_iterator RBTree<T, CMP>::const_iterator::operator++(int) {
    auto tmp = *this;
    ++(*this);
    return tmp;
}

template<typename T, typename CMP>
typename RBTree<T, CMP>::Node *RBTree<T, CMP>::tree_minimum(RBTree::Node *x) {
    while (x->left != nil) {
        x = x->left;
    }
    return x;
}

// find node
template<typename T, typename CMP>
bool RBTree<T, CMP>::contains(const T &value) const {
    auto it = std::find(begin(), end(), value);
    if (it == end()) return false;
    return true;
}

// erase node
template<typename T, typename CMP>
bool RBTree<T, CMP>::erase(const T &value) {
    Node* z = root;
    while(z != nil) {
        if(cmp(value, z->key)) {
            z = z->left;
        } else if(cmp(z->key,value)) {
            z = z->right;
        } else {
            break;
        }
    }
    if(z == nil) return false;

    Node *y = z;
    Node *x;
    node_color y_original_color = y->color;
    if (z->left == nil) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = tree_minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == node_color::black) {
        delete_fixup(x);
    }
    delete z;
    return true;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::transplant(RBTree::Node *u, RBTree::Node *v) {
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::delete_fixup(RBTree::Node *x) {
    while (x != root && x->color == node_color::black) {
        if (x == x->parent->left) {
            Node *w = x->parent->left;
            if (w->color == node_color::red) {
                w->color = node_color::black;
                x->parent->color = node_color::red;
                left_rotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == node_color::black && w->right->color == node_color::black) {
                w->color = node_color::red;
                x = x->parent;
            } else if (w->right->color == node_color::black) {
                w->left->color = node_color::black;
                w->color = node_color::red;
                right_rotate(w);
                w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = node_color::black;
            w->right->color = node_color::black;
            left_rotate(x->parent);
            x = root;
        } else {
            // lol
            Node *w = x->parent->right;
            if (w->color == node_color::red) {
                w->color = node_color::black;
                x->parent->color = node_color::red;
                right_rotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == node_color::black && w->left->color == node_color::black) {
                w->color = node_color::red;
                x = x->parent;
            } else if (w->left->color == node_color::black) {
                w->right->color = node_color::black;
                w->color = node_color::red;
                left_rotate(w);
                w = x->parent->left;
            }
            w->color = x->parent->color;
            x->parent->color = node_color::black;
            w->left->color = node_color::black;
            right_rotate(x->parent);
        }
    }
    x->color = node_color::black;
}

#endif //RED_BLACK_TREE_RBTREE_H
