#pragma once

template <typename K, typename V>
class Entry {
private:
    K key;
    V value;
public:
    Entry(K k = K(), V v = V()) : key(k), value(v) {

    }

    Entry(Entry<K, V> const& e) : key(e.key), value(e.value) {

    }

    bool operator== (Entry <K, V> const& e);
    bool operator!= (Entry <K, V> const& e);
    bool operator< (Entry <K, V> const& e);
    bool operator> (Entry <K, V> const& e);
};