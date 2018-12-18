#pragma once
#include "red_black_tree\rbtree.h" // declarations and implementations of Red Black Tree, used as basic data structure of SimpleMap
#include "entry.h" // element in SimpleMap named "entry", a pair of <key, value>
#include <iterator>
#include <limits.h> // for MAX_UNSIGNED_INT, theorical max size of SimpleMap

// DECLARATIONS
template <typename Key, typename Value>
class SimpleMap {
public:
    class iterator {
    private:
        Node< Entry<Key, Value> >* _data;
    public:
        iterator() : _data(nullptr) { }
        iterator(const iterator& x) : _data(x) { }

        Node< Entry<Key, Value> >* data() {
            return _data;
        }

        iterator& operator=(const iterator& b) {
            _data = b.data();
            return *this;
        }

        bool operator==(const iterator& b) const {
            return *_data == *(b.data());
        }

        bool operator!=(const iterator& b) const {
            return *_data != *(b.data());
        }

        // in Binary Search Tree, e.g., Red Black Tree
        // transfer to successor in inorder traversal, otherwise nullptr
        iterator& operator++() {
            if (_data->HasRChild()) {
                _data = _data->_rchild;
                while (_data->_lchild) {
                    _data = _data->_lchild;
                }
            } else if(_data->ISRChild()){
                _data = _data->_parent->_parent;
            } else {
                _data = _data->_parent;
            }

            return *this;
        }

        Node< Entry<Key, Value> >& operator*() const {
            return *_data;
        }

        Node< Entry<Key, Value> >* operator->() const {
            return _data->;
        }
    };

    class const_iterator {
    private:
        const Node< Entry<Key, Value> >* _data;
    public:
        const_iterator() : _data(nullptr) { }
        const_iterator(const const_iterator& cx) : _data(cx) { }
        const_iterator(const iterator& x) : _data(x) { }

        Node< Entry<Key, Value> >* data() {
            return _data;
        }

        const_iterator& operator=(const const_iterator& b) {
            _data = b.data();
            return *this;
        }
         
        bool operator==(const iterator& b) const {
            return *_data == *(b.data());
        }

        bool operator!=(const iterator& b) const {
            return *_data != *(b.data());
        }

        const_iterator& operator++() {
            if (_data->HasRChild()) {
                _data = _data->_rchild;
                while (_data->_lchild) {
                    _data = _data->_lchild;
                }
            } else if (_data->ISRChild()) {
                _data = _data->_parent->_parent;
            } else {
                _data = _data->_parent;
            }

            return *this;
        }

        const Node< Entry<Key, Value> >& operator*() const {
            return *_data;
        }

        const Node< Entry<Key, Value> >* operator->() const {
            return _data->;
        }
    };

    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
protected:
    iterator _begin;
    iterator _end;
    reverse_iterator _rbegin;
    reverse_iterator _rend;
    const_iterator _cbegin;
    const_iterator _cend;
    const_reverse_iterator _crbegin;
    const_reverse_iterator _crend;
protected:
    RedBlackTree< Entry<Key, Value> >* _data;
    unsigned int _size;
public:
    // Constructor
    SimpleMap() : _data(new RedBlackTree< Entry<Key, Value> >), _size(0), _begin(), _end(), _rbegin(), _rend(), _cbegin(), _cend(), _crbegin(), _crend() { } 
    
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
    RedBlackTree< Entry<Key, Value> >* data() const; // return pointer to root of basic Red Black Tree

    // Modifiers
    Entry<Key, Value> insert(const Entry<Key, Value>& element); // return copy of newly inserted element 
    Value erase(const Key& key); // erase by key, popped its mapped value
    void erase(iterator position); // erase by position directly
    void erase(iterator first, iterator last); // erase elements in range [first, last)
    void clear(); // erase all elements
};


// IMPLEMENTATIONS
template <typename Key, typename Value>
SimpleMap<Key, Value>::~SimpleMap() {
    delete _data;
}

template <typename Key, typename Value>
SimpleMap<Key, Value>& SimpleMap<Key, Value>::operator=(const SimpleMap<Key, Value>& x) {
    _data = x.data();
    _size = x.size();
    _begin = x.begin();
    _end = x.end();
    _rbegin = x.rbegin();
    _rend = x.rend();
    _cbegin = x.cbegin();
    _cend = x.cend();
    _crbegin = x.crbegin();
    _crend = x.crend();
}

template <typename Key, typename Value>
SimpleMap<Key, Value>::iterator SimpleMap<Key, Value>::begin() const {
    return _begin;
}

template <typename Key, typename Value>
SimpleMap<Key, Value>::iterator SimpleMap<Key, Value>::end() const {
    return _end;
}

template <typename Key, typename Value>
SimpleMap<Key, Value>::reverse_iterator SimpleMap<Key, Value>::rbegin() const {
    return _rbegin;
}

template <typename Key, typename Value>
SimpleMap<Key, Value>::reverse_iterator SimpleMap<Key, Value>::rend() const {
    return _rend;
}

template <typename Key, typename Value>
SimpleMap<Key, Value>::const_iterator SimpleMap<Key, Value>::cbegin() const {
    return _cbegin;
}

template <typename Key, typename Value>
SimpleMap<Key, Value>::const_iterator SimpleMap<Key, Value>::cend() const {
    return _cend;
}

template <typename Key, typename Value>
SimpleMap<Key, Value>::const_reverse_iterator SimpleMap<Key, Value>::crbegin() const {
    return _crbegin;
}

template <typename Key, typename Value>
SimpleMap<Key, Value>::const_reverse_iterator SimpleMap<Key, Value>::crend() const {
    return _crend;
}

template <typename Key, typename Value>
bool SimpleMap<Key, Value>::empty() const {
    return !_size;
}

template <typename Key, typename Value>
unsigned int SimpleMap<Key, Value>::size() const {
    return _size;
}

template <typename Key, typename Value>
unsigned int SimpleMap<Key, Value>::max_size() const {
    return UINT_MAX;
}




