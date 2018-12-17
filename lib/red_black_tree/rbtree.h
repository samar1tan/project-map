#pragma once
#include "tree_node.h"
#include "helpers.h"

// DECLARATIONS

template <typename T>
class Tree {
protected:
    Node<T>* _root;
    int _size;

    void RemoveSubtree(Node<T>* subtree);
public:
    Tree() : _size(0), _root(nullptr) {
        return;
    }
    ~Tree();

    int size() const;
    bool IsEmpty() const;
    Node<T>* root() const;
};

template <typename T>
class SearchTree : public Tree<T>{
protected:
    virtual int UpdateHeight(Node<T>* node) = 0; // special definition of height in child class

    // refactor subtree to model "3-node-4-tree"
    //        n2
    //    n1       n3
    // t1   t2   t3  t4
    Node<T>* RefactorSubtree(Node<T>* n1, Node<T>* n2, Node<T>* n3,
        Node<T>* t1, Node<T>* t2, Node<T>*t3, Node<T>* t4);

    // find correct order to feed into model "3-node-4-tree"  
    Node<T>* RebalanceSubtree(Node<T>* newly_inserted);
    Node<T>* RemoveAt(Node<T>* posi, Node<T>** return_real_removed_parent);
};

template <typename T>
class RedBlackTree : public SearchTree<T> {
private:
    bool IsBlack(Node<T>* node) const;

    Node<T>* SearchNodeIn(Node<T>* subtree, const T& goal, Node<T>** return_hitted_parent) const;
    void SolveDoubleRed(Node<T>* newly_inserted);
    void SolveDoubleBlack(Node<T>* removed_replacer, Node<T>** goal_parent);
    
    int UpdateHeight(Node<T>* node);
    int height(Node<T>* node) const;
    bool IsHeightUpdated(Node<T>* node) const;
public:
    Node<T>* SearchNode(const T& goal) const;
    Node<T>* InsertNode(const T& data);
    bool RemoveNode(const T& goal);
};


// IMPLEMENTATIONS

// Tree
template <typename T>
void Tree<T>::RemoveSubtree(Node<T>* subtree) {
    if (subtree->HasLChild()) {
        RemoveSubtree(subtree->_lchild);
    }

    if (subtree->HasRChild()) {
        RemoveSubtree(subtree->_rchild);
    }

    delete subtree;
}

template <typename T>
Tree<T>::~Tree() {
    if (_size > 0) {
        RemoveSubtree(_root);
    }
}

template <typename T>
int Tree<T>::size() const {
    return _size;
}

template <typename T>
bool Tree<T>::IsEmpty() const {
    return !_root;
}

template <typename T>
Node<T>* Tree<T>::root() const {
    return _root;
}

// SearchTree
template <typename T>
Node<T>* SearchTree<T>::RefactorSubtree(Node<T>* n1, Node<T>* n2, Node<T>* n3,
    Node<T>* t1, Node<T>* t2, Node<T>*t3, Node<T>* t4) {
    n1->_lchild = t1;
    if (t1) {
        t1->_parent = n1;
    }
    n1->_rchild = t2;
    if (t2) {
        t2->_parent = n1;
    }
    UpdateHeight(n1);

    n3->_lchild = t3;
    if (t3) {
        t3->_parent = n3;
    }
    n3->_rchild = t4;
    if (t4) {
        t4->_parent = n3;
    }
    UpdateHeight(n2);

    n2->_lchild = n1;
    n1->_parent = n2;
    n2->_rchild = n3;
    n3->_parent = n2;
    UpdateHeight(n3);

    return n2;
}

template <typename T>
Node<T>* SearchTree<T>::RebalanceSubtree(Node<T>* newly_inserted) {
    Node<T>* son = newly_inserted;
    Node<T>* parent = son->_parent;
    Node<T>* grandparent = parent->_parent;
    if (!(son && parent && grandparent)) {
        return nullptr;
    } else {
        Node<T>* subtree_root = nullptr;
        if (parent->IsLChild()) {
            if (son->IsLChild()) {
                if (parent->_parent = grandparent->_parent) {
                    if (grandparent->IsLChild()) {
                        parent->_parent->_lchild = parent;
                    } else {
                        parent->_parent->_rchild = parent;
                    }
                }
                subtree_root = RefactorSubtree(son, parent, grandparent,
                    son->_lchild, son->_rchild, parent->_rchild, grandparent->_rchild);
            } else {
                if (son->_parent = grandparent->_parent) {
                    if (grandparent->IsLChild()) {
                        son->_parent->_lchild = son;
                    } else {
                        son->_parent->_rchild = son;
                    }
                }
                subtree_root = RefactorSubtree(parent, son, grandparent,
                    parent->_lchild, son->_lchild, son->_rchild, grandparent->_rchild);
            }
        } else {
            if (son->IsLChild()) {
                if (son->_parent = grandparent->_parent) {
                    if (grandparent->IsLChild()) {
                        son->_parent->_lchild = son;
                    } else {
                        son->_parent->_rchild = son;
                    }
                }
                subtree_root = RefactorSubtree(grandparent, son, parent,
                    grandparent->_lchild, son->_lchild, son->_rchild, parent->_rchild);
            } else {
                if (parent->_parent = grandparent->_parent) {
                    if (grandparent->IsLChild()) {
                        parent->_parent->_lchild = parent;
                    } else {
                        parent->_parent->_rchild = parent;
                    }
                }
                subtree_root = RefactorSubtree(grandparent, parent, son,
                    grandparent->_lchild, parent->_lchild, son->_lchild, son->_rchild);
            }
        }

        if (this->_root->_parent) {
            this->_root = subtree_root;
        }

        return subtree_root;
    }
}

template <typename T>
Node<T>* SearchTree<T>::RemoveAt(Node<T>* posi, Node<T>** return_real_removed_parent) {
    if (posi->HasLChild() && posi->HasRChild()) {
        Node<T>* temp = posi;
        posi = posi->_rchild;
        while (posi->_lchild) {
            posi = posi->_lchild;
        }
        temp->_data = posi->_data;
    }
    
    Node<T>* replacer = nullptr;
    if (!posi->HasLChild()) {
        replacer = posi->_rchild;
    } else if(!posi->HasRChild()){
        replacer = posi->_lchild;
    }

    if (posi == this->_root) {
        if (this->_size == 1) {
            this->_root = nullptr;
        } else {
            this->_root = replacer;
            replacer->_parent = nullptr;
        }
    } else {
        if (posi->IsLChild()) {
            posi->_parent->_lchild = replacer;
        } else {
            posi->_parent->_rchild = replacer;
        }

        if (replacer) {
            replacer->_parent = posi->_parent;
        }
    } 

    *return_real_removed_parent = posi->_parent;
    delete posi;

    return replacer;
}


// RedBlackTree
template <typename T>
bool RedBlackTree<T>::IsBlack(Node<T>* node) const {
    return (!node) || (node->_color == RB_BLACK);
}

template <typename T>
Node<T>* RedBlackTree<T>::SearchNodeIn(Node<T>* subtree, const T& goal, Node<T>** return_hitted_parent) const {
    if (!subtree || subtree->_data == goal) {
        return subtree;
    } else {
        if (return_hitted_parent) {
            *return_hitted_parent = subtree;
        }

        if (subtree->_data < goal) {
            return SearchNodeIn(subtree->_rchild, goal, return_hitted_parent);
        } else {
            return SearchNodeIn(subtree->_lchild, goal, return_hitted_parent);
        }
    }
}

template <typename T>
void RedBlackTree<T>::SolveDoubleRed(Node<T>* newly_inserted) {
    if (newly_inserted == this->_root) {
        this->_root->_color = RB_BLACK;
        this->_root->_height++;
    } else {
        Node<T>* son = newly_inserted;
        Node<T>* parent = newly_inserted->_parent;
        if (IsBlack(parent)) {
            return;
        }

        Node<T>* uncle = newly_inserted->uncle();
        Node<T>* grandparent = parent->_parent;

        if (IsBlack(uncle)) {
            if (son->IsLChild() == parent->IsLChild()) {
                parent->_color = RB_BLACK;
            } else {
                son->_color = RB_BLACK;
            }
            grandparent->_color = RB_RED;

            Node<T>* rebalanced_subtree = this->RebalanceSubtree(son);
        } else {
            uncle->_color = RB_BLACK;
            uncle->_height++;
            parent->_color = RB_BLACK;
            parent->_height++;
            grandparent->_color = RB_RED;
            SolveDoubleRed(grandparent);
        }
    }
}

template <typename T>
void RedBlackTree<T>::SolveDoubleBlack(Node<T>* removed_replacer, Node<T>** goal_parent) {
    Node<T>* parent = (removed_replacer ? removed_replacer->_parent : *goal_parent);
    if (!parent) {
        return;
    }

    Node<T>* brother = (removed_replacer == parent->_lchild ? parent->_rchild : parent->_lchild);

    if (IsBlack(brother)) {
        Node<T>* red_nephew = nullptr; // red left nephew > red right nephew. if all black, remain NULL
        if (!IsBlack(brother->_lchild)) {
            red_nephew = brother->_lchild;
        } else if (!IsBlack(brother->_rchild)) {
            red_nephew = brother->_rchild;
        }

        if (red_nephew) {
            RBColor old_color = parent->_color;
            Node<T>* new_parent = this->RebalanceSubtree(red_nephew);
            if (new_parent->HasLChild()) {
                new_parent->_lchild->_color = RB_BLACK;
                UpdateHeight(new_parent->_lchild);
            }
            if (new_parent->HasRChild()) {
                new_parent->_rchild->_color = RB_BLACK;
                UpdateHeight(new_parent->_rchild);
            }
            new_parent->_color = old_color;
            UpdateHeight(new_parent);
        } else {
            brother->_color = RB_RED;
            brother->_height--;
            if (!IsBlack(parent)) {
                parent->_color = RB_BLACK;
            } else {
                parent->_height--;
                SolveDoubleBlack(parent, goal_parent);
            }
        }
    } else {
        brother->_color = RB_BLACK;
        parent->_color = RB_RED;
        Node<T>* same_side_nephew = (brother->IsLChild() ? brother->_lchild : brother->_rchild);
        *goal_parent = parent;
        this->RebalanceSubtree(same_side_nephew);
        SolveDoubleBlack(removed_replacer, goal_parent);
    }
}

template <typename T>
int RedBlackTree<T>::height(Node<T>* node) const {
    return (node ? node->_height : 0); // define NIL (outer node) 's black height as 0
}

template <typename T>
int RedBlackTree<T>::UpdateHeight(Node<T>* node) {
    node->_height = max<int>(2, height(node->_lchild), height(node->_rchild));
    return (IsBlack(node) ? node->_height++ : node->_height);
}

template <typename T>
bool RedBlackTree<T>::IsHeightUpdated(Node<T>* node) const {
    return (height(node->_lchild) == height(node->_rchild)) &&
        (height(node) == (IsBlack(node) ? height(node->_lchild) + 1 : height(node->_lchild)));
}

template <typename T>
Node<T>* RedBlackTree<T>::SearchNode(const T& goal) const {
    return SearchNodeIn(this->_root, goal, nullptr);
}

template <typename T>
Node<T>* RedBlackTree<T>::InsertNode(const T& data) {
    Node<T>* insert_posi = nullptr;
    Node<T>* is_exist = SearchNodeIn(this->_root, data, &insert_posi);

    if (is_exist) {
        return is_exist;
    } else {
        Node<T>* raw = nullptr;
        if (!((this->_size)++)) {
            raw = this->_root = new Node<T>(data);
        } else {
            raw = new Node<T>(data, insert_posi);
        }

        SolveDoubleRed(raw);
        return raw;
    }
}

template <typename T>
bool RedBlackTree<T>::RemoveNode(const T& goal) {
    Node<T>* is_exist = SearchNode(goal);
    if (!is_exist) {
        return false;
    } 
    Node<T>* real_removed_parent = nullptr;
    Node<T>* removed_replacer = this->RemoveAt(is_exist, &real_removed_parent);
    if (!(--(this->_size))) {
        return true;
    }

    if (!real_removed_parent) {
        this->_root->_color = RB_BLACK;
        UpdateHeight(this->_root);
        return true;
    }

    if (IsHeightUpdated(real_removed_parent)) {
        return true;
    }

    if (!IsBlack(removed_replacer)) {
        removed_replacer->_color = RB_BLACK;
        removed_replacer->_height++;
        return true;
    }

    SolveDoubleBlack(removed_replacer, &real_removed_parent);

    return true;
}