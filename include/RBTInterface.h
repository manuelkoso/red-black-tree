//
// Created by koso on 09/09/22.
//

#ifndef RED_BLACK_TREE_RBTINTERFACE_H
#define RED_BLACK_TREE_RBTINTERFACE_H

#include "RBTree.h"
#include <memory>
#include <cassert>
#include <algorithm>

template<typename T, typename CMP>
typename RBTree<T, CMP>::const_iterator RBTree<T, CMP>::begin() const {
    return const_iterator{tree_minimum(root.get())};
}

template<typename T, typename CMP>
typename RBTree<T, CMP>::const_iterator RBTree<T, CMP>::end() const {
    return const_iterator{nullptr};
}

template<typename T, typename CMP>
void RBTree<T, CMP>::insert(const T &value) {
    auto new_node = std::make_unique<Node>(value);
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
    //assert(check_red_node_has_black_children());
    //assert(check_root_black());
    //assert(check_number_black_nodes());
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::erase(const T &value) {

    Node *z = find_node(value);
    if (!z) return false;

    Node *x;
    Node *xp;
    node_color original_color = z->color;
    std::unique_ptr<Node> up;
    std::unique_ptr<Node> uz;

    if (!z->left) {
        x = z->right.get();
        xp = z->parent;
        transplant(z, z->right);
    } else if (!z->right) {
        x = z->left.get();
        xp = z->parent;
        transplant(z, z->left);
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

    assert(check_red_node_has_black_children());
    assert(check_root_black());
    assert(check_number_black_nodes());

    return true;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::contains(const T &value) const {
    if(find_node(value)) return true;
    return false;
}

#endif //RED_BLACK_TREE_RBTINTERFACE_H
