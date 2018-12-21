#include "../lib/simple_map.h"
#include <iostream>
#include <string>
using namespace std;

// typedef for test
typedef SimpleMap<int, string> Map;
typedef Entry<int, string> Elem;
typedef SimpleMap<string, int> rMap;
typedef Entry<string, int> rElem;

// test SimpleMap and also Entry
int main() {
    // Construct
    Map* test1 = new Map;
    rMap test2;
    
    // Process
    test1->insert(Elem(42027, "Zhang Jingzhi"));
    test2.insert(rElem("China Mobile", 10086));

    // Output
    cout << "42027 is stu id of " << (*test1)[42027] << endl;
    cout << "42027 is stu id of " << test1->max()->value() << endl;
    cout << test1->find(42027)->key() << " is stu id of " << test1->max()->value() << endl;
    cout << "China Mobile's TEL: " << test2["China Mobile"] << endl;

    cout << "China Mobile's TEL: " << test2["China Mobile"] << endl;

    cout << "max size of SimpleMap is " << test1->max_size() << endl;

    // Destruct
    delete test1;

    system("pause");
}