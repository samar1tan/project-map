#pragma once
typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T> 
struct Node {
    T _data;
    Node<T>* _parent, _lchild, _rchild;
    int _black_height;
    RBColor _color;

    Node(T d = T(), Node<T>* p = nullptr, Node<T>* l = nullptr, Node<T>* r = nullptr, int height = 0, RBColor c = RB_RED) : _data(d), _parent(p), _lchild(l), _rchild(r), _black_height(0), _color(c) {

    }

    ~Node() {
        delete _data, _black_height, _color, _parent, _lchild, _rchild;
    }

    bool IsBlack() const;

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
        _lchild = bn._lchild;
        _rchild = bn._rchild;
        _black_height = bn._black_height;
        _color = bn._color;
    }

    Node<T>* InsertAsLC(T const&);
    Node<T>* InsertAsRC(T const&);
    template <typename VST> void TravLevel(VST&); 
    template <typename VST> void TravPre(VST&); 
    template <typename VST> void TravIn(VST&);
    template <typename VST> void TravPost(VST&);
};