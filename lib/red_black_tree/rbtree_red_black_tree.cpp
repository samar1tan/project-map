#include "rbtree.h"
#include "helpers.h"

template <typename T>
Node<T>* RedBlackTree<T>::SearchNodeIn(Node<T>* subtree, const T& goal, Node<T>** return_hitted_parent) const {
    if (!subtree || subtree->_data == goal) {
        return subtree;
    } else {
        *return_hitted_parent = subtree;
        if (subtree->_data < goal) {
            return SearchNodeIn(subtree->_rchild, goal, &return_hitted_parent);
        } else {
            return SearchNodeIn(subtree->_lchild, goal, &return_hitted_parent);
        }
    }
}

template <typename T>
void RedBlackTree<T>::SolveDoubleRed(Node<T>* newly_inserted) {
    if (newly_inserted == _root) {
        _root->_color = RB_BLACK;
        _root->_height++;
    } else {
        Node<T>* son = newly_inserted;
        Node<T>* parent = newly_inserted->_parent;
        Node<T>* uncle = newly_inserted->uncle();
        Node<T>* grandparent = parent->_parent;

        if (uncle->IsBlack()) {
            Node<T>* rebalanced_subtree = RebalanceSubtree(son);
            rebalanced_subtree->_color = RB_BLACK;
            rebalanced_subtree->_lchild->_color = rebalanced_subtree->_rchild->_color = RB_RED;
        } else {
            uncle->_color = parent->_color = RB_BLACK;
            uncle->_height++;
            parent->_height++;
            grandparent->_color = RB_RED;
            SolveDoubleRed(grandparent);
        }
    }
}

template <typename T>
void RedBlackTree<T>::SolveDoubleBlack(Node<T>* newly_removed) {

}

template <typename T>
int RedBlackTree<T>::height(Node<T>* node) const {
    return (node ? node->_height : 0); // define NIL (outer node) 's black height as 0
}

template <typename T>
bool RedBlackTree<T>::IsHeightUpdated(Node<T>* node) const {
    return (height(node->_lchild) == height(node->_rchild)) &&
        (height(node) == (node->IsBlack() ? height(node->_lchild) + 1 : height(node->_lchild)));
}

template <typename T>
int RedBlackTree<T>::UpdateHeight(Node<T>* node) {
    node->_height = max<int>(2, height(node->_lchild), height(node->_rchild));
    return (node->IsBlack() ? node->_height++ : node->_height);
}

template <typename T>
Node<T>* RedBlackTree<T>::SearchNode(const T& goal, Node<T>** return_hitted_parent) const {
    return SearchNodeIn(_root, goal, &return_hitted_parent);
}

template <typename T> 
Node<T>* RedBlackTree<T>::InsertNode(const T& data) {
    Node<T>* insert_posi = nullptr;
    Node<T>* is_exist = SearchNode(data, &insert_posi);
    
    if (is_exist) {
        return is_exist;
    } else {
        Node<T>* raw = nullptr;
        if (!_size++) {
            raw = _root = new Node<T>(data);
        } else {
            raw = new Node<T>(data, parent = insert_posi);
        }

        SolveDoubleRed(raw);
        return raw;
    }
}

template <typename T> 
bool RedBlackTree<T>::RemoveNode(const T& goal) {
    
}