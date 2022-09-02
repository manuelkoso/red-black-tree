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
        Node *parent;
        std::unique_ptr<Node> right;
        std::unique_ptr<Node> left;
        T key;
        node_color color{node_color::red};

        Node() = default;

        explicit Node(T value) :
                key{value} {}
    };

    std::unique_ptr<Node> root;
    CMP cmp;

    void left_rotate(std::unique_ptr<Node> &x);

    void right_rotate(std::unique_ptr<Node> &x);

    void insert_fixup(Node* new_node);

    void transplant(Node *u, Node *v);

    void delete_fixup(Node *x);

    Node *tree_minimum(Node *x);

    bool parentExist(Node *node);

    bool parentExist(std::unique_ptr<Node> &node);

    bool checkColor(Node *node, node_color color);

    bool isLeftChild(Node *node);

    bool isLeftChild(std::unique_ptr<Node> &node);

    bool isRightChild(Node *node);

    bool isRightChild(std::unique_ptr<Node> &node);

    std::unique_ptr<Node> &get_uniq_pointer(Node *node) {
        if (isRightChild(node)) {
            return node->parent->right;
        } else if(isLeftChild(node)) {
            return node->parent->left;
        } else {
            return root;
        }
    }

public:

    RBTree() = default;

    RBTree(std::initializer_list<T>);

    class const_iterator;

    const_iterator begin() const;

    const_iterator end() const;

    void insert(const T &value);

    bool contains(const T &value) const;

    bool erase(const T &value);

};

// custom constructor
template<typename T, typename CMP>
RBTree<T, CMP>::RBTree(const std::initializer_list<T> list): root{nullptr} {
    for (auto element: list) {
        insert(element);
    }
}

// insertion
template<typename T, typename CMP>
void RBTree<T, CMP>::left_rotate(std::unique_ptr<Node> &x) {
    auto y = std::move(x->right);
    x->right = std::move(y->left);
    if (x->right) {
        x->right->parent = x.get();
    }
    y->parent = x->parent;
    auto xp = x->parent;
    if (!x->parent) {
        auto px = x.release();
        root = std::move(y);
        root->left = std::unique_ptr<Node>(px);
        root->left->parent = root.get();
    } else if (xp && x == xp->left) {
        auto px = x.release();
        xp->left = std::move(y);
        xp->left->left = std::unique_ptr<Node>(px);
        xp->left->left->parent = xp->left.get();
    } else if (x->parent) {
        auto px = x.release();
        xp->right = std::move(y);
        xp->right->left = std::unique_ptr<Node>(px);
        xp->right->left->parent = xp->right.get();
    }
}


template<typename T, typename CMP>
void RBTree<T, CMP>::right_rotate(std::unique_ptr<Node> &x) {
    auto y = std::move(x->left);
    x->left = std::move(y->right);
    if (x->left) {
        x->left->parent = x.get();
    }
    y->parent = x->parent;
    auto xp = x->parent;
    if (!x->parent) {
        auto px = x.release();
        root = std::move(y);
        root->right = std::unique_ptr<Node>(px);
        root->right->parent = root.get();
    } else if (xp && x == xp->right) {
        auto px = x.release();
        xp->right = std::move(y);
        xp->right->right = std::unique_ptr<Node>(px);
        xp->right->right->parent = xp->right.get();
    } else if (x->parent) {
        auto px = x.release();
        xp->left = std::move(y);
        xp->left->right = std::unique_ptr<Node>(px);
        xp->left->right->parent = xp->left.get();
    }
}


template<typename T, typename CMP>
void RBTree<T, CMP>::insert(const T &value) {
    std::unique_ptr new_node = std::make_unique<Node>(value);
    Node *new_node_parent = root.get();
    Node *tmp_node = root.get();
    while (tmp_node) {
        new_node_parent = tmp_node;
        if (cmp(new_node->key, tmp_node->key)) {
            tmp_node = tmp_node->left.get();
        } else {
            tmp_node = tmp_node->right.get();
        }
    }
    new_node->parent = new_node_parent;
    if (!new_node_parent) {
        root = std::move(new_node);
        insert_fixup(root.get());
    } else if (cmp(new_node->key, new_node_parent->key)) {
        new_node_parent->left = std::move(new_node);
        new_node_parent->left->left = nullptr;
        new_node_parent->left->right = nullptr;
        new_node_parent->left->color = node_color::red;
        insert_fixup(new_node_parent->left.get());
    } else {
        new_node_parent->right = std::move(new_node);
        new_node_parent->right->left = nullptr;
        new_node_parent->right->right = nullptr;
        new_node_parent->right->color = node_color::red;
        insert_fixup(new_node_parent->right.get());
    }
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::parentExist(RBTree::Node *node) {
    if(!node) return false;
    if (node->parent) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::parentExist(std::unique_ptr<Node> &node) {
    if(!node) return false;
    if (node->parent) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::isLeftChild(RBTree::Node *node) {
    if(node == root.get()) return false;
    if (node->parent->left.get() == node) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::isLeftChild(std::unique_ptr<Node> &node) {
    if(node == root) return false;
    if (node->parent->left == node) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::isRightChild(RBTree::Node *node) {
    if(node == root.get()) return false;
    if (node->parent->right.get() == node) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::isRightChild(std::unique_ptr<Node> &node) {
    if(node == root) return false;
    if (node->parent->right == node) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::checkColor(RBTree::Node *node, node_color color) {
    if(!node && color == node_color::black) return true;
    if(!node && color == node_color::red) return false;
    if (node->color == color) return true;
    return false;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::insert_fixup(Node* new_node) {
    while (parentExist(new_node) && checkColor(new_node->parent, node_color::red)) {
        if (parentExist(new_node->parent) && new_node->parent == new_node->parent->parent->left.get()) {
            Node *y = new_node->parent->parent->right.get();
            if (checkColor(y, node_color::red)) {
                new_node->parent->color = node_color::black;
                y->color = node_color::black;
                new_node->parent->parent->color = node_color::red;
                new_node = new_node->parent->parent;
            } else {
                if (new_node == new_node->parent->right.get()) {
                    new_node = new_node->parent;
                    left_rotate(get_uniq_pointer(new_node));
                }
                new_node->parent->color = node_color::black;
                new_node->parent->parent->color = node_color::red;
                right_rotate(get_uniq_pointer(new_node->parent->parent));
            }
        } else {
            Node *y = new_node->parent->parent->left.get();
            if (checkColor(y, node_color::red)) {
                new_node->parent->color = node_color::black;
                y->color = node_color::black;
                new_node->parent->parent->color = node_color::red;
                new_node = new_node->parent->parent;
            } else {
                if (new_node == new_node->parent->left.get()) {
                    new_node = new_node->parent;
                    right_rotate(get_uniq_pointer(new_node));
                }
                new_node->parent->color = node_color::black;
                new_node->parent->parent->color = node_color::red;
                left_rotate(get_uniq_pointer(new_node->parent->parent));
            }
        }
    }
    root->color = node_color::black;
}

/*
template<typename T, typename CMP>
typename RBTree<T, CMP>::const_iterator RBTree<T, CMP>::begin() const {
    if(root == nil) return const_iterator{nil};
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
*/
#endif //RED_BLACK_TREE_RBTREE_H
