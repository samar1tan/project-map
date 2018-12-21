#pragma once
#include "red_black_tree\rbtree.h" // declarations and implementations of Red Black Tree, used as basic data structure of SimpleMap
#include "entry.h" // element in SimpleMap named "entry", a pair of <key, value>
#include <iterator>
#include <limits.h> // for MAX_UNSIGNED_INT, theorical max size of SimpleMap

// DECLARATIONS
template <typename Key, typename Value>
class SimpleMap {
public:
    // TODO: implement STL-style iterators
    
    class MapIterator {
    private:
        Entry<Key, Value>* _data; // not Node*
    public:
        MapIterator() : _data(nullptr) { }
        MapIterator(Entry<Key, Value>* data) : _data(data) { }
        MapIterator(Node< Entry<Key, Value> >* node): _data(&(node->_data)) { }
        

        Entry<Key, Value>* data() {
            return _data;
        }

        Entry<Key, Value>* operator!() const {
            return !_data;
        }

        MapIterator& operator=(Entry<Key, Value>* b) {
            _data = b;
            return *this;
        }

        MapIterator& operator=(Node< Entry<Key, Value> >* b) {
            _data = &(b->_data);
            return *this;
        }

        MapIterator& operator=(MapIterator& b) {
            _data = b.data();
            return *this;
        }

        bool operator==(const MapIterator& b) const {
            if (!this->data()) {
                if (!b.data()) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return *_data == *(b.data());
            }
        }

        bool operator!=(const MapIterator& b) const {
            return !((*this) == b);
        }

        // in Binary Search Tree, e.g., Red Black Tree
        // transfer to successor in inorder traversal, otherwise nullptr
        MapIterator& operator++() {
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

        Entry<Key, Value>*& operator*() const {
            return *_data;
        }

        Entry<Key, Value>* operator->() const {
            return _data;
        }
    };
    
    class ConstMapIterator {
    private:
        const Entry<Key, Value>* _data;
    public:
        ConstMapIterator() : _data(nullptr) { }
        ConstMapIterator(Entry<Key, Value>* data) : _data(data) { }
        ConstMapIterator(Node< Entry<Key, Value> >* node) : _data(node->_data) { }
        ConstMapIterator(MapIterator& x) : _data(x.data()) { }

        Entry<Key, Value>* data() {
            return _data;
        }

        ConstMapIterator& operator=(Entry<Key, Value>* b) {
            _data = b;
            return *this;
        }

        MapIterator& operator=(Node< Entry<Key, Value> >* b) {
            _data = &(b->_data);
            return *this;
        }

        ConstMapIterator& operator=(ConstMapIterator& b) {
            _data = b.data();
            return *this;
        }
        
        ConstMapIterator& operator=(MapIterator& b) {
            _data = b.data();
            return *this;
        }

        Entry<Key, Value>* operator!() const {
            return !_data;
        }

        bool operator==(const MapIterator& x) const {
            if (!this->data()) {
                if (!x.data()) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return *_data == *(x.data());
            }
        }

        bool operator!=(const MapIterator& x) const {
            return !((*this) == x);
        }

        ConstMapIterator& operator++() {
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

        const Entry<Key, Value>& operator*() const {
            return *_data;
        }

        const Entry<Key, Value>* operator->() const {
            return _data;
        }
    };

    // typedef std::reverse_iterator<iterator> reverse_iterator;
    // typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
protected:
    MapIterator _begin;
    // iterator _end; // nullptr
    // reverse_iterator _rbegin;
    // reverse_iterator _rend; // nullptr
    ConstMapIterator _cbegin;
    // const_iterator _cend; // nullptr
    // const_reverse_iterator _crbegin;
    // const_reverse_iterator _crend; // nullptr

    RedBlackTree< Entry<Key, Value> >* _data;
    unsigned int _size;

    // TODO: better implementation?
    void UpdateMemberIterators(); // update _begin, _end, _cbegin, _cend...
public:
    // Member types
    typedef Key key_type;
    typedef Value value_type; // don't like std::map
    typedef Value mapped_type; // like std::map
    typedef Entry<Key, Value> element_type;
    typedef RedBlackTree<element_type> allocator_type;
    typedef MapIterator iterator;
    typedef ConstMapIterator const_iterator;

    // Constructor
    SimpleMap() : _data(new RedBlackTree< Entry<Key, Value> >), _size(0), _begin(), _cbegin() { }; // _rbegin(), _crbegin()
    
    // Destructor
    ~SimpleMap();
    
    // Copier
    SimpleMap& operator= (const SimpleMap& x); // copy all the elements from x

    // Iterators
    MapIterator begin() const;
    MapIterator end() const; // return nullptr
    // reverse_iterator rbegin() const;
    // reverse_iterator rend() const; // return nullptr
    ConstMapIterator cbegin() const;
    ConstMapIterator cend() const; // return nullptr
    // const_reverse_iterator crbegin() const;
    // const_reverse_iterator crend() const; // return nullptr

    // Capacity 
    bool empty() const;
    size_t size() const;
    size_t max_size() const; // return max size in theory, no promise that can approach it

    // Element access
    Value& operator[] (const Key& k); // return reference to mapped value of k, otherwise reference to newly initialized default value
    MapIterator find(const Key& k) const; // return iterator to element with key = k, otherwise nullptr (SimpleMap::end)
    int count(const Key& k) const; // return number of elements with key = k, only 0 / 1 is legal
    
// because <minmax.h> included recursively
#ifdef min
    #undef min
#endif

#ifdef max
    #undef max
#endif

    MapIterator min() const; // return iterator to element with min key
    MapIterator max() const; // return iterator to element with max key
    RedBlackTree< Entry<Key, Value> >* data() const; // return pointer to root of basic Red Black Tree

    // Modifiers
    MapIterator insert(const Entry<Key, Value> element); // return reference to newly inserted element 
    bool erase(const Key& key); // erase by key and return true, otherwise false
    bool erase(MapIterator position); // erase by position and return true, otherwise false
    void clear(); // erase all elements
};


// IMPLEMENTATIONS

template <typename Key, typename Value>
SimpleMap<Key, Value>::~SimpleMap() {
    delete _data;
}

template <typename Key, typename Value>
void SimpleMap<Key, Value>::UpdateMemberIterators() {
    if (_size) {
        Node<Entry<Key, Value>>* node = _data->root();
        while (node->_lchild) {
            node = node->_lchild;
        }
        _cbegin = _begin = node;
        
        // _rbegin = _data->_root;
        // while (_rbegin->_rchild) {
        //     _rbegin = _rbegin->_rchild;
        // }
        // _crbegin = _rbegin;
    } else {
        _cbegin = _begin = (Entry<Key, Value>*)nullptr; // _rbegin = _crbegin =  
    }
}

//template <typename Key, typename Value>
//SimpleMap<Key, Value>::~SimpleMap() {
//    delete _data;
//}

template <typename Key, typename Value>
SimpleMap<Key, Value>& SimpleMap<Key, Value>::operator=(const SimpleMap<Key, Value>& x) {
    _data = x.data();
    _size = x.size();
    _begin = x.begin();
    // _rbegin = x.rbegin();
    _cbegin = x.cbegin();
    // _crbegin = x.crbegin();
}

template <typename Key, typename Value>
typename SimpleMap<Key, Value>::MapIterator SimpleMap<Key, Value>::begin() const {
    return _begin;
}

template <typename Key, typename Value>
typename SimpleMap<Key, Value>::MapIterator SimpleMap<Key, Value>::end() const {
    return (Entry<Key, Value>*)nullptr;
}

// template <typename Key, typename Value>
// typename SimpleMap<Key, Value>::reverse_iterator SimpleMap<Key,  Value>::rbegin() const {
//     return _rbegin;
// }

// template <typename Key, typename Value>
// typename SimpleMap<Key, Value>::reverse_iterator SimpleMap<Key, Value>::rend() const {
//     return nullptr;
// }

template <typename Key, typename Value>
typename SimpleMap<Key, Value>::ConstMapIterator SimpleMap<Key, Value>::cbegin() const {
    return _cbegin;
}

template <typename Key, typename Value>
typename SimpleMap<Key, Value>::ConstMapIterator SimpleMap<Key, Value>::cend() const {
    return (Entry<Key, Value>*) nullptr;
}

// template <typename Key, typename Value>
// typename SimpleMap<Key, Value>::const_reverse_iterator SimpleMap<Key, Value>::crbegin() const {
//     return _crbegin;
// }

// template <typename Key, typename Value>
// typename SimpleMap<Key, Value>::const_reverse_iterator SimpleMap<Key, Value>::crend() const {
//     return nullptr;
// }

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

template <typename Key, typename Value>
Value& SimpleMap<Key, Value>::operator[] (const Key& k) {
    Entry<Key, Value> temp(k); // build <k, placeholder(null) >, fill placeholder and return, otherwise insert temp into RBTree
    Node<Entry<Key, Value>>* is_exist = _data->SearchNode(temp); // entry1 == entry2, iff, entry1.key == entry2.key
    if (!is_exist) {
        if (_size <= max_size()) {
            return insert(temp)->value();
        } else {
            return max()->value(); // size overflow, keep saturation
        }
    } else {
        return is_exist->_data.value();
    }
}

template <typename Key, typename Value>
typename SimpleMap<Key, Value>::MapIterator SimpleMap<Key, Value>::find(const Key& k) const {
    Entry<Key, Value> temp(k);
    MapIterator result = _data->SearchNode(temp); // entry1 == entry2, iff, entry1.key == entry2.key
    return result;
}

template <typename Key, typename Value>
int SimpleMap<Key, Value>::count(const Key& k) const {
    Entry<Key, Value> temp(k);
    return _data->CountNode(temp);
}

template <typename Key, typename Value>
typename SimpleMap<Key, Value>::MapIterator SimpleMap<Key, Value>::min() const {
    return _begin; // beginning of inorder traversal in Search Tree
}

template <typename Key, typename Value>
typename SimpleMap<Key, Value>::MapIterator SimpleMap<Key, Value>::max() const {
    // reserve beginning of inorder traversal in Search Tree
    Node<Entry<Key, Value>>* temp = _data->root();
    while (temp->_rchild) {
        temp = temp->_rchild;
    }
    return temp;
}

template <typename Key, typename Value>
RedBlackTree< Entry<Key, Value> >* SimpleMap<Key, Value>::data() const {
    return _data;
}

// TODO: why not const Entry<Key, Value>& like STL?
template <typename Key, typename Value>
typename SimpleMap<Key, Value>::MapIterator SimpleMap<Key, Value>::insert(const Entry<Key, Value> element) {
    int old_size = _data->size();
    MapIterator newly_inserted = _data->InsertNode(element);
    if (old_size == _data->size()) { // element's key already exists, insertion failed
        return newly_inserted;
    } else {
        _size++;
        UpdateMemberIterators();
        return newly_inserted;
    }
}

template <typename Key, typename Value>
bool SimpleMap<Key, Value>::erase(const Key& key) {
    Entry<Key, Value> temp(key);
    bool is_successful = _data->RemoveNode(temp);
    if (is_successful) {
        _size--;
        UpdateMemberIterators();
        return true;
    } else {
        return false;
    }
}

template <typename Key, typename Value>
bool SimpleMap<Key, Value>::erase(MapIterator position) {
     return erase(position->key());
}

template <typename Key, typename Value>
void SimpleMap<Key, Value>::clear() {
    delete _data;
    _data = new RedBlackTree< Entry<Key, Value> >;
    _size = 0;
    _cbegin = _begin = (Entry<Key, Value>*)nullptr;
}