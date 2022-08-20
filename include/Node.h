#ifndef RED_BLACK_TREE_NODE_H
#define RED_BLACK_TREE_NODE_H

enum class node_color {
    none, red, black
};

template<typename T>
struct Node {
    Node<T> *parent;
    Node<T> *right;
    Node<T> *left;
    T key;
    node_color color;

    Node() : color{node_color::none} {}

    Node(T value) :
            key{value}, color{node_color::none}  {}

    Node(T value, node_color color) :
            key{value}, color{color}  {}

    ~Node() {
        delete[] parent;
        delete[] right;
        delete[] left;
    }
};

#endif //RED_BLACK_TREE_NODE_H
