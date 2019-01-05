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
    RedBlackTree<int>* _object;
    const int _scale;
    vector<int> _data;
    vector<int> _baseline;

    void InitializeData() {
        for (int i = 1; i <= _scale; i++) {
            _data.push_back(i);
        }

        for (int i = 0; i < _scale; i++) {
            int temp = _data[i];
            srand(clock());
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
        }
        else {
            return max(height(subtree->_lchild), height(subtree->_rchild)) + 1;
        }
    }

    bool IsBalanced() {
        return height(_object->root()) <= 2 * log2(_object->size() + 1);
    }

    clock_t Insert(int elem) {
        clock_t tik = clock();
        _baseline.push_back(elem);
        clock_t tok = clock();
        _object->InsertNode(elem);
        return tok - tik;
    }

    clock_t Search(int elem) {
        clock_t tik = clock();
        vector<int>::const_iterator i = _baseline.cbegin();
        for (; i != _baseline.cend() && *i != elem; i++);
        clock_t tok = clock();
        Node<int>* query = _object->SearchNode(elem);
        return tok - tik;
    }

    clock_t Remove(int elem) {
        clock_t tik = clock();
        vector<int>::const_iterator i = _baseline.cbegin();
        for (; i != _baseline.cend() && *i != elem; i++);
        if (i != _baseline.cend()) {
            _baseline.erase(i);
        }
        clock_t tok = clock();
        _object->RemoveNode(elem);
        return tok - tik;
    }

    void PrintResult(string prompt, bool signal) {
        cout << "Checkpoint " << prompt << ": ";
        if (signal) {
            cout << "pass" << endl;
        }
        else {
            cout << "fail" << endl;
        }
    }

    bool TestInsert() {
        cout << "Term: Insert node randomly * " << _scale << endl;
        for (int i = 0; i < _scale; i++) {
            Insert(_data[i]);
        }

        bool flag_size = InRightSize();
        PrintResult("1", flag_size);
        bool flag_balance = IsBalanced();
        PrintResult("2", flag_balance);
        cout << endl;
        return flag_size && flag_balance;
    }

    bool TestSearch() {
        cout << "Term: Search node * " << _scale << endl;
        bool flag = true;
        for (int i = 0; i < _scale; i++) {
            Node<int>* query = _object->SearchNode(_data[i]);
            Node<int>* empty_query = _object->SearchNode(-_data[i]);
            if (!(flag = (query->data() == _data[i] && !empty_query))) {
                system("pause");
            }
        }
        
        PrintResult("1", flag);
        cout << endl;
        return flag;
    }

    bool TestRemoveUtil(int ratio) {
        double real_ratio = 0.0;
        string prompt = "";
        switch (ratio)
        {
        case 10: 
            real_ratio = 0.1; 
            prompt = "1";
            break;
        case 50: 
            real_ratio = 0.4; 
            prompt = "2";
            break;
        case 100: 
            prompt = "3";
            real_ratio = 0.5;
        }

        const int scale = _scale * real_ratio;

        for (int i = 0; i < scale; i++) {
            srand(clock());
            int aim = rand() % _baseline.size();
            Remove(_baseline[aim]);
        }

        cout << ratio << "% deleted" << endl;
        string temp = prompt;
        temp.append(".1");
        PrintResult(temp, InRightSize());
        PrintResult(prompt.append(".2"), IsBalanced());
        
        return InRightSize() && IsBalanced();
    }
    
    bool TestRemove() {
        cout << "Term: Remove node randomly * " << _scale << endl;
        bool flag = true;
        flag &= TestRemoveUtil(10);
        flag &= TestRemoveUtil(50);
        flag &= TestRemoveUtil(100);
        cout << endl;
        return flag;
    }

    bool TestTimeEfficiency() {
        cout << "Term: Time Efficiency * " << _scale << endl;
        
        clock_t time_vector = 0;
        clock_t clock_tree = 0;
        for (int i = 0; i < _scale; i++) {
            srand(clock());
            clock_t tik, tok, vector;
            switch (rand() % 3)
            {
            case 0: 
                tik = clock();
                vector = Insert(_data[rand() % _scale]);
                tok = clock();
                time_vector += vector;
                clock_tree += (tok - tik - vector);
                break;
            case 1:
                tik = clock();
                vector = Search(_data[rand() % _scale]);
                tok = clock();
                time_vector += vector;
                clock_tree += (tok - tik - vector);
                break;
            case 2:
                tik = clock();
                vector = Remove(_data[rand() % _scale]);
                tok = clock();
                time_vector += vector;
                clock_tree += (tok - tik - vector);
            }
        }

        cout << "Time Baseline: " << time_vector << " ms" << endl;
        cout << "Real Time: " << clock_tree << " ms" << endl;
        cout << "Speedup Ratio: " << (double)time_vector / (double)clock_tree << endl;
        PrintResult("1", clock_tree < time_vector);
        return clock_tree < time_vector;
    }
public:
    RBTTest(RedBlackTree<int>* object, int scale) : _object(object), _scale(scale), _data(), _baseline() {
        InitializeData();
    }

    void RunTest() {
        bool flag_global = true;
        flag_global &= TestInsert();
        flag_global &= TestSearch();
        flag_global &= TestRemove();
        flag_global &= TestTimeEfficiency();

        cout << "--------------------------------------------" << endl;
        cout << "All Checkpoints: ";
        if (flag_global) {
            cout << "pass" << endl;
        }
        else {
            cout << "fail" << endl;
        }
    }
};


int main() {
    RedBlackTree<int>* test = new RedBlackTree<int>;

    RBTTest tester(test, 10000);
    tester.RunTest();

    delete test;

    return 0;
}