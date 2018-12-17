#pragma once
typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T> 
struct Node {
    T _data;
    Node<T>* _parent, _lchild, _rchild;
    int _height; // black height
    RBColor _color;

    // define init color as RB_RED --> init (black) height as 0
    Node(T data, Node<T>* parent = nullptr, Node<T>* lchild = nullptr, Node<T>* rchild = nullptr, int height = 0, RBColor color = RB_RED) : _data(data), _parent(parent), _lchild(lchild), _rchild(rchild), _height(height), _color(color) {
        if (parent) {
            if (parent->_data < data) {
                parent->_rchild = this;
            } else {
                parent->_lchild = this;
            }
        }
    }

    bool IsBlack() const;
    bool HasLChild() const;
    bool HasRChild() const;
    bool IsLChild() const;
    bool ISRChild() const;

    Node<T>* uncle() const;

    bool operator== (const Node& bn) const;
    bool operator!= (const Node& bn) const;
    bool operator< (const Node& bn) const;
    bool operator> (const Node& bn) const;
    void operator= (const Node& bn);
};