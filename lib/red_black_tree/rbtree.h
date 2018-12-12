#pragma once
#include "tree_node.h"

template <typename T>
class Tree {
protected:
    Node<T>* _root;
    int _size;
public:
    Tree() : _size(0), _root(nullptr) { }
    ~Tree();

    int size() const;
    bool IsEmpty() const;
    Node<T>* root() const;

    Node<T>* InsertAsRoot(T const& e);
    Node<T>* InsertAsLC(Node<T>* x, T const& e);
    Node<T>* InsertAsRC(Node<T>* x, T const& e);
    Node<T>* AttachAsLST(Node<T>* x, Tree<T>*& T);
    Node<T>* AttachAsRST(Node<T>* x, Tree<T>*& T);
    int RemoveSubtree(Node<T>* x);
    template <typename VST> 
    void TravLevel(VST& visit);
    template <typename VST> 
    void TravPre(VST& visit);
    template <typename VST> 
    void TravIn(VST& visit);
    template <typename VST> 
    void TravPost(VST& visit);
};

template <typename T>
class RedBlackTree : public Tree<T> {
private:
    bool NeedUpdateHeight(const Node<T>* node);

    Node<T>* SearchNodeIn(const Node<T>* subtree, const T& target, Node<T>*& target_parent) const;
    
    void SolveDoubleRed(Node<T>*);
    void SolveDoubleBlack(Node<T>*);

    int black_height(const Node<T>* node);
    int UpdateBlackHeight(const Node<T>* node);
    void UpdateBlackHeightAbove(const Node<T>* node);
public:
    Node<T>* SearchNode(const T& target, Node<T>*& target_parent) const;
    Node<T>* InsertNode(const T& data);
    bool RemoveNode(const T& target);
};