//
// Created by koso on 09/09/22.
//

#ifndef RED_BLACK_TREE_RBTPRIVATEFUNCTIONS_H
#define RED_BLACK_TREE_RBTPRIVATEFUNCTIONS_H

#include "RBTree.h"

template<typename T, typename CMP>
std::unique_ptr<typename RBTree<T,CMP>::Node> &RBTree<T, CMP>::get_uniq_pointer(RBTree::Node *node) {
    if (isRightChild(node)) {
        return node->parent->right;
    } else if (isLeftChild(node)) {
        return node->parent->left;
    } else {
        return root;
    }
}

template<typename T, typename CMP>
std::unique_ptr<typename RBTree<T, CMP>::Node> RBTree<T, CMP>::transplant(Node *u, std::unique_ptr<Node> &v) noexcept {
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
void RBTree<T, CMP>::left_rotate(std::unique_ptr<Node> &x) noexcept {
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
void RBTree<T, CMP>::right_rotate(std::unique_ptr<Node> &x) noexcept {
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
bool RBTree<T, CMP>::parentExist(RBTree::Node *node) const noexcept {
    if (!node) return false;
    if (node->parent) return true;
    return false;
}

template<typename T, typename CMP>
typename RBTree<T, CMP>::Node *RBTree<T, CMP>::tree_minimum(RBTree::Node *x) const noexcept {
    if (!x) return x;
    while (x->left) {
        x = x->left.get();
    }
    return x;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::isLeftChild(RBTree::Node *node) const noexcept {
    if (!node || node == root.get()) return false;
    if (node->parent->left.get() == node) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::isRightChild(RBTree::Node *node) const noexcept {
    if (!node || node == root.get()) return false;
    if (node->parent->right.get() == node) return true;
    return false;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::checkColor(RBTree::Node *node, node_color color) const noexcept {
    if (!node && color == node_color::black) return true;
    if (!node && color == node_color::red) return false;
    if (node->color == color) return true;
    return false;
}

template<typename T, typename CMP>
typename RBTree<T, CMP>::Node *RBTree<T, CMP>::find(const T &value) const noexcept {
    for(auto it = begin(); it!=end(); ++it) {
        if(*it == value) return it.node();
    }
    return nullptr;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::insert_fixup(Node *new_node) noexcept {
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

template<typename T, typename CMP>
void RBTree<T, CMP>::delete_fixup(RBTree::Node *x, Node *xp) noexcept {
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


#endif //RED_BLACK_TREE_RBTPRIVATEFUNCTIONS_H
