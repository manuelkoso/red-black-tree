#ifndef RED_BLACK_TREE_NODE_H
#define RED_BLACK_TREE_NODE_H

enum class node_color {
    none, red, black
};

template<typename T>
struct Node {
    Node<T> *parent {nullptr};
    Node<T> *right  {nullptr};
    Node<T> *left {nullptr};
    T key;
    node_color color {node_color::none};

    Node() {}

    Node(T value) :
            key{value} {}

    Node(T value, node_color color) :
            key{value}, color{color}  {}

};

#endif //RED_BLACK_TREE_NODE_H
