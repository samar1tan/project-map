#pragma once
#include "tree_node.h"

template <typename T>
class Tree {
protected:
    Node<T>* _root;
    int _size;

    void RemoveSubTree(Node<T>* subtree);
public:
    Tree() : _size(0), _root(nullptr) {
        return;
    }
    ~Tree();

    int size() const;
    bool IsEmpty() const;
    Node<T>* root() const;
};

template <typename T>
class SearchTree : public Tree<T>{
protected:
    virtual int UpdateHeight(Node<T>* node);

    // refactor subtree to model "3-node-4-tree"
    //        n2
    //    n1       n3
    // t1   t2   t3  t4
    Node<T>* RefactorSubtree(Node<T>* n1, Node<T>* n2, Node<T>* n3,
        Node<T>* t1, Node<T>* t2, Node<T>*t3, Node<T>* t4);
    
    // find correct order to feed into model "3-node-4-tree"  
    Node<T>* RebalanceSubtree(Node<T>* newly_inserted);

    Node<T>* RemoveAt(Node<T>* posi);
};

template <typename T>
class RedBlackTree : public SearchTree<T> {
private:
    Node<T>* SearchNodeIn(Node<T>* subtree, const T& goal, Node<T>** return_hitted_parent) const;
    void SolveDoubleRed(Node<T>* newly_inserted);
    void SolveDoubleBlack(Node<T>* removed_replacer, Node<T>* goal_parent);
    
    int height(Node<T>* node) const;
    bool IsHeightUpdated(Node<T>* node) const;
    int UpdateHeight(Node<T>* node);
public:
    Node<T>* SearchNode(const T& goal, Node<T>** return_hitted_parent) const;
    Node<T>* InsertNode(const T& data);
    bool RemoveNode(const T& goal);
};