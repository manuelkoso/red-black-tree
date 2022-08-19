#ifndef RED_BLACK_TREE_NODE_H
#define RED_BLACK_TREE_NODE_H

enum class node_color {red, black};

template<typename T>
struct Node {
    Node* parent;
    Node* right;
    Node* left;
    T key;
    node_color color;
};

#endif //RED_BLACK_TREE_NODE_H
