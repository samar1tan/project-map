#include "rbtree.h"
#include "helpers.h"

template <typename T>
Node<T>* RedBlackTree<T>::SearchNodeIn(Node<T>* subtree, const T& goal, Node<T>** return_hitted_parent) const {
    if (!subtree || subtree->_data == goal) {
        return subtree;
    } else {
        *return_hitted_parent = subtree;
        if (subtree->_data < goal) {
            return SearchNodeIn(subtree->_rchild, goal, &return_hitted_parent);
        } else {
            return SearchNodeIn(subtree->_lchild, goal, &return_hitted_parent);
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
        Node<T>* uncle = newly_inserted->uncle();
        Node<T>* grandparent = parent->_parent;

        if (uncle->IsBlack()) {
            Node<T>* rebalanced_subtree = RebalanceSubtree(son);
            rebalanced_subtree->_color = RB_BLACK;
            rebalanced_subtree->_lchild->_color = rebalanced_subtree->_rchild->_color = RB_RED;
        } else {
            uncle->_color = parent->_color = RB_BLACK;
            uncle->_height++;
            parent->_height++;
            grandparent->_color = RB_RED;
            SolveDoubleRed(grandparent);
        }
    }
}

template <typename T>
void RedBlackTree<T>::SolveDoubleBlack(Node<T>* removed_replacer, Node<T>* goal_parent) {
    Node<T>* parent = (removed_replacer ? removed_replacer->_parent : goal_parent);
    if (!parent) {
        return;
    }

    Node<T>* brother = (removed_replacer->IsLChild() ? parent->_rchild : parent->_lchild);

    if (brother->IsBlack()) {
        Node<T>* red_nephew = nullptr; // red left nephew > red right nephew. if all black, remain NULL
        if (!brother->_lchild->IsBlack()) {
            red_nephew = brother->_lchild;
        } else if (!brother->_rchild->IsBlack()) {
            red_nephew = brother->_rchild;
        }

        if (red_nephew) {
            RBColor old_color = parent->_color;
            Node<T>* new_parent = RebalanceSubtree(red_nephew);
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
            if (!parent->IsBlack()) {
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
        RebalanceSubtree(same_side_nephew);
        SolveDoubleBlack(removed_replacer, parent);
    }
}

template <typename T>
int RedBlackTree<T>::height(Node<T>* node) const {
    return (node ? node->_height : 0); // define NIL (outer node) 's black height as 0
}

template <typename T>
bool RedBlackTree<T>::IsHeightUpdated(Node<T>* node) const {
    return (height(node->_lchild) == height(node->_rchild)) &&
        (height(node) == (node->IsBlack() ? height(node->_lchild) + 1 : height(node->_lchild)));
}

template <typename T>
int RedBlackTree<T>::UpdateHeight(Node<T>* node) {
    node->_height = max<int>(2, height(node->_lchild), height(node->_rchild));
    return (node->IsBlack() ? node->_height++ : node->_height);
}

template <typename T>
Node<T>* RedBlackTree<T>::SearchNode(const T& goal, Node<T>** return_hitted_parent) const {
    return SearchNodeIn(this->_root, goal, &return_hitted_parent);
}

template <typename T> 
Node<T>* RedBlackTree<T>::InsertNode(const T& data) {
    Node<T>* insert_posi = nullptr;
    Node<T>* is_exist = SearchNode(data, &insert_posi);
    
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
    Node<T>* goal_parent = nullptr; 
    Node<T>* is_exist = SearchNode(goal, &goal_parent);
    if (!is_exist) {
        return false;
    } else {
        Node<T>* removed_replacer = RemoveAt(is_exist);
        if (!(--(this->_size))) {
            return true;
        } else if (!removed_replacer->_parent) {
            this->_root->_color = RB_BLACK;
            UpdateHeight(this->_root);
            return true;
        } else if (IsHeightUpdated(removed_replacer) || removed_replacer->IsBlack()) {
            return true;
        } else {
            SolveDoubleBlack(removed_replacer);
            return true;
        }
    }
}