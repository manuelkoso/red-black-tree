//
// Created by koso on 09/09/22.
//

#ifndef RED_BLACK_TREE_RBTCHECKPROPERTIESFUNCTIONS_H
#define RED_BLACK_TREE_RBTCHECKPROPERTIESFUNCTIONS_H

#include "RBTree.h"

template<typename T, typename CMP>
bool RBTree<T, CMP>::check_properties() const {
    // Property 2
    if(root->check_color(node_color::red)) return false;

    for (auto it = begin(); it != end(); ++it) {
        Node *current = it.get_node();
        // Property 1
        if(!current->check_color(node_color::red) && !current->check_color(node_color::black)) return false;
        // Property 4
        if (current->check_color(node_color::red) && !current->has_black_children()) return false;

        // Property 5
        std::vector<unsigned int> number_black_nodes_of_paths;
        if (current->right) {
            number_black_nodes_of_paths.push_back(0);
            count_black_nodes_through_path(current->right.get(), number_black_nodes_of_paths, number_black_nodes_of_paths.size() - 1);
        } else if (current->left) {
            number_black_nodes_of_paths.push_back(0);
            count_black_nodes_through_path(current->left.get(), number_black_nodes_of_paths, number_black_nodes_of_paths.size() - 1);
        }
        if (!check_all_paths_have_same_number_of_black_nodes(number_black_nodes_of_paths)) return false;
    }

    return true;
}

template<typename T, typename CMP>
bool RBTree<T, CMP>::check_all_paths_have_same_number_of_black_nodes(
        const std::vector<unsigned int> &number_black_nodes_of_paths) const {
    if (!number_black_nodes_of_paths.empty()) {
        auto tmp = number_black_nodes_of_paths.at(0);
        for (std::size_t i = 1; i < number_black_nodes_of_paths.size(); i++) {
            if (number_black_nodes_of_paths.at(i) != tmp) return false;
        }
    }
    return true;
}

template<typename T, typename CMP>
void RBTree<T, CMP>::count_black_nodes_through_path(Node *node, std::vector<unsigned int> &number_black_nodes_of_paths,
                                                    unsigned int index_of_path) const {
    if (node && node->check_color(node_color::black)) {
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
