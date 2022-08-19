#include "../include/Node.h"

template<typename T>
Node<T>::Node(T value): key{value}, color{node_color::red}, parent{nullptr}, right{nullptr}, left{nullptr} {}

template<typename T>
Node<T>::~Node() {
    delete[] parent;
    delete[] right;
    delete[] left;
}