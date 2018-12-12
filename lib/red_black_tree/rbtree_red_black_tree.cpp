#include "rbtree.h"
#include "helpers.h"

template <typename T>
bool RedBlackTree<T>::NeedUpdateHeight(const Node<T>* node) {

}

template <typename T>
int RedBlackTree<T>::black_height(const Node<T>* node) {
    return (node ? node->_black_height : 0); // define NULL's black height as 0
}

template <typename T> 
int RedBlackTree<T>::UpdateBlackHeight(const Node<T>* node) {
    node->_black_height = max<int>(2, black_height(node->_lchild), black_height(node->_rchild));
    return (node->IsBlack() ? node->_black_height++ : node->_black_height);
}

template <typename T>
void RedBlackTree<T>::UpdateBlackHeightAbove(const Node<T>* node) {

}

template <typename T> 
Node<T>* RedBlackTree<T>::SearchNodeIn(const Node<T>* subtree, const T& target, Node<T>*& target_parent) const{

}

template <typename T> 
Node<T>* RedBlackTree<T>::SearchNode(const T& target, Node<T>*& target_parent) const{

}

template <typename T> 
Node<T>* RedBlackTree<T>::InsertNode(const T& data) {

}

template <typename T> 
bool RedBlackTree<T>::RemoveNode(const T& target) {

}