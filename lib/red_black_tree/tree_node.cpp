#include "tree_node.h"
#include <iostream>
using namespace std;

template <typename T> 
Node<T>* Node<T>::InorderSuccessor() const {
    if (!_right_child) {
        if (this == _parent->_left_child) {
            return _parent;
        } else {
            return nullptr;
        }
    } else {
        Node<T>* temp = _right_child;
        while (temp->_left_child) {
            temp = temp->_left_child;
        }
        return temp;
    }
}

template <typename T>
Node<T>* Node<T>::InsertAsLC(const T& e) {
    try {
        Node<T>* temp = new Node<T> (_data = e, _parent = this);
    }
    catch (const bad_alloc& foo) {
        throw "insertion failed: run out of space";
    }

    _left_child = temp;
    return temp;
}

template <typename T>
Node<T>* Node<T>::InsertAsRC(const T& e) {
    try {
        Node<T>* temp = new Node<T>(_data = e, _parent = this);
    }
    catch (const bad_alloc& foo) {
        throw "insertion failed: run out of space";
    }

    _right_child = temp;
    return temp;
}