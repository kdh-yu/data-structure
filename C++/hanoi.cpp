#include <iostream>
#include <cmath>
using namespace std;

void hanoi(int num, int a, int b, int c) {
    if (num == 1) cout << a << " " << c << endl;
    else {
        hanoi(num-1, a, c, b);
        cout << a << " " << c << endl;
        hanoi(num-1, b, a, c);
    }
}

int main() {
    int n;
    cin >> n;
    cout << pow(2, n) - 1 << endl;
    if (n <= 20) hanoi(n, 1, 2, 3);
}