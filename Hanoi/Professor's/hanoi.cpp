#include <cstdio>
#include <iostream>
using namespace std;

int hanoi(int n, int a=1, int b=2, int c=3) {
  if (n < 1)
    return 0;
  int numAToB = hanoi(n-1, a, c, b);
  cout<<"Move "<<a<<" to "<<c<<endl;
  int numBToC = hanoi(n-1, b, a, c);
  return numAToB + 1 + numBToC;
}

int main(int argc, char* argv[]) {
  int number;
  if (argc == 2) {
    number = hanoi(atoi(argv[1]));
  }
}
