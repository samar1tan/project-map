#include "rbtree.h"
#include "helpers.h"

template <typename T>
bool RedBlackTree<T>::NeedUpdateHeight(const Node<T>* node) {
    if (node->IsBlack()) {
        return node->_black_height == max<int>(2, black_height(node->_lchild), black_height(node->_rchild)) + 1;
    } else {
        return node->_black_height == max<int>(2, black_height(node->_lchild), black_height(node->_rchild));
    }
}

template <typename T>
int RedBlackTree<T>::black_height(const Node<T>* node) const{
    return (node ? node->_black_height : 0); // define NULL (outer node) 's black height as 0
}

template <typename T> 
int RedBlackTree<T>::UpdateBlackHeight(const Node<T>* node) {
    node->_black_height = max<int>(2, black_height(node->_lchild), black_height(node->_rchild));
    return (node->IsBlack() ? node->_black_height++ : node->_black_height);
}

template <typename T>
void RedBlackTree<T>::SolveDoubleRed(Node<T>*) {

}

template <typename T>
void RedBlackTree<T>::SolveDoubleBlack(Node<T>*) {

}

template <typename T> 
Node<T>* RedBlackTree<T>::InsertNode(const T& data) {

}

template <typename T> 
bool RedBlackTree<T>::RemoveNode(const T& target) {

}