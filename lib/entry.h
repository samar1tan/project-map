#pragma once

// DECLARATION
template <typename K, typename V>
class Entry {
private:
    K key;
    V value;
public:
    Entry(K k = K(), V v = V()) : key(k), value(v) {
        return;
    }

    Entry(Entry<K, V> const& e) : key(e.key), value(e.value) {
        return;
    }

    // assert: key is comparabled
    bool operator== (Entry <K, V> const& e);
    bool operator!= (Entry <K, V> const& e);
    bool operator< (Entry <K, V> const& e);
    bool operator> (Entry <K, V> const& e);
};


// IMPLEMENTATIONS
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