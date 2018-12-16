#include "tree_node.h"

template <typename T>
bool Node<T>::IsBlack() const {
    return _color == RB_BLACK;
}

template <typename T>
bool Node<T>::HasLChild() const {
    return _lchild;
}

template <typename T>
bool Node<T>::HasRChild() const {
    return _rchild;
}

template <typename T>
bool Node<T>::IsLChild() const {
    if (!_parent) {
        return false;
    } else {
        return _parent->_lchild == this;
    }
}

template <typename T>
bool Node<T>::ISRChild() const {
    if (!_parent) {
        return false;
    } else {
        return _parent->_rchild == this;
    }
}

template <typename T>
Node<T>* Node<T>::uncle() const{
    if (!_parent || !_parent->_parent) {
        return nullptr;
    } else {
        if (_parent->IsLChild()) {
            return _parent->_parent->_rchild;
        } else {
            return _parent->_parent->_lchild;
        }
    }
}

template <typename T>
bool Node<T>::operator== (const Node& bn) const {
    return _data == bn._data;
}

template <typename T>
bool Node<T>::operator!= (const Node& bn) const {
    return _data != bn._data;
}

template <typename T>
bool Node<T>::operator< (const Node& bn) const {
    return _data < bn._data;
}

template <typename T>
bool Node<T>::operator> (const Node& bn) const {
    return _data > bn._data;
}

template <typename T>
void Node<T>::operator= (const const Node& bn) {
    _data = bn._data;
    _parent = bn._parent;
    _lchild = bn._lchild;
    _rchild = bn._rchild;
    _height = bn._height;
    _color = bn._color;
}