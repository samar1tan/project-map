#pragma once

// DECLARATION

template <typename K, typename V>
struct Entry {
    K* _key;
    V* _value;

    Entry(K k = K(), V v = V()) : _key(new K(k)), _value(new V(v)) { }

    // ~Entry();

    Entry& operator=(const Entry<K, V>& b);

    V& value() const;
    const K& key() const; // key can't be altered directly

    // assert: key is comparabled
    bool operator==(const Entry <K, V> & e);
    bool operator!=(const Entry <K, V>& e);
    bool operator<(const Entry <K, V>& e);
    bool operator>(const Entry <K, V>& e);
};


// IMPLEMENTATIONS

// template <typename K, typename V>
// Entry<K, V>::~Entry() {
//    delete _key, _value;
// }

template <typename K, typename V>
Entry<K, V>& Entry<K, V>::operator=(const Entry<K, V>& b) {
    _key = b._key;
    _value = b._value;
}

template <typename K, typename V>
V& Entry<K, V>::value() const{
    return *_value;
}

template <typename K, typename V> 
const K& Entry<K, V>::key() const{
    return *_key;
}

template <typename K, typename V>
bool Entry<K, V>::operator==(Entry <K, V> const& e) {
    return  *_key == *e._key;
}

template <typename K, typename V>
bool Entry<K, V>::operator!=(Entry <K, V> const& e) {
    return  *_key != *e._key;
}

template <typename K, typename V>
bool Entry<K, V>::operator<(Entry <K, V> const& e) {
    return  *_key < *e._key;
}

template <typename K, typename V>
bool Entry<K, V>::operator>(Entry <K, V> const& e) {
    return  *_key > *e._key;
}