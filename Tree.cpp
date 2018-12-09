#include "Tree.h"

template <typename T>
void Tree<T>::updateHeightAbove(NodePosi(T) x) {
    if (x) {
        x->height++;
        updateHeightAbove(x->parent);
    }
}

template <typename T>
int Tree<T>::size() const {
    return _size;
}

template <typename T>
bool Tree<T>::empty() const {
    return !_root;
}

template <typename T>
NodePosi(T) Tree<T>::root() const {
    return _root;
}

template <typename T> 
template <typename VST> void Tree<T>::travLevel(VST& visit) {
    if (_root)
        _root->travLevel(visit);
}

template <typename T> 
template <typename VST> void Tree<T>::travPre(VST& visit) {
    if (_root)
        _root->travPre(visit);
}

template <typename T>
template <typename VST> void Tree<T>::travIn(VST& visit) {
    if (_root)
        _root->travIn(visit);
}

template <typename T> 
template <typename VST> void Tree<T>::travPost(VST& visit) {
    if (_root)
        _root->travPost(visit);
}