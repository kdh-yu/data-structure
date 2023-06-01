// Practice 12. Use hash tables
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;
const char TWO_SUM = 'T';
const char SYMMETRIC_PAIRS = 'S';

vector<int> readIntegers(int k, string& line) {
  vector<int> arr;
  istringstream liss(line);
  int val;
  for (int i = 0; i < k; ++i) {
    if (!(liss >> val)) {
      cerr<<"Error: invalid input value"<<endl;
      exit(1);
    }
    else {
      arr.push_back(val);
    }
  }
  return arr;
}

bool twoSum(int n, vector<int> arr) {
  unordered_map<int, bool> hashTable;
  for (int i=0; i<arr.size(); i++)
    for (int j=i; j<arr.size(); j++)
        hashTable[arr[i] + arr[j]] = true;
  return hashTable[n];
}

vector<pair<int, int> > symmetricPairs(vector<pair<int, int> > arr) {
  unordered_map<int, int> hashTable;
  vector<pair<int, int> > symmetric;
  for (vector<pair<int, int> >::iterator iter=arr.begin(); iter!=arr.end(); iter++) {
    if ((hashTable[iter->first] == iter->second) && hashTable[iter->second] == iter->first)
      symmetric.push_back(*iter);
    else {
      hashTable[iter->first] = iter->second;
      hashTable[iter->second] = iter->first;
    }
  }
  for (int i=0; i<symmetric.size(); i++)
    swap(symmetric[i].first, symmetric[i].second);
  sort(symmetric.begin(), symmetric.end());
  return symmetric;
}

int main() {
  ifstream inFile("input.txt");
  ofstream outFile("output.txt");
  string line;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(2));
    vector<int> nums;
    vector<pair<int, int> > pairs;
    vector<pair<int, int> > ans;
    vector<pair<int, int> >::iterator it;
    int k, n, a, b;
    bool exist;
    switch(op)
    {
      case TWO_SUM:
        if (!(iss >> k >> n)) {
          cerr<<"TWO_SUM: invalid input"<<endl;
          exit(1);
        }
        if (!getline(inFile, line)) {
          cerr<<"TWO_SUM: unable to read a line"<<endl;
          exit(1);
        }
        nums = readIntegers(n, line);
        exist = twoSum(k, nums);
        if (exist)
          outFile << "T" << endl;
        else
          outFile << "F" << endl;
        break;

      case SYMMETRIC_PAIRS:
        if (!(iss >> n)) {
          cerr<<"SYMMETRIC_PAIRS: invalid input"<<endl;
          exit(1);
        }
        for (int i = 0; i < n; ++i) {
          if (!getline(inFile, line)) {
            cerr<<"SYMMERIC_PAIRS: invalid input"<<endl;
            exit(1);
          }
          istringstream tiss(line);
          if (!(tiss >> a >> b)) {
            cerr<<"SYMMETRIC_PAIRS: invalid input"<<endl;
            exit(1);
          }
          pairs.push_back(make_pair(a, b));
        }
        ans = symmetricPairs(pairs);
        for (vector<pair<int, int> >::iterator iter=ans.begin(); iter!=ans.end(); iter++)
          outFile << iter->first << " " << iter->second << endl;
        // TODO
        // Take pairs as input, and run symmetricPairs(pairs)
        // Write every symmetric pair into output file
        break;

      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
