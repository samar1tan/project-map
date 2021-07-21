# Project Map
Course Project for `Data Structures`：Based on [Red-black tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree), simply implemented [std::map](http://www.cplusplus.com/reference/map/map/)

This is part of our Library Management System.
## Demo
```cpp
#include "lib\simple_map.h" // for Windows. '\' --> '/' on Linux 
#include <string>
#include <iostream>

SimpleMap<int, std::string> foo;
foo.insert(Entry<int, std::string> (1220, "alpha"))
std::cout << foo[1220] << " version pushed on 1220" << std::endl;
```
```
alpha version pushed on 1220
```
## Member types
- `key_type` == Entry<Key, Value>.Key
- `value_type` == Value
  - == std\::map::mapped_type
  - != std\::map::value_type
- `mapped_type` the same as above
- `element_type` == Entry<Key, Value>
  - == std\::map::value_type
- `allocator_type` == RedBlackTree< Node<Entry<Key, Value> >
- `iterator` == SimpleMap::MapIterator
## Member functions
- (constructor)
- (destructor)
- operator=
- Iterators (Forward Iterator)
  - `begin` Return the iterator of the first Entry with min key of inorder traversal
  - `end` Return the iterator of the last Entry of inorder traversal, i.e., `(SimpleMap::iterator)nullptr`
- Capacity
  - `empty` Return true if empty, otherwise false
  - `size` Return the current number of Entry
  - `max_size` Return the theoretic max amount of Entry, i.e., `UINT_MAX`
- Element Access
  - `operator[](k)` return the reference of Entry.value where key == k, otherwise, insert new Entry with key == k and return the reference of its defaultly constructed value
  - `find(k)` Return the iterator of Entry of which the key is k, otherwise SimpleMap::end, i.e., `(SimpleMap::const_iterator)nullptr`
  - `count(k)` Return the count of Entry of which the key is k, i.e., 0 / 1
  - `min` Return the iterator pointing to Entry with the minimum key
  - `max` Return the iterator pointing to Entry with the maximum key
  - `data` Return the pointer to RBTree
- Modifiers
  - `insert(element)` Return iterator pointing to newly inserted Entry, otherwise pointing to the old element identified by key
  - `erase(k)` Delete Entry by key，returning true when successful, otherwise false
  - `erase(position)` Delete Entry by iterator，returning true when successful，otherwise false
  - `clear()` Delete all elements and re-allocate the storage position of Red-black tree in the heap
## Implementation summary
- `template class SimpleMap<Key, Value>` fake std::map
  - `template class Entry<Key, Value>` the element of SimpleMap，fake [std::pair](http://www.cplusplus.com/reference/utility/pair/)
- `template class RedBlackTree<node_data_type>` Red Black Tree, in which node.data.key increases in inorder traversal
  - `template class RedBlackTree : public SearchTree<node_data_type> : public Tree<node_data_type>` put the implementation of Search Tree and Binary Tree into the parent classes of RBTree
  - `template class Node<node_data_type>` the node of the tree, of which node_data_type == Entry
## Contributing
### Coding style
- `lib\red_black_tree\rbtree.h` following [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- `lib\simple_map.h` like [std::map](http://www.cplusplus.com/reference/map/map/)
#### Comments 
There were plenty of comments in `simple_map.h`, including:
- the definition of interfaces
- implementation details
- TODOs
## Acknowledgement & References
1. [《数据结构（C++语言版）（第3版）》 邓俊辉 清华大学出版社 ](https://dsa.cs.tsinghua.edu.cn/~deng/ds/dsacpp/)
2. [map - C++ Reference](http://www.cplusplus.com/reference/map/map/)
## Checkpoints
- [x] Test all behaviors of SimpleMap
- [x] Further test the stability of Red-black tree performing random insertions and deletions
- [x] Showcase the final gains
- [x] Write the experiment report
- [ ] STL-style improvement
## Version history
- alpha (Dec. 20, 2018)
- beta (Dec. 21, 2018)
  - Due to the poor initial design, cancelled the usage of `const_iterator` that incurred the conflicts of various `const`
  - Completed the dynamic memory management under multiple layers of nested data structures
  - Added Member types into README
  - Initially tested the interfaces and fixed some bugs
- released! (Jan. 5, 2019)
- v1.0 (Jan. 5, 2019)
  - Systematically tested RedBlackTree
  - Tested all interfaces of SimpleMap
  - Fixed SimpleMap::count()
  - Fixed SimpleMap::iterator::operator++()
