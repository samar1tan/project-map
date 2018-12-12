#include "rbtree.h"

template <typename T> 
static Node<T>* SearchIn(Node<T>* v, const T e, Node<T>*& hot) {
    if (!v || e == v->_data) {
        return v;
    } else {
        hot = v;
        return SearchIn((e < v->_data ? v->_left_child : v->_right_child), e, hot);
    }
}

template <typename T> 
Node<T>* RedBlackTree<T>::SearchNode(const T& e) {
    return SearchIn(this->_root, e, _hot = nullptr); // initialize _hot & update it
}

template <typename T> 
Node<T>* RedBlackTree<T>::InsertNode(const T& e) {
    Node<T>* result = SearchNode(e);
    Node<T>* aim = (result ? result : _hot);
    Node<T>* back = nullptr;
    if (e < aim->_data) {
        back = aim->InsertAsLC(e);
    } else {
        back = aim->InsertAsRC(e);
    }

    _size++;
    UpdateHeightAbove(back);

}

template <typename T> 
bool RedBlackTree<T>::RemoveNode(const T& e) {
    Node<T>* aim = SearchNode(e);
    if (!aim) {
        return false;
    } else {
        if
    }


}