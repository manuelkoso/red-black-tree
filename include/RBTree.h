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

    void insert_fixup(Node *new_node);

    std::unique_ptr<Node> transplant(Node *u, std::unique_ptr<Node> &v);

    void delete_fixup(Node *x, Node *xp);

    Node *tree_minimum(Node *x) const;

    bool parentExist(Node *node) const;

    bool checkColor(Node *node, node_color color) const;

    bool isLeftChild(Node *node) const;

    bool isRightChild(Node *node) const;

    Node *get_node_from_key(const T &value) const;

    std::unique_ptr<Node> &get_uniq_pointer(Node *node) {
        if (isRightChild(node)) {
            return node->parent->right;
        } else if (isLeftChild(node)) {
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

// utils
template<typename T, typename CMP>
std::unique_ptr<typename RBTree<T, CMP>::Node> RBTree<T, CMP>::transplant(Node *u, std::unique_ptr<Node> &v) {
    std::unique_ptr<Node> tmp;
    if (!u->parent) {
        tmp = std::move(root);
        root = std::move(v);
        root->parent = nullptr;
    } else if (isLeftChild(u)) {
        tmp = std::move(u->parent->left);
        u->parent->left = std::move(v);
        if (u->parent->left) u->parent->left->parent = u->parent;
    } else {
        tmp = std::move(u->parent->right);
        u->parent->right = std::move(v);
        if (u->parent->right) u->parent->right->parent = u->parent;
    }
    return tmp;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::left_rotate(std::unique_ptr<Node> &x) {
    auto y = std::move(x->right);
    x->right = std::move(y->left);
    if (x->right) {
        x->right->parent = x.get();
    }
    y->parent = x->parent;
    auto xp = x->parent;
    if (!parentExist(x.get())) {
        auto px = x.release();
        root = std::move(y);
        root->left = std::unique_ptr<Node>(px);
        root->left->parent = root.get();
    } else if (isLeftChild(x.get())) {
        auto px = x.release();
        xp->left = std::move(y);
        xp->left->left = std::unique_ptr<Node>(px);
        xp->left->left->parent = xp->left.get();
    } else {
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
    if (!parentExist(x.get())) {
        auto px = x.release();
        root = std::move(y);
        root->right = std::unique_ptr<Node>(px);
        root->right->parent = root.get();
    } else if (isRightChild(x.get())) {
        auto px = x.release();
        xp->right = std::move(y);
        xp->right->right = std::unique_ptr<Node>(px);
        xp->right->right->parent = xp->right.get();
    } else {
        auto px = x.release();
        xp->left = std::move(y);
        xp->left->right = std::unique_ptr<Node>(px);
        xp->left->right->parent = xp->left.get();
    }
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::parentExist(RBTree::Node *node) const {
    if (!node) return false;
    if (node->parent) return true;
    return false;
}

template<typename T, typename CMP>
typename RBTree<T, CMP>::Node *RBTree<T, CMP>::tree_minimum(RBTree::Node *x) const{
    while (x->left) {
        x = x->left.get();
    }
    return x;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::isLeftChild(RBTree::Node *node) const {
    if (!node || node == root.get()) return false;
    if (node->parent->left.get() == node) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::isRightChild(RBTree::Node *node) const {
    if (!node || node == root.get()) return false;
    if (node->parent->right.get() == node) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::checkColor(RBTree::Node *node, node_color color) const {
    if (!node && color == node_color::black) return true;
    if (!node && color == node_color::red) return false;
    if (node->color == color) return true;
    return false;
}

template<typename T, typename CMP>
typename RBTree<T, CMP>::Node *RBTree<T, CMP>::get_node_from_key(const T &value) const{
    Node *node_to_remove = root.get();
    while (node_to_remove) {
        if (cmp(value, node_to_remove->key)) {
            node_to_remove = node_to_remove->left.get();
        } else if (cmp(node_to_remove->key, value)) {
            node_to_remove = node_to_remove->right.get();
        } else {
            break;
        }
    }
    return node_to_remove;
}

// insertion
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
void RBTree<T, CMP>::insert_fixup(Node *new_node) {
    while (parentExist(new_node) && checkColor(new_node->parent, node_color::red)) {
        if (parentExist(new_node->parent) && new_node->parent == new_node->parent->parent->left.get()) {
            Node *y = new_node->parent->parent->right.get();
            if (checkColor(y, node_color::red)) {
                new_node->parent->color = node_color::black;
                y->color = node_color::black;
                new_node->parent->parent->color = node_color::red;
                new_node = new_node->parent->parent;
            } else {
                if (isRightChild(new_node)) {
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
                if (isLeftChild(new_node)) {
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

// iterator
template<typename T, typename CMP>
typename RBTree<T, CMP>::const_iterator RBTree<T, CMP>::begin() const {
    if (root == nullptr) return const_iterator{nullptr};
    Node *left_most_node = root.get();
    while (left_most_node->left) {
        left_most_node = left_most_node->left.get();
    }
    return const_iterator{left_most_node};
}

template<typename T, typename CMP>
typename RBTree<T, CMP>::const_iterator RBTree<T, CMP>::end() const {
    return const_iterator{nullptr};
}

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
        Node *z = current->right.get();
        while (z->left->left) {
            z = z->left.get();
        }
        current = z;
        return *this;
    }
    Node *y = current->parent;
    while ((y->left) && (current == y->right.get())) {
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

    Node *z = get_node_from_key(value);
    if (!z) return false;

    Node *x = nullptr;
    Node *xp = nullptr;
    node_color original_color = z->color;
    std::unique_ptr<Node> up;
    std::unique_ptr<Node> uz;
    std::unique_ptr<Node> tmp;
    if (!z->left) {
        x = z->right.get();
        xp = z->parent;
        tmp = transplant(z, z->right);
    } else if (!z->right) {
        x = z->left.get();
        xp = z->parent;
        tmp = transplant(z, z->left);
    } else {
        Node *y = tree_minimum(z->right.get());
        Node *yp = y->parent;
        original_color = y->color;
        x = y->right.get();
        xp = y;
        if (yp == z) {
            if (x) {
                x->parent = y;
            }
        } else {
            up = transplant(y, y->right);
            xp = up->parent;
            y->right = std::move(z->right);
            y->right->parent = y;
        }
        uz = transplant(z, up);
        y->left = std::move(uz->left);
        y->left->parent = y;
        y->color = z->color;
    }
    if (original_color == node_color::black) {
        delete_fixup(x, xp);
    }
    return true;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::delete_fixup(RBTree::Node *x, Node *xp) {
    while (x != root.get() && checkColor(x, node_color::black)) {
        if (xp->left.get() == x) {
            Node *w = xp->right.get();
            if (checkColor(w, node_color::red)) {
                w->color = node_color::black;
                xp->color = node_color::red;
                left_rotate(get_uniq_pointer(xp));
                w = xp->right.get();
            }
            if (w && checkColor(w->left.get(), node_color::black) && checkColor(w->right.get(), node_color::black)) {
                w->color = node_color::red;
                x = xp;
                xp = x->parent;
            } else if (w) {
                if (checkColor(w->right.get(), node_color::black)) {
                    if (w->left) w->left->color = node_color::black;
                    w->color = node_color::red;
                    right_rotate(get_uniq_pointer(w));
                    w = xp->right.get();
                }
                w->color = xp->color;
                xp->color = node_color::black;
                if (w->right) w->right->color = node_color::black;
                left_rotate(get_uniq_pointer(xp));
                x = root.get();
            } else {
                x = root.get();
            }
        } else {
            Node *w = xp->left.get();
            if (checkColor(w, node_color::red)) {
                w->color = node_color::black;
                xp->color = node_color::red;
                right_rotate(get_uniq_pointer(xp));
                w = xp->left.get();
            }
            if (w && checkColor(w->right.get(), node_color::black) && checkColor(w->left.get(), node_color::black)) {
                w->color = node_color::red;
                x = xp;
                xp = x->parent;
            } else if (w) {
                if (checkColor(w->left.get(), node_color::black)) {
                    if (w->right) w->right->color = node_color::black;
                    w->color = node_color::red;
                    left_rotate(get_uniq_pointer(w));
                    w = xp->left.get();
                }
                w->color = xp->color;
                xp->color = node_color::black;
                if (w->left) w->left->color = node_color::black;
                right_rotate(get_uniq_pointer(xp));
                x = root.get();
            } else {
                x = root.get();
            }
        }
    }
    x->color = node_color::black;
}

#endif //RED_BLACK_TREE_RBTREE_H
