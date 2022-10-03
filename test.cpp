#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int test [5] = {10, 15, 2};
    cout << sizeof(test)/sizeof(test[0]);
}