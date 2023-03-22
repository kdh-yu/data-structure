#include <iostream>
using namespace std;

int main() {
    int n = 3;
    int* pn = &n;
    pn = nullptr;
    cout << pn << endl;
    pn = &n;
    cout << pn << endl;

}