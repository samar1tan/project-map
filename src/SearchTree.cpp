#include "SearchTree.h"

template <typename T> NodePosi(T) SearchTree<T>::searchIn(NodePosi(T)& v, const T e, NodePosi(T)& hot) {
    if (!v || e == v->data) {
        return v;
    } else {
        hot = v;
        return searchIn((e < v->data ? v->lc : v->rc), e, hot);
    }
}

template <typename T> NodePosi(T)& SearchTree<T>::search(const T& e) {
    return searchIn(this->_root, e, _hot = nullptr); // why need explicit "this->"?
}