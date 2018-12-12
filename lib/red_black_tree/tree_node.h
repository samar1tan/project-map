#pragma once
typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T> 
struct Node {
    T _data;
    Node<T>* _parent, _left_child, _right_child;
    int _height;
    RBColor _color;

    Node(T d = T(), Node<T>* p = nullptr, Node<T>* l = nullptr, Node<T>* r = nullptr, int height = 0, RBColor c = RB_RED) : _data(d), _parent(p), _left_child(l), _right_child(r), _height(0), _color(c) {

    }

    ~Node() {
        delete _data, _height, _color, _parent, _left_child, _right_child;
    }

    Node<T>* InorderSuccessor() const;
    bool operator== (Node& bn) const {
        return _data == bn._data;
    }

    bool operator!= (Node& bn) const {
        return _data != bn._data;
    }

    bool operator< (Node& bn) const {
        return _data < bn._data;
    }

    bool operator> (Node& bn) const {
        return _data > bn._data;
    }

    void operator= (const Node& bn) {
        _data = bn._data;
        _parent = bn._parent;
        _left_child = bn._left_child;
        _right_child = bn._right_child;
        _height = bn._height;
        _color = bn._color;
    }

    Node<T>* InsertAsLC(T const&);
    Node<T>* InsertAsRC(T const&);
    template <typename VST> void TravLevel(VST&); 
    template <typename VST> void TravPre(VST&); 
    template <typename VST> void TravIn(VST&);
    template <typename VST> void TravPost(VST&);
};