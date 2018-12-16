#include "rbtree.h"

template <typename T>
Node<T>* SearchTree<T>::RefactorSubtree(Node<T>* n1, Node<T>* n2, Node<T>* n3,
    Node<T>* t1, Node<T>* t2, Node<T>*t3, Node<T>* t4) {
    n1->_lchild = t1;
    if (t1) {
        t1->_parent = n1;
    }
    n1->_rchild = t2;
    if (t2) {
        t2->_parent = n1;
    }

    n3->_lchild = t3;
    if (t3) {
        t3->_parent = n3;
    }
    n3->_rchild = t4;
    if (t4) {
        t4->_parent = n3;
    }

    n2->_lchild = n1;
    n2->_rchild = n3;

    return n2;
}

template <typename T>
Node<T>* SearchTree<T>::RebalanceSubtree(Node<T>* newly_inserted) {
    if (!(newly_inserted && newly_inserted->_parent && newly_inserted->_parent->_parent)) {
        return nullptr;
    } else {
        Node<T>* parent = newly_inserted->_parent;
        Node<T>* grandparent = father->_parent;
        if (parent->IsLChild()) {
            if (newly_inserted->IsLChild()) {
                if (parent->_parent = grandparent->_parent) {
                    if (grandparent->IsLChild()) {
                        parent->_parent->_lchild = parent;
                    } else {
                        parent->_parent->_rchild = parent;
                    }
                }
                return RefactorSubtree(newly_inserted, parent, grandparent,
                    newly_inserted->_lchild, newly_inserted->_rchild, parent->_rchild, grandparent->_rchild);
            } else {
                if (newly_inserted->_parent = grandparent->_parent) {
                    if (grandparent->IsLChild()) {
                        newly_inserted->_parent->_lchild = newly_inserted;
                    } else {
                        newly_inserted->_parent->_rchild = newly_inserted;
                    }
                }
                return RefactorSubtree(parent, newly_inserted, grandparent,
                    parent->_lchild, newly_inserted->_lchild, newly_inserted->_rchild, grandparent->_rchild);
            }
        } else {
            if (newly_inserted->IsLChild()) {
                if (newly_inserted->_parent = grandparent->_parent) {
                    if (grandparent->IsLChild()) {
                        newly_inserted->_parent->_lchild = newly_inserted;
                    } else {
                        newly_inserted->_parent->_rchild = newly_inserted;
                    }
                }
                return RefactorSubtree(grandparent, newly_inserted, parent,
                    grandparent->_lchild, newly_inserted->_lchild, newly_inserted->_rchild, parent->_rchild);
            } else {
                if (parent->_parent = grandparent->_parent) {
                    if (grandparent->IsLChild()) {
                        parent->_parent->_lchild = parent;
                    } else {
                        parent->_parent->_rchild = parent;
                    }
                }
                return RefactorSubtree(grandparent, parent, newly_inserted,
                    grandparent->_lchild, parent->_lchild, newly_inserted->_lchild, newly_inserted->_rchild, );
            }
        }
    }
}

template <typename T>
Node<T>* SearchTree<T>::SearchNodeIn(const Node<T>* subtree, const T& target, Node<T>*& target_parent) const {
    if (!subtree || subtree->_data == target) {
        return subtree;
    } else {
        target_parent = subtree;
        if (subtree->_data < target) {
            return SearchNodeIn(subtree->_rchild, target, target_parent);
        } else {
            return SearchNodeIn(subtree->_lchild, target, target_parent);
        }
    }
}

template <typename T>
Node<T>* SearchTree<T>::SearchNode(const T& target, Node<T>*& target_parent) const {
    return SearchNodeIn(_root, target, target_parent);
}