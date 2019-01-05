#include "../lib/simple_map.h"
#include <iostream>
using namespace std;

// typedef for SimpleMap testing
typedef SimpleMap<int, char> Map;
typedef Entry<int, char> Elem;

int main() {
    Map* test = new Map;

    test->insert(Elem(1, 'a'));
    test->insert(Elem(2, 'b'));
    test->insert(Elem(3, 'c'));
    test->insert(Elem(4, 'd'));
    test->insert(Elem(5, 'e'));
    test->insert(Elem(6, 'f'));
    test->insert(Elem(7, 'g'));
    test->insert(Elem(8, 'h'));
    test->insert(Elem(9, 'i'));
    test->insert(Elem(10, 'j'));

    for (Map::iterator i = test->begin(); i != test->end(); i++) {
        cout << "(" << i->key() << ", " << i->value() << ") ";
    }
    cout << endl << endl;

    cout << "Size: " << test->size() << endl;
    cout << "Is empty? " << test->empty() << endl;
    cout << "Max Size: " << test->max_size() << endl << endl;

    cout << "The value with key 6 is '" << (*test)[6] << "'" << endl;
    cout << "The value with min key is '" << test->min()->value() << "'" << endl << endl;

    test->erase(6);
    test->erase(test->min());
    cout << "key-6 and key-min deleted" << endl << endl;

    if (!(test->find(6).data())) {
        cout << "Cannot find non-existed key-6" << endl << endl;
    }

    cout << "The amount of key-7: " << test->count(7) << endl;
    cout << "The value with max key is '" << test->max()->value() << "'" << endl << endl;

    for (Map::iterator i = test->begin(); i != test->end(); i++) {
        cout << "(" << i->key() << ", " << i->value() << ") ";
    }
    cout << endl;

    test->clear();

    delete test;

    return 0;
}