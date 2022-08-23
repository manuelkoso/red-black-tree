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
        std::weak_ptr<Node> parent;
        std::shared_ptr<Node> right;
        std::shared_ptr<Node> left;
        T key;
        node_color color{node_color::red};

        Node() = default;

        explicit Node(T value) :
                key{value} {}

        explicit Node(node_color color) :
                color{color} {}
    };

    std::shared_ptr<Node> root;
    std::shared_ptr<Node> nil;
    CMP cmp;

    void left_rotate(std::shared_ptr<Node> x);

    void right_rotate(std::shared_ptr<Node> x);

    void insert_fixup(std::shared_ptr<Node> z);

    void transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v);

    void delete_fixup(std::shared_ptr<Node> x);

    std::shared_ptr<Node> tree_minimum(std::shared_ptr<Node> x);

public:

    RBTree() : root{nullptr}, nil{std::make_shared<Node>(node_color::black)} {
        root = nil;
    }

    RBTree(std::initializer_list<T>);

    class const_iterator;

    const_iterator begin() const;

    const_iterator end() const;

    void insert(const T &value);

    bool contains(const T &value) const;

    bool erase(const T &value);

    std::shared_ptr<Node> get_root() const {
        return root;
    }

    std::shared_ptr<Node> get_nil() const {
        return nil;
    }
};

// custom constructor
template<typename T, typename CMP>
RBTree<T, CMP>::RBTree(const std::initializer_list<T> list): root{nullptr}, nil{std::make_shared<Node>(node_color::black)} {
    root = nil;
    for (auto element: list) {
        insert(element);
    }
}

// insertion
template<typename T, typename CMP>
void RBTree<T, CMP>::left_rotate(std::shared_ptr<Node> x) {
    auto y = x->right;
    x->right = y->left;
    if (y->left != nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent.lock() == nil) {
        root = y;
    } else if (x == x->parent.lock()->left) {
        x->parent.lock()->left = y;
    } else {
        x->parent.lock()->right = y;
    }
    y->left = x;
    x->parent = y;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::right_rotate(std::shared_ptr<Node> x) {
    auto y = x->left;
    x->left = y->right;
    if (y->right != nil) {
        y->right->parent = x;
    }
    y->parent = x->parent;

    if (x->parent.lock() == nil) {
        root = y;
    } else if (x == x->parent.lock()->left) {
        x->parent.lock()->left = y;
    } else {
        x->parent.lock()->right = y;
    }
    y->right = x;
    x->parent = y;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::insert(const T &value) {
    auto z = std::make_shared<Node>(value);
    auto y = nil;
    auto x = root;
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
void RBTree<T, CMP>::insert_fixup(std::shared_ptr<Node> z) {
    while (z->parent.lock()->color == node_color::red) {
        if (z->parent.lock() == z->parent.lock()->parent.lock()->left) {
            auto y = z->parent.lock()->parent.lock()->right;
            if (y->color == node_color::red) {
                z->parent.lock()->color = node_color::black;
                y->color = node_color::black;
                z->parent.lock()->parent.lock()->color = node_color::red;
                z = z->parent.lock()->parent.lock();
            } else {
                if (z == z->parent.lock()->right) {
                    z = z->parent.lock();
                    left_rotate(z);
                }
                z->parent.lock()->color = node_color::black;
                z->parent.lock()->parent.lock()->color = node_color::red;
                right_rotate(z->parent.lock()->parent.lock());
            }
        } else {
            auto y = z->parent.lock()->parent.lock()->left;
            if (y->color == node_color::red) {
                z->parent.lock()->color = node_color::black;
                y->color = node_color::black;
                z->parent.lock()->parent.lock()->color = node_color::red;
                z = z->parent.lock()->parent.lock();
            } else {
                if (z == z->parent.lock()->left) {
                    z = z->parent.lock();
                    right_rotate(z);
                }
                z->parent.lock()->color = node_color::black;
                z->parent.lock()->parent.lock()->color = node_color::red;
                left_rotate(z->parent.lock()->parent.lock());
            }
        }
    }

    root->color = node_color::black;
}

template<typename T, typename CMP>
typename RBTree<T, CMP>::const_iterator RBTree<T, CMP>::begin() const {
    auto left_most_node = root;
    while (left_most_node->left != nil) {
        left_most_node = left_most_node->left;
    }
    return const_iterator{left_most_node.get()};
}

template<typename T, typename CMP>
typename RBTree<T, CMP>::const_iterator RBTree<T, CMP>::end() const {
    return const_iterator{nil.get()};
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
        auto z = current->right;
        while (z->left->left) {
            z = z->left;
        }
        current = z.get();
        return *this;
    }
    auto y = current->parent.lock();
    while ((y->left) && (current == y->right.get())) {
        current = y.get();
        y = y->parent.lock();
    }
    current = y.get();
    return *this;
}

template<typename T, typename CMP>
typename RBTree<T, CMP>::const_iterator RBTree<T, CMP>::const_iterator::operator++(int) {
    auto tmp = *this;
    ++(*this);
    return tmp;
}

template<typename T, typename CMP>
std::shared_ptr<typename RBTree<T,CMP>::Node> RBTree<T, CMP>::tree_minimum(std::shared_ptr<Node> x) {
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
    auto z = root;
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

    auto y = z;
    std::shared_ptr<Node> x;
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
        if (y->parent.lock() == z) {
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
    return true;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v) {
    if (u->parent.lock() == nil) {
        root = v;
    } else if (u == u->parent.lock()->left) {
        u->parent.lock()->left = v;
    } else {
        u->parent.lock()->right = v;
    }
    v->parent = u->parent;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::delete_fixup(std::shared_ptr<Node> x) {
    while (x != root && x->color == node_color::black) {
        if (x == x->parent.lock()->left) {
            auto w = x->parent.lock()->left;
            if (w->color == node_color::red) {
                w->color = node_color::black;
                x->parent.lock()->color = node_color::red;
                left_rotate(x->parent.lock());
                w = x->parent.lock()->right;
            }
            if (w->left->color == node_color::black && w->right->color == node_color::black) {
                w->color = node_color::red;
                x = x->parent.lock();
            } else if (w->right->color == node_color::black) {
                w->left->color = node_color::black;
                w->color = node_color::red;
                right_rotate(w);
                w = x->parent.lock()->right;
            }
            w->color = x->parent.lock()->color;
            x->parent.lock()->color = node_color::black;
            w->right->color = node_color::black;
            left_rotate(x->parent.lock());
            x = root;
        } else {
            auto w = x->parent.lock()->right;
            if (w->color == node_color::red) {
                w->color = node_color::black;
                x->parent.lock()->color = node_color::red;
                right_rotate(x->parent.lock());
                w = x->parent.lock()->left;
            }
            if (w->right->color == node_color::black && w->left->color == node_color::black) {
                w->color = node_color::red;
                x = x->parent.lock();
            } else if (w->left->color == node_color::black) {
                w->right->color = node_color::black;
                w->color = node_color::red;
                left_rotate(w);
                w = x->parent.lock()->left;
            }
            w->color = x->parent.lock()->color;
            x->parent.lock()->color = node_color::black;
            w->left->color = node_color::black;
            right_rotate(x->parent.lock());
        }
    }
    x->color = node_color::black;
}

#endif //RED_BLACK_TREE_RBTREE_H
