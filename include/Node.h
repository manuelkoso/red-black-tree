#ifndef RED_BLACK_TREE_NODE_H
#define RED_BLACK_TREE_NODE_H

#include <iostream>

enum class node_color {red, black};

template<typename T>
struct Node {
    Node<T>* parent;
    Node<T>* right;
    Node<T>* left;
    T key;
    node_color color;

    Node(T value): key{value}, color{node_color::red}, parent{nullptr}, right{nullptr}, left{nullptr} {}

    ~Node() {
        delete[] parent;
        delete[] right;
        delete[] left;
    }
};

#endif //RED_BLACK_TREE_NODE_H
