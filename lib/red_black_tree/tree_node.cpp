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
Node<T>* Node<T>::InsertAsLC(const T& e) {
    _lchild = Node<T>* raw = new Node<T>(_parent = this, _data = e);
    return raw;
}

template <typename T>
Node<T>* Node<T>::InsertAsRC(const T& e) {
    _rchild = Node<T>* raw = new Node<T>(_parent = this, _data = e);
    return raw;
}

template <typename T>
bool Node<T>::operator== (Node& bn) const {
    return _data == bn._data;
}

template <typename T>
bool Node<T>::operator!= (Node& bn) const {
    return _data != bn._data;
}

template <typename T>
bool Node<T>::operator< (Node& bn) const {
    return _data < bn._data;
}

template <typename T>
bool Node<T>::operator> (Node& bn) const {
    return _data > bn._data;
}

template <typename T>
void Node<T>::operator= (const Node& bn) {
    _data = bn._data;
    _parent = bn._parent;
    _lchild = bn._lchild;
    _rchild = bn._rchild;
    _black_height = bn._black_height;
    _color = bn._color;
}