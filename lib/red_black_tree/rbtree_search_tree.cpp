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
    UpdateHeight(n1);

    n3->_lchild = t3;
    if (t3) {
        t3->_parent = n3;
    }
    n3->_rchild = t4;
    if (t4) {
        t4->_parent = n3;
    }
    UpdateHeight(n2);

    n2->_lchild = n1;
    n2->_rchild = n3;
    UpdateHeight(n3);

    return n2;
}

template <typename T>
Node<T>* SearchTree<T>::RebalanceSubtree(Node<T>* newly_inserted) {
    Node<T>* son = newly_inserted;
    Node<T>* parent = son->_parent;
    Node<T>* grandparent = parent->_parent;
    if (!(son && parent && grandparent)) {
        return nullptr;
    } else {
        if (parent->IsLChild()) {
            if (son->IsLChild()) {
                if (parent->_parent = grandparent->_parent) {
                    if (grandparent->IsLChild()) {
                        parent->_parent->_lchild = parent;
                    } else {
                        parent->_parent->_rchild = parent;
                    }
                }
                return RefactorSubtree(son, parent, grandparent,
                    son->_lchild, son->_rchild, parent->_rchild, grandparent->_rchild);
            } else {
                if (son->_parent = grandparent->_parent) {
                    if (grandparent->IsLChild()) {
                        son->_parent->_lchild = son;
                    } else {
                        son->_parent->_rchild = son;
                    }
                }
                return RefactorSubtree(parent, son, grandparent,
                    parent->_lchild, son->_lchild, son->_rchild, grandparent->_rchild);
            }
        } else {
            if (son->IsLChild()) {
                if (son->_parent = grandparent->_parent) {
                    if (grandparent->IsLChild()) {
                        son->_parent->_lchild = son;
                    } else {
                        son->_parent->_rchild = son;
                    }
                }
                return RefactorSubtree(grandparent, son, parent,
                    grandparent->_lchild, son->_lchild, son->_rchild, parent->_rchild);
            } else {
                if (parent->_parent = grandparent->_parent) {
                    if (grandparent->IsLChild()) {
                        parent->_parent->_lchild = parent;
                    } else {
                        parent->_parent->_rchild = parent;
                    }
                }
                return RefactorSubtree(grandparent, parent, son,
                    grandparent->_lchild, parent->_lchild, son->_lchild, son->_rchild);
            }
        }
    }
}

template <typename T>
Node<T>* SearchTree<T>::RemoveAt(Node<T>* posi) {
    if (posi->HasLChild() && posi->HasRChild()) {
        Node<T>* temp = posi;
        posi = posi->_rchild;
        while (posi->_lchild) {
            posi = posi->_lchild;
        }
        temp->_data = posi->_data;
    }

    Node<T>* replacer = nullptr;
    if (posi->HasLChild()) {
        replacer = posi->_lchild;
    } else {
        replacer = posi->_rchild;
    } 
    
    if (posi == this->_root) {
        this->_root = replacer;
        replacer->_parent = nullptr;
    } else {
        if (posi->IsLChild()) {
            posi->_parent->_lchild = replacer;
        } else {
            posi->_parent->_rchild = replacer;
        }
        replacer->_parent = posi->_parent;
        delete posi;
    }

    return replacer;
}