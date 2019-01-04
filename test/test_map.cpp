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
    
    string foo;
    foo.
    // Process
    test1->insert(Elem(42027, "Zhang Jingzhi"));
    test1->insert(Elem(42028, "foobar"));
    test1->insert(Elem(42029, "foo"));
    test1->insert(Elem(42030, "bar"));
    test2.insert(rElem("China Mobile", 10086));
    (*test1)[42027] = "FOOBAR";
    test1->find(42030)->value() = "Bar";
    
    // Output
    Map::iterator min = test1->min();
    cout << (++min)++->key() << endl;
    cout << min->key() << endl;
    
    cout << "China Mobile's TEL: " << test2["China Mobile"] << endl;
    test2.erase(test2.max());
    cout << "China Mobile's TEL: " << test2["China Mobile"] << endl;

    cout << "max size of SimpleMap is " << test1->max_size() << endl;

    // Destruct
    delete test1;

    system("pause");
}