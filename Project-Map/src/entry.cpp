#include "entry.h"

template <typename K, typename V>
bool Entry<K, V>::operator== (Entry <K, V> const& e) {
    return  key == e.key;
}

template <typename K, typename V>
bool Entry<K, V>::operator!= (Entry <K, V> const& e) {
    return  key != e.key;
}

template <typename K, typename V>
bool Entry<K, V>::operator< (Entry <K, V> const& e) {
    return  key < e.key;
}

template <typename K, typename V>
bool Entry<K, V>::operator> (Entry <K, V> const& e) {
    return  key > e.key;
}