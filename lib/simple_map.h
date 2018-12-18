#pragma once
#include "red_black_tree\rbtree.h" // declarations and implementations of Red Black Tree, used as basic data structure of SimpleMap
#include "entry.h" // element in SimpleMap named "entry", a pair of <key, value>
#include <iterator>
#include <limits> // for MAX_UNSIGNED_INT, theorical max size of SimpleMap

template <typename Key, typename Value>
class SimpleMap {
protected: // ready for derivations
    RedBlackTree< Entry<Key, Value> >* _data;
    unsigned int _size;
public:
    class iterator {
    public:
        iterator();
        iterator(const iterator&);
        ~iterator();

        iterator& operator=(const iterator&);
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;

        iterator& operator++();

        Entry<Key, Value>& operator*() const;
        Entry<Key, Value>* operator->() const;
    };

    class const_iterator {
        const_iterator();
        const_iterator(const const_iterator&);
        const_iterator(const iterator&);
        ~const_iterator();

        const_iterator& operator=(const const_iterator&);
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;

        const_iterator& operator++();

        Entry<Key, Value>& operator*() const;
        Entry<Key, Value>* operator->() const;
    };

    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;


    // Constructor
    SimpleMap() : _data(new RedBlackTree< Entry<Key, Value> >), _size(0) { } 
    
    // Destructor
    ~SimpleMap();
    
    // Copier
    SimpleMap& operator= (const SimpleMap& x); // copy all the elements from x

    // Iterators
    iterator begin() const;
    iterator end() const;
    reverse_iterator rbegin() const;
    reverse_iterator rend() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    // Capacity 
    bool empty() const;
    unsigned int size() const;
    unsigned int max_size() const; // return max size in theory, no promise that can approach it

    // Element access
    Value& operator[] (const Key& k); // return reference to mapped value of k, otherwise reference to newly initialized default value
    iterator find(const Key& k) const; // return iterator to element with key = k, otherwise SimpleMap::end 
    int count(const Key& k) const; // return number of elements with key = k, only 0 / 1 is legal
    iterator lower_bound(const Key& k) const; // return iterator to element with min key
    iterator upper_bound(const Key& k) const; // return iterator to element with max key

    // Modifiers
    Entry<Key, Value> insert(const Entry<Key, Value>& element); // return copy of newly inserted element 
    Value erase(const Key& key); // erase by key, popped its mapped value
    void erase(iterator position); // erase by position directly
    void erase(iterator first, iterator last); // erase elements in range [first, last)
    void clear(); // erase all elements
};