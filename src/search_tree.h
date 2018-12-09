#pragma once
#include "binary_tree.h"

template <typename T> class SearchTree : public Tree<T> {
private:
    Node<T>* SearchIn(Node<T>*& v, const T e, Node<T>*& hot);
protected:
    Node<T>* _hot; // hitted node's parent
    Node<T>* Connect34(Node<T>*, Node<T>*, Node<T>*,
        Node<T>*, Node<T>*, Node<T>*, Node<T>*);
    Node<T>* RotateAt(Node<T>* x);
public:
    Node<T>*& SearchNode(const T& e);
    virtual Node<T>*& InsertNode(const T& e);
    virtual bool RemoveNode(const T& e);
};