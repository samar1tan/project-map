#pragma once
#include "Tree.h"

template <typename T> class SearchTree : public Tree<T> {
private:
    NodePosi(T) searchIn(NodePosi(T)& v, const T e, NodePosi(T)& hot);
protected:
    NodePosi(T) _hot; // hitted node's parent
    NodePosi(T) connect34(NodePosi(T), NodePosi(T), NodePosi(T),
        NodePosi(T), NodePosi(T), NodePosi(T), NodePosi(T));
    NodePosi(T) rotateAt(NodePosi(T) x);
public:
    NodePosi(T)& search(const T& e);
    virtual NodePosi(T)& insert(const T& e);
    virtual bool remove(const T& e);
};