#include "..\lib\red_black_tree\rbtree.h"
#include <vector>
#include <iostream>
#include <random>
#include <time.h>
using namespace std;

// TODO: Testing Framework for RBTree
/*
enum CONTROL {
    SEARCH, INSERT, REMOVE
};

class TestFramework {
private:
    vector<int> _data_path;
    vector<CONTROL> _control_path;
public:
    TestFramework(vector<int>data_path, vector<CONTROL> control_path) : _data_path(data_path), _control_path(control_path) {
        cout << "Red Black Tree Testing Info:" << endl;
        cout << "1. Size of test data (int): " << data_path.size() << endl;
        int 
        cout << "2. "
    }

    bool TestSearch() {

    }

    bool TestInsert() {

    }

    bool TestRemove() {
    
    }

};
*/

int main() {
    RedBlackTree<int>* test = new RedBlackTree<int>;
    test->InsertNode(10086);
    test->InsertNode(10000);
    test->InsertNode(10010);
    test->InsertNode(12315);
    test->InsertNode(12306);

    int no_exist = 10086;
    test->RemoveNode(no_exist);
    Node<int>* goal = nullptr;
    if (goal = test->SearchNode(no_exist)) {
        cout << "fail: searching no-exist " << no_exist << " -> " << goal->_data << endl;
    } else {
        cout << "success: searching no-exist " << no_exist << endl;
    }

    int exist = 10000;
    if (goal = test->SearchNode(exist)) {
        cout << "success: searching exist " << exist << ": " << goal->_data << endl;
    } else {
        cout << "fail: searching exist " << exist << endl;
    }

    srand(time(NULL));
    for (int i = 0; i < 1000; i++) {
        test->InsertNode(rand() % 10000);
    }

    for (int i = 0; i < 1000; i++) {
        test->RemoveNode(rand() % 10000);
    }
    
    delete test;

    return 0;
}