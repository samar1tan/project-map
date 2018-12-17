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
   
    srand(time(NULL));
    vector<int> trace;
    for (int i = 0; i < 100000; i++) {
        trace.push_back(rand() % 10000);
        test->InsertNode(trace.back());
    }

    for (int i = 9999; i > -1; i--) {
        test->RemoveNode(trace[i]);
    }
    
    delete test;

    return 0;
}