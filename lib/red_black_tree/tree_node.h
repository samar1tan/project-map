#pragma once

// DECLARATION

typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T> 
struct Node {
    T* _data;
    Node<T> *_parent, *_lchild, *_rchild;
    int _height; // black height
    RBColor _color;

    // define init color as RB_RED --> init (black) height as 0
    Node(const T& data, Node<T>* parent = nullptr, Node<T>* lchild = nullptr, Node<T>* rchild = nullptr, int height = 0, RBColor color = RB_RED) : _data(new T(data)), _color(color), _parent(parent), _lchild(lchild), _rchild(rchild), _height(height) {
        if (parent) {
            if (*(parent->_data) < data) {
                parent->_rchild = this;
            } else {
                parent->_lchild = this;
            }
        }
    }

    ~Node();

    void operator= (const Node& bn);

    bool HasLChild() const;
    bool HasRChild() const;
    bool IsLChild() const;
    bool ISRChild() const;

    Node<T>* uncle() const;
};


// IMPLEMENTATIONS

template <typename T>
Node<T>::~Node() {
    delete _data;
}

template <typename T>
void Node<T>::operator= (const Node& bn) {
    _data = bn._data;
    _parent = bn._parent;
    _lchild = bn._lchild;
    _rchild = bn._rchild;
    _height = bn._height;
    _color = bn._color;
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
Node<T>* Node<T>::uncle() const {
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