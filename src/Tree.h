#pragma once
#include "Node.h"

template <typename T> class Tree {
protected:
    int _size;
    NodePosi(T) _root;
    
    virtual int updateHeight(NodePosi(T) x);
    void updateHeightAbove(NodePosi(T) x);
public:
    Tree() : _size(0), _root(nullptr) {}
    ~Tree() { if (_size > 0) remove(_root); }
    
    int size() const;
    bool empty() const;
    NodePosi(T) root() const;

    NodePosi(T) insertAsRoot(T const& e);
    NodePosi(T) insertAsLC(NodePosi(T) x, T const& e);
    NodePosi(T) insertAsRC(NodePosi(T) x, T const& e);
    NodePosi(T) attachAsLST(NodePosi(T) x, Tree<T>*& T);
    NodePosi(T) attachAsRST(NodePosi(T) x, Tree<T>*& T);
    int remove(NodePosi(T) x);
    Tree<T>* secede(NodePosi(T) x);
    template <typename VST> void travLevel(VST& visit);
    template <typename VST> void travPre(VST& visit);
    template <typename VST> void travIn(VST& visit);
    template <typename VST> void travPost(VST& visit);
};