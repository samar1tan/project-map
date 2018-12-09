#pragma once
#define NodePosi(T) Node<T>*
#define stature(p) ((p)? (p)->height : -1) // define empty tree's height = -1

typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T> struct Node {
    T data;
    NodePosi(T) parent, lc, rc;
    int height;
    RBColor color;
    
    Node(T d=T(), NodePosi(T) p=nullptr, NodePosi(T) l=nullptr, NodePosi(T) r=nullptr, int height=0, RBColor c=RB_RED ) : data(d), parent(p), lc(l), rc(r), height(0), color(c) {}
    
    int size() const; // return total number of descendants
    NodePosi(T) succ() const; // return direct successor
    bool operator== (Node const& bn) const;
    bool operator!= (Node const& bn) const;
    bool operator< (Node const& bn) const;
    bool operator> (Node const& bn) const;

    NodePosi(T) insertAsLC(T const&);
    NodePosi(T) insertAsRC(T const&);
    template <typename VST> void travLevel(VST&); 
    template <typename VST> void travPre(VST&); 
    template <typename VST> void travIn(VST&);
    template <typename VST> void travPost(VST&);   
};