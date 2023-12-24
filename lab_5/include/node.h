#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include <iostream>

template <typename T>
class Node {
public:
    T value;
    Node<T>* next = nullptr;
    Node<T>* prev = nullptr;

public:
    Node() = default;
    Node(const T& value);
    Node(const T& value, Node<T>* prev, Node<T>* next);
    
    void set_value(const T& value);

};

template <typename T>
Node<T>::Node(const T& value): value(value) {}

template <typename T>
Node<T>::Node(const T& value, Node<T>* prev, Node<T>* next): value(value), next(next), prev(prev) {}

template <typename T>
void Node<T>::set_value(const T& value) {
    this->value = value;
}

#endif