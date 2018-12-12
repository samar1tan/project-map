#include "rbtree.h"

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

template <typename T>
template <typename VST> 
void Tree<T>::TravLevel(VST& visit) {
    if (_root)
        _root->TravLevel(visit);
}

template <typename T>
template <typename VST> 
void Tree<T>::TravPre(VST& visit) {
    if (_root)
        _root->TravPre(visit);
}

template <typename T>
template <typename VST> 
void Tree<T>::TravIn(VST& visit) {
    if (_root)
        _root->TravIn(visit);
}

template <typename T> 
template <typename VST> 
void Tree<T>::TravPost(VST& visit) {
    if (_root)
        _root->TravPost(visit);
}