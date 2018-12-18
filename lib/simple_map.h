#pragma once
#include "red_black_tree\rbtree.h" // declarations and implementations of Red Black Tree, used as basic data structure of SimpleMap
#include "entry.h" // element in SimpleMap named "entry", a pair of <key, value>
#include "iterators.h"
#include <limits> // for MAX_UNSIGNED_INT, theorical max size of SimpleMap

template <typename Key, typename Value>
class SimpleMap {
protected: // ready for derivations
    RedBlackTree< Entry<Key, Value> >* _data;
    unsigned int _size;
public:
    /* Constructor */
    SimpleMap() : _data(new RedBlackTree< Entry<Key, Value> >), _size(0) { } 
    
    /* Destructor */
    ~SimpleMap();
    
    /* Copier */
    SimpleMap& operator= (const SimpleMap& x); // copy all the elements from x

    /* Iterators */
    iterator begin() const;
    iterator end() const;
    reserve_iterator rbegin() const;
    reverse_iterator rend() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    const_reserve_iterator crbegin() const;
    const_reserve_iterator crend() const;

    /* Capacity */
    bool empty() const;
    unsigned int size() const;
    unsigned int max_size() const; // return max size in theory, no promise that can approach it

    /* Element access */
    Value& operator[] (const Key& k); // return reference to mapped value of k, otherwise reference to newly initialized default value
    iterator find(const Key& k) const; // return iterator to element with key = k, otherwise SimpleMap::end 
    int count(const Key& k) const; // return number of elements with key = k, only 0 / 1 is legal
    iterator lower_bound(const Key& k) const; // return iterator to element with min key
    iterator upper_bound(const Key& k) const; // return iterator to element with max key

    /* Modifiers */
    Entry<Key, Value> insert(const Entry<Key, Value>& element); // return copy of newly inserted element 
    Value erase(const Key& key); // erase by key, popped its mapped value
    void erase(iterator position); // erase by position directly
    void erase(iterator first, iterator last); // erase elements in range [first, last)
    void clear(); // erase all elements
};