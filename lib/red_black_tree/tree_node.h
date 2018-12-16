#pragma once
typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T> 
struct Node {
    T _data;
    Node<T>* _parent, _lchild, _rchild;
    int _black_height;
    RBColor _color;

    Node(T d, Node<T>* p = nullptr, Node<T>* l = nullptr, Node<T>* r = nullptr, int height = 0, RBColor c = RB_RED) : _data(d), _parent(p), _lchild(l), _rchild(r), _black_height(0), _color(c) {
        return;
    }

    bool IsBlack() const;
    bool HasLChild() const;
    bool HasRChild() const;
    bool IsLChild() const;
    bool ISRChild() const;

    bool operator== (Node& bn) const;
    bool operator!= (Node& bn) const;
    bool operator< (Node& bn) const;
    bool operator> (Node& bn) const;
    void operator= (const Node& bn);

    Node<T>* InsertAsLC(T const&);
    Node<T>* InsertAsRC(T const&);
};