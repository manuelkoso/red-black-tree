//
// Created by koso on 09/09/22.
//

#ifndef RED_BLACK_TREE_RBTCONSTITERATOR_H
#define RED_BLACK_TREE_RBTCONSTITERATOR_H

#include "RBTree.h"

template<typename T, typename CMP>
typename RBTree<T, CMP>::const_iterator RBTree<T, CMP>::begin() const {
    return const_iterator{tree_minimum(root.get())};
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
    if (current->right) {
        Node *z = current->right.get();
        while (z->left) {
            z = z->left.get();
        }
        current = z;
        return *this;
    }
    Node *y = current->parent;
    while (y && (current == y->right.get())) {
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

#endif //RED_BLACK_TREE_RBTCONSTITERATOR_H
