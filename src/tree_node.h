#pragma once
typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T> struct Node {
    T data;
    Node<T>* parent, lc, rc;
    int height;
    RBColor color;
    
    Node(T d = T(), Node<T>* p = nullptr, Node<T>* l = nullptr, Node<T>* r = nullptr, int height = 0, RBColor c = RB_RED) : data(d), parent(p), lc(l), rc(r), height(0), color(c) {

    }
    
    int size() const; // return total number of descendants
    Node<T>* succ() const; // return direct successor
    bool operator== (Node const& bn) const;
    bool operator!= (Node const& bn) const;
    bool operator< (Node const& bn) const;
    bool operator> (Node const& bn) const;

    Node<T>* InsertAsLC(T const&);
    Node<T>* InsertAsRC(T const&);
    template <typename VST> void TravLevel(VST&); 
    template <typename VST> void TravPre(VST&); 
    template <typename VST> void TravIn(VST&);
    template <typename VST> void TravPost(VST&);
};