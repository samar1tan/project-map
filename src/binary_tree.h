#pragma once
#include "tree_node.h"

template <typename T> class Tree {
protected:
    int _size;
    Node<T>* _root;
    
    virtual int UpdateHeight(Node<T>* x);
    void UpdateHeightAbove(Node<T>* x);
public:
    Tree() : _size(0), _root(nullptr) {

    }

    ~Tree() { 
        if (_size > 0) {
            RemoveSubtree(_root);
        }
    }
    
    int size() const;
    bool IsEmpty() const;
    Node<T>* root() const;

    Node<T>* InsertAsRoot(T const& e);
    Node<T>* InsertAsLC(Node<T>* x, T const& e);
    Node<T>* InsertAsRC(Node<T>* x, T const& e);
    Node<T>* AttachAsLST(Node<T>* x, Tree<T>*& T);
    Node<T>* AttachAsRST(Node<T>* x, Tree<T>*& T);
    int RemoveSubtree(Node<T>* x);
    template <typename VST> void TravLevel(VST& visit);
    template <typename VST> void TravPre(VST& visit);
    template <typename VST> void TravIn(VST& visit);
    template <typename VST> void TravPost(VST& visit);
};