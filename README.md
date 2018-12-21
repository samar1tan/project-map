# Project Map
数据结构大作业：基于[红黑树](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)简单实现[std::map](http://www.cplusplus.com/reference/map/map/)

这是**学生信息管理系统项目**的一部分
## 版本历史
- alpha (2018.12.20)
## 实现概要
- `template class SimpleMap<Key, Value>` std::map的劣质仿品
  - `template class Entry<Key, Value>` SimpleMap的元素，类似于[std::pair](http://www.cplusplus.com/reference/utility/pair/)
- `template class RedBlackTree<node_data_type>` 红黑树，其中序遍历序列中node.data.key递增
  - `template class RedBlackTree : public SearchTree<node_data_type> : public Tree<node_data_type>` 把搜索树和二叉树的一般实现丢在RBTree的父类中
  - `template class Node<node_data_type>` 树的节点，node_data_type == Entry
## 命名规范
- `lib\red_black_tree\rbtree.h` （大概是）遵循[Google开源项目风格指南](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/)
- `lib\simple_map.h` 仿照[std::map](http://www.cplusplus.com/reference/map/map/)
## 使用示例
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
## 注释信息
`simple_map.h`内的注释比较完善，包括
- 接口定义
- 实现细节
- TODO
 
*其它文件注释较少 ：）*
## 接口定义
- (constructor)
- (destructor)
- operator=
- Iterators
  - `begin` 返回指向红黑树中序遍历序列中的首节点（key最小的元素）的iterator
  - `end` 返回指向中序遍历假想的哨兵尾节点的iterator，实现为`(SimpleMap::iterator)nullptr`
  - `cbegin` 返回指向...首节点的const_iterator
  - `cend` 返回指向...尾节点的const_iterator，实现为`(SimpleMap::const_iterator)nullptr`
- Capacity
  - `empty` 为空返回true，否则为false
  - `size` 返回当前的元素个数
  - `max_size` 返回理论上Entry的最大个数，实现为`UINT_MAX`
- Element Access
  - `operator[](k)` 返回对key为k的Entry的value的引用，否则插入以k为key的新Entry并返回为其默认构造出的value的引用
  - `find(k)` 返回指向key为k的Entry的iterator，否则返回SimpleMap::end，也即`(SimpleMap::const_iterator)nullptr`
  - `count(k)` 返回key为k的Entry的个数，合法的值为0和1
  - `min` 返回指向key最小的Entry的iterator 
  - `max` 返回指向key最大的Entry的iterator
  - `data` 返回指向红黑树的指针
- Modifiers
  - `insert(element)` 返回指向新插入Entry的iterator，否则指向key相同的旧元素
  - `erase(k)` 按key删除Entry，成功时返回true，否则false
  - `erase(position)` 按iterator指示的位置删除Entry，成功时返回true，否则false
  - `clear()` 删除所有元素，并重新分配红黑树在堆中的存储位置
## 后续安排
- [ ] 测试SimpleMap的全部接口
- [ ] （*）进一步测试红黑树在随机插入、删除中的稳定性
- [ ] 与项目的另一部分合并
- [ ] 展示最终成果
- [ ] 撰写实验报告
## 参考资料
1. [《数据结构（C++语言版）（第3版）》 邓俊辉 清华大学出版社 ](https://dsa.cs.tsinghua.edu.cn/~deng/ds/dsacpp/)
2. [map - C++ Reference](http://www.cplusplus.com/reference/map/map/)