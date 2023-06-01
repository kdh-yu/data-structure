#include <unordered_map>
#include <iostream>
using namespace std;

int main() {
    unordered_map<int, bool> map;
    map[1] = true;
    cout << map[1] << endl;
    cout << map[2] << endl;
    cout << true << endl;
}