#include "search_tree.h"

template <typename T> Node<T>* SearchTree<T>::SearchIn(Node<T>*& v, const T e, Node<T>*& hot) {
    if (!v || e == v->data) {
        return v;
    } else {
        hot = v;
        return SearchIn((e < v->data ? v->lc : v->rc), e, hot);
    }
}

template <typename T> Node<T>*& SearchTree<T>::SearchNode(const T& e) {
    return searchIn(this->_root, e, _hot = nullptr); // why need explicit "this->"?
}