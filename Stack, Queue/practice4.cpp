// Practice 4. Palindromes and Balance
#include <iostream>
#include <fstream>
#include <deque> // built-in library for deque (stack + queue)
#include <map>
using namespace std;
const char PALINDROME = 'P';
const char BALANCE = 'B';

// Return true if str is a palindrome; false otherwise
bool isPalindrome(string& str) {
  deque<char> deq;
  for (int i=0; i<str.length(); i++)
    deq.push_back(str[i]);
  
  while (deq.size() >= 2) {
    if (deq.front() != deq.back()) return false;
    deq.pop_front();
    deq.pop_back();
  }

  return true;
}

// Return true if brackets are balanced in str; false otherwise
bool balance(string& str) {
  deque<char> deq;
  map<char, char> brackets;
  string bracket = "{[()]}";
  brackets['}'] = '{';
  brackets[']'] = '[';
  brackets[')'] = '(';

  for (int i=0; i<str.length(); i++) {
    if (bracket.find(str[i]) == string::npos);
    else if (deq.empty() || bracket.substr(0,3).find(str[i]) != string::npos)
      deq.push_back(str[i]);
    else if (deq.back() == brackets[str[i]])
      deq.pop_back();
  }

  return deq.empty();
}

int main() {
  ifstream inFile("infile.txt");
  ofstream outFile("outfile.txt");
  string line;
  string input;
  while (getline(inFile, line))
  {
    char op = line[0];
    switch(op)
    {
      case PALINDROME:
        input = line.substr(2);
        if(isPalindrome(input))
          outFile<<"T"<<endl;
        else
          outFile<<"F"<<endl;
        break;

      case BALANCE:
        input = line.substr(2);
        if(balance(input))
          outFile<<"T"<<endl;
        else
          outFile<<"F"<<endl;
        break;
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
