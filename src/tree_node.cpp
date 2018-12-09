#include "Node.h"

template <typename T>
bool Node<T>::operator== (Node const& bn) const {
    return data == bn.data;
};

template <typename T>
bool Node<T>::operator!= (Node const& bn) const {
    return data != bn.data;
};

template <typename T>
bool Node<T>::operator< (Node const& bn) const {
    return data < bn.data;
};

template <typename T>
bool Node<T>::operator> (Node const& bn) const {
    return data > bn.data;
};