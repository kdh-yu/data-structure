// Practice 15. Autocomplete System
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
using namespace std;
const char BUILD_TRIE = 'T';
const char AUTOCOMPLETE = 'A';
const int CHAR_SIZE = 128;

class Trie {
public:
  char data;
  vector<string> l;
  string endsHere;
  unordered_map<char, Trie*> child;
  Trie(): data(0), endsHere(""), child() {}
  Trie(char c): data(c), endsHere(""), child() {}
  void insert(string);
  string check(string);
  void search(Trie*);
};

void Trie::insert(string ss) {
  Trie* root = this;
  for (int i=0; i<ss.length(); i++) {
    if (root->child.find(ss[i]) == root->child.end()) {
      root->child[ss[i]] = new Trie(ss[i]);
    }
    root = root->child[ss[i]];
  }
  root->endsHere = ss;
}

void Trie::search(Trie* cur) {
  if (cur->endsHere != "")
    l.push_back(cur->endsHere);
  else {
    for (unordered_map<char, Trie*>::iterator iter=cur->child.begin(); iter!=cur->child.end(); iter++)
      Trie::search(cur->child[iter->first]);
  }
}

string Trie::check(string s) {
  Trie* root = this;
  int i = 0;
  for (; i<s.length(); i++) {
    if (root->child[s[i]])
      root = root->child[s[i]];
    else
      break;
  }
  if (i == s.length()) {
    l.clear();
    Trie::search(root);
  }
  string tmp = "";
  for (vector<string>::iterator iter=l.begin(); iter!=l.end(); iter++)
    tmp += *iter + " ";
  return tmp;
}


int main() {
  ifstream inFile("input.txt");
  ofstream outFile("output.txt");
  string line;
  Trie t;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(2));
    vector<string> words;
    string prefix;
    int n;
    switch(op)
    {
      case BUILD_TRIE: 
        if (!(iss >> n)) {
          cerr<<"BUILD_TRIE: invalid input"<<endl;
          exit(1);
        }
        for (int i = 0; i < n; ++i) {
          if (!getline(inFile, line)) {
            cerr<<"BUILD_TRIE: invalid input"<<endl;
            exit(1);
          }
          t.insert(line);
          //words.push_back(line);
        }
        // TODO. Bulid a trie with the stings in vector "words"
        break;

      case AUTOCOMPLETE:
        if (!(iss >> prefix)) {
          cerr<<"AUTOCOMPLETE: invalid input"<<endl;
          exit(1);
        }
        // TODO. Run autocomplete with "prefix" and write result into "outFile"
        outFile << t.check(prefix) << endl;
        break;

      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
