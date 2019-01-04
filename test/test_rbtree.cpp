#include "..\lib\red_black_tree\rbtree.h"
#include <vector>
#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
using namespace std;

// Testing Framework for RBTree
class RBTTest {
private:
    enum INSTRUCTION { INSERT, SEARCH, REMOVE };
    
    RedBlackTree<int>* _object;
    int _scale;
    vector<int> _data;
    vector<int> _baseline;
    
    void InitializeData() {
        for (int i = 1; i <= _scale; i++) {
            _data.push_back(i);
        }

        for (int i = 0; i < _scale; i++) {
            int temp = _data[i];
            srand(time(NULL));
            int posi = i + rand() % (_scale - i);
            _data[i] = _data[posi];
            _data[posi] = temp;
        }
    }

    bool InRightSize() {
        return _baseline.size() == _object->size();
    }

    int height(Node<int>* subtree) {
        if (!subtree) {
            return 0;
        } else {
            return max(height(subtree->_lchild), height(subtree->_rchild)) + 1;
        }
    }

    bool IsBalanced() {
        return height(_object->root()) <= 2 * log2(_object->size() + 1);
    }

    time_t Insert(int elem) {
        time_t tik = time(NULL);
        _baseline.push_back(elem);
        time_t tok = time(NULL);
        _object->InsertNode(elem);
        return tok - tik;
    }

    time_t Search(int elem) {
        time_t tik = time(NULL);
        vector<int>::const_iterator i = _baseline.cbegin();
        for (; i != _baseline.cend() && *i != elem; i++);
        time_t tok = time(NULL);
        Node<int>* query = _object->SearchNode(elem);
        return tok - tik;
    }

    time_t Remove(int elem) {
        time_t tik = time(NULL);
        vector<int>::const_iterator i = _baseline.cbegin();
        for (; i != _baseline.cend() && *i != elem; i++);
        if (i != _baseline.cend()) {
            _baseline.erase(i);
        }
        time_t tok = time(NULL);
        _object->RemoveNode(elem);
        return tok - tik;
    }

    bool TestInsert() {
        cout << "Term: Insert node randomly * " << _scale << endl;
        for (int i = 0; i < _scale; i++) {
            Insert(_data[i]);
        }

        cout << "Checkpoint 1: ";
        bool flag_size = InRightSize();
        if (flag_size) {
            cout << "pass" << endl;
        }
        else {
            cout << "fail" << endl;
        }

        cout << "Checkpoint 2: ";
        bool flag_balance = IsBalanced();
        if (flag_balance) {
            cout << "pass" << endl;
        }
        else {
            cout << "fail" << endl;
        }

        return flag_size && flag_balance;
    }

    bool TestSearch() {

    }

    bool TestRemove() {

    }

    bool TestTimeEfficiency() {

    }

public:
    RBTTest(RedBlackTree<int>* object, int scale) : _object(object), _scale(scale), _data(), _baseline() {
        InitializeData();
    }

    void RunTest() {
        TestInsert();
    }
};


int main() {
    RedBlackTree<int>* test = new RedBlackTree<int>;
    
    RBTTest tester(test, 10000);
    tester.RunTest();
    
    delete test;

    return 0;
}