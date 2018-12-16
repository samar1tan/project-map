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
    Node<T>* RefactorSubtree(Node<T>* n1, Node<T>* n2, Node<T>* n3,
        Node<T>* t1, Node<T>* t2, Node<T>*t3, Node<T>* t4);
    Node<T>* RebalanceSubtree(Node<T>* newly_inserted);
    
    Node<T>* SearchNodeIn(const Node<T>* subtree, const T& target, Node<T>*& target_parent) const;
    Node<T>* SearchNode(const T& target, Node<T>*& target_parent) const;
};

template <typename T>
class RedBlackTree : public SearchTree<T> {
private:
    bool NeedUpdateHeight(const Node<T>* node);
 
    void SolveDoubleRed(Node<T>* newly_inserted);
    void SolveDoubleBlack(Node<T>* newly_removed);

    int black_height(const Node<T>* node) const;
    int UpdateBlackHeight(const Node<T>* node);
public:
    Node<T>* InsertNode(const T& data);
    bool RemoveNode(const T& target);
};