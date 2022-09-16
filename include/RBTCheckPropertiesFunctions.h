//
// Created by koso on 09/09/22.
//

#ifndef RED_BLACK_TREE_RBTCHECKPROPERTIESFUNCTIONS_H
#define RED_BLACK_TREE_RBTCHECKPROPERTIESFUNCTIONS_H

#include "RBTree.h"

template<typename T, typename CMP>
bool RBTree<T, CMP>::check_root_black() const {
    return root->checkColor(node_color::black);
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::check_red_node_has_black_children() const {
    for (auto it = begin(); it != end(); ++it) {
        Node *current = it.node();
        if (current->checkColor(node_color::red) && !current->hasBlackChildren()) return false;
    }
    return true;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::check_number_black_nodes() const {

    for (auto it = begin(); it != end(); ++it) {
        std::vector<int> paths;
        if (it.node()->right) {
            paths.push_back(0);
            count_black_nodes_through_path(it.node()->right.get(), paths, 0);
        } else if (it.node()->left) {
            paths.push_back(0);
            count_black_nodes_through_path(it.node()->left.get(), paths, paths.size() - 1);
        }
        if (!check_all_paths_have_same_number_of_black_nodes(paths)) return false;
    }

    return true;

}

template<typename T, typename CMP>
bool RBTree<T, CMP>::check_all_paths_have_same_number_of_black_nodes(
        const std::vector<int> &number_black_nodes_of_paths) const {
    if (!number_black_nodes_of_paths.empty()) {
        int tmp = number_black_nodes_of_paths.at(0);
        for (auto i = 1; i < number_black_nodes_of_paths.size(); i++) {
            if (number_black_nodes_of_paths.at(i) != tmp) return false;
        }
    }
    return true;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::count_black_nodes_through_path(Node *node, std::vector<int> &number_black_nodes_of_paths,
                                                    int index_of_path) const {
    if (node && node->checkColor(node_color::black)) {
        number_black_nodes_of_paths.at(index_of_path)++;
    }

    int current_number_black_nodes = number_black_nodes_of_paths.at(index_of_path);

    if (!node->left && !node->right) return;

    if (node->left && node->right) {
        count_black_nodes_through_path(node->left.get(), number_black_nodes_of_paths, index_of_path);
        number_black_nodes_of_paths.push_back(current_number_black_nodes);
        count_black_nodes_through_path(node->right.get(), number_black_nodes_of_paths,
                                       number_black_nodes_of_paths.size() - 1);
    } else if (!node->right) {
        count_black_nodes_through_path(node->left.get(), number_black_nodes_of_paths, index_of_path);
    } else if (!node->left) {
        count_black_nodes_through_path(node->right.get(), number_black_nodes_of_paths, index_of_path);
    }

}


#endif //RED_BLACK_TREE_RBTCHECKPROPERTIESFUNCTIONS_H
