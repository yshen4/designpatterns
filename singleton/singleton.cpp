#include "singleton.hpp"
#include <assert.h>
#include <iostream>

using namespace std;

int main(void) {
    Singleton *a = Singleton::getInstance();
    Singleton *b = Singleton::getInstance();

    assert(a==b); // "Not singleton"
}
