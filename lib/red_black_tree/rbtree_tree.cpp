#include "rbtree.h"

template <typename T>
void Tree<T>::RemoveSubTree(Node<T>* subtree) {
    if (subtree->HasLChild()) {
        RemoveSubTree(subtree->_lchild);
    }
    
    if (subtree->HasRChild()){
        RemoveSubTree(subtree->_rchild);
    }

    delete subtree;
}

template <typename T>
Tree<T>::~Tree() {
    if (_size > 0) {
        RemoveSubtree(_root);
    }
}

template <typename T>
int Tree<T>::size() const {
    return _size;
}

template <typename T>
bool Tree<T>::IsEmpty() const {
    return !_root;
}

template <typename T>
Node<T>* Tree<T>::root() const {
    return _root;
}