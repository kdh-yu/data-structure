// Practice 4. Palindromes and Balance
#include <iostream>
#include <fstream>
#include <deque> // built-in library for deque (stack + queue)
#include <map>
using namespace std;
const char PALINDROME = 'P';
const char BALANCE = 'B';

/*
Return true if str is a palindrome; false otherwise
Time complexity is O(n), since we need to check
the whole length n string.
Popping componenets takes O(1).
*/
bool isPalindrome(string& str) {
  // add each char to deque
  deque<char> deq;
  for (int i=0; i<str.length(); i++)
    deq.push_back(str[i]);
  
  // Bi-directionally checking
  while (deq.size() >= 2) {
    if (deq.front() != deq.back())
      return false;
    deq.pop_front();
    deq.pop_back();
  }

  return true;
}

// Return true if brackets are balanced in str; false otherwise
// Time complexity : O(n)
// Because we need to check whole length n string
bool balance(string& str) {
  deque<char> deq;
  map<char, char> brackets;
  string bracket = "{[()]}";
  // I used dictionary in Python, but we can't use dictionary
  // Instead, there is map
  // it's like hash, so it takes O(1)
  brackets['}'] = '{';
  brackets[']'] = '[';
  brackets[')'] = '(';

  for (int i=0; i<str.length(); i++) {
    // pass if it is not bracket
    if (bracket.find(str[i]) == string::npos);
    // stack is empty or opening bracket, then append it
    // bracket.substr(0,3) == "{[("
    else if (deq.empty() || bracket.substr(0,3).find(str[i]) != string::npos)
      deq.push_back(str[i]);
    // If matched well, instead of appending it, pop it
    // which takes O(1)
    else if (deq.back() == brackets[str[i]])
      deq.pop_back();
  }
  // Return whether stack is empty or not
  return deq.empty();
}

// Now we can check BALANCE in any string!
// Even if it has space, we can check. (as we can see in my infile.txt)
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
