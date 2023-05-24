// Practice 12. Search
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>
#include <utility>
using namespace std;
const char BINARY_SEARCH = 'B';
const char PERFECT_SQUARE = 'P';

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr<<"Correct usage: [program] [input] [output]"<<endl;
    exit(1);
  }
  ifstream inFile(argv[1]);
  ofstream outFile(argv[2]);
  string line;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(2));
    vector<int> arr;
    int size, x, index;
    switch(op)
    {
      case BINARY_SEARCH:
        // TODO
        break;
      case PERFECT_SQUARE:
        if (!(iss >> x)) {
          cerr<<"Error: invalid input"<<endl;
          exit(1);
        }
        // TODO
        break;
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
