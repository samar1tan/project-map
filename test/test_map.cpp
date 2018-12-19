#include "../lib/simple_map.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    SimpleMap<int, string>* test = new SimpleMap<int, string>;
    test->insert(Entry<int, string>(42027, "Zhang Jingzhi"));
    
    cout << (*test)[42027] << endl;

    delete test;

    system("pause");
    return 0;
}