#pragma once

// DECLARATION

template <typename K, typename V>
struct Entry {
    K _key;
    V _value;
    
    typedef K key_type;
    typedef V value_type;

    Entry(K k = K(), V v = V()) : _key(k), _value(v) { }

    Entry& operator=(const Entry<K, V>& b);

    V& value();
    const K& key() const; // key can't be altered directly

    // assert: key is comparable
    bool operator==(const Entry <K, V> & e) const;
    bool operator!=(const Entry <K, V>& e) const;
    bool operator<(const Entry <K, V>& e) const;
    bool operator>(const Entry <K, V>& e) const;
};


// IMPLEMENTATIONS

template <typename K, typename V>
Entry<K, V>& Entry<K, V>::operator=(const Entry<K, V>& b) {
    _key = b._key;
    _value = b._value;

    return *this;
}

template <typename K, typename V>
V& Entry<K, V>::value() { // value can be altered directly
    return _value;
}

template <typename K, typename V> 
const K& Entry<K, V>::key() const{ // key can't be altered directly
    return _key;
}

template <typename K, typename V>
bool Entry<K, V>::operator==(Entry <K, V> const& e) const{
    return _key == e._key;
}

template <typename K, typename V>
bool Entry<K, V>::operator!=(Entry <K, V> const& e) const{
    return _key != e._key;
}

template <typename K, typename V>
bool Entry<K, V>::operator<(Entry <K, V> const& e) const{
    return _key < e._key;
}

template <typename K, typename V>
bool Entry<K, V>::operator>(Entry <K, V> const& e) const{
    return _key > e._key;
}