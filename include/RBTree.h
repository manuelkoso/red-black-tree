#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H

#include <functional>
#include <memory>
#include <vector>
#include <iostream>

template<typename T, typename CMP = std::less<T>>
class RBTree {
private:
    enum class node_color {
        red, black
    };
    struct Node;
    CMP cmp;

    std::unique_ptr<Node> root{nullptr};

    // Modify tree structure
    void left_rotate(std::unique_ptr<Node> &x);

    void right_rotate(std::unique_ptr<Node> &x);

    std::unique_ptr<Node> transplant(Node *u, std::unique_ptr<Node> &v);

    // Fixup
    void delete_fixup(Node *x, Node *xp);

    void insert_fixup(Node *new_node);

    // Utils
    Node *tree_minimum(Node *x) const;

    Node *find_node(const T &value) const;

    std::unique_ptr<Node> &get_uniq_pointer(Node *node);

public:

    class const_iterator;

    // Constructors
    RBTree() = default;

    RBTree(std::initializer_list<T> list) : root{nullptr} {
        for (auto element: list) {
            insert(element);
        }
    }

    // Move semantics
    RBTree(RBTree &&) noexcept = default;

    RBTree &operator=(RBTree &&) noexcept = default;

    // Copy semantics
    RBTree(const RBTree &tree) {
        for (auto node_value: tree) {
            insert(node_value);
        }
    }

    RBTree &operator=(const RBTree &tree) {
        root.reset();
        for (auto node_value: tree) {
            insert(node_value);
        }
    }

    // Public methods
    const_iterator begin() const;

    const_iterator end() const;

    void insert(const T &value);

    bool contains(const T &value) const;

    bool erase(const T &value);

    // Print
    friend std::ostream &operator<<(std::ostream &os, const RBTree &tree) {
        for (auto it = tree.begin(); it != tree.end(); ++it) {
            if (it == tree.begin()) {
                os << *it;
            } else {
                os << " " << *it;
            }
        }
        return os;
    }

    ~RBTree() noexcept = default;


private:

    // Check red black tree properties
    bool check_properties() const;

    bool
    check_all_paths_have_same_number_of_black_nodes(const std::vector<unsigned int> &number_black_nodes_of_paths) const;

    void
    count_black_nodes_through_path(Node *node, std::vector<unsigned int> &number_black_nodes_of_paths,
                                   unsigned int index_of_path) const;

};

#include "RBTNode.h"
#include "RBTConstIterator.h"
#include "RBTCheckPropertiesFunctions.h"
#include "RBTPrivateFunctions.h"
#include "RBTInterface.h"

#endif //RED_BLACK_TREE_RBTREE_H
