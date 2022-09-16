#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H

#include <functional>

enum class node_color {
    red, black
};

template<typename T, typename CMP = std::less<T>>
class RBTree {
private:
    struct Node;

    std::unique_ptr<Node> root;
    CMP cmp;

    // check red black tree properties
    bool check_root_black() const noexcept;

    bool check_red_node_has_black_children() const noexcept;

    bool check_number_black_nodes() const noexcept;

    bool check_all_paths_have_same_number_of_black_nodes(const std::vector<int> &number_black_nodes_of_paths) const noexcept;

    void count_black_nodes_through_path(Node *node, std::vector<int> &number_black_nodes_of_paths, int index_of_path) const noexcept;

    // utils
    void left_rotate(std::unique_ptr<Node> &x) noexcept;

    void right_rotate(std::unique_ptr<Node> &x) noexcept;

    std::unique_ptr<Node> transplant(Node *u, std::unique_ptr<Node> &v) noexcept;

    void delete_fixup(Node *x, Node *xp) noexcept;

    void insert_fixup(Node *new_node) noexcept;

    Node *tree_minimum(Node *x) const noexcept;

    bool parentExist(Node *node) const noexcept;

    bool checkColor(Node *node, node_color color) const noexcept;

    bool isLeftChild(Node *node) const noexcept;

    bool isRightChild(Node *node) const noexcept;

    Node *find(const T &value) const noexcept;

    std::unique_ptr<Node> &get_uniq_pointer(Node *node);

public:

    class const_iterator;

    // constructors
    RBTree() = default;
    RBTree(std::initializer_list<T> list): root{nullptr} {
        for (auto element: list) {
            insert(element);
        }
    }

    // move semantics
    RBTree(RBTree&&) noexcept = default;
    RBTree& operator=(RBTree&&) noexcept = default;

    // Copy semantics
    RBTree(const RBTree& tree) {
        for(auto node_value : tree) {
            insert(node_value);
        }
    }
    RBTree& operator=(const RBTree& tree) {
        root.reset();
        for(auto node_value : tree) {
            insert(node_value);
        }
    }

    // Interface
    const_iterator begin() const;

    const_iterator end() const;

    void insert(const T &value);

    bool contains(const T &value) const;

    bool erase(const T &value);

    friend std::ostream& operator<<(std::ostream& os, const RBTree& tree) {
        for(auto it = tree.begin(); it!=tree.end(); ++it) {
            if(it == tree.begin()) {
                os << *it;
            } else {
                os << " " << *it;
            }
        }
        return os;
    }

};

#include "RBTNode.h"
#include "RBTConstIterator.h"
#include "RBTCheckPropertiesFunctions.h"
#include "RBTInterface.h"
#include "RBTPrivateFunctions.h"

#endif //RED_BLACK_TREE_RBTREE_H
