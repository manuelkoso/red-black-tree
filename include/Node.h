#ifndef RED_BLACK_TREE_NODE_H
#define RED_BLACK_TREE_NODE_H

enum class node_color {
    red, black
};

template<typename T>
struct Node {
    Node<T> *parent;
    Node<T> *right;
    Node<T> *left;
    T key;
    node_color color;

    Node(T value) : key{value}, color{node_color::red}, parent{nullptr}, right{nullptr}, left{nullptr} {}

    Node(Node<T> *p,
         Node<T> *r, Node<T> *l, T value, node_color color) :
            parent{p}, right{r}, left{l}, key{value}, color{color}  {}

    ~Node() {
        delete[] parent;
        delete[] right;
        delete[] left;
    }
};

#endif //RED_BLACK_TREE_NODE_H
