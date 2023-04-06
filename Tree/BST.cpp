// Practice 5. Binary Search Tree
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
const char BUILD = 'B';
const char FIND_MIN = 'm';
const char FIND_MAX = 'M';

class TreeNode {
public:
  int key;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int data) {
    key = data;
    left = nullptr;
    right = nullptr;
  }
};

class BinarySearchTree {
public:
  TreeNode* root;
  BinarySearchTree(): root(nullptr) {}

  TreeNode* arrayToBST(vector<int>&);
  TreeNode* findMin();
  TreeNode* findMax();
  void printTree();
private:
  int _getHeight(TreeNode*);
  void _printSpaces(double, TreeNode*);
};

// Given a sequence arr of integers, start index l, the end index r, 
// build a binary search (sub)tree that contains keys in arr[l], ..., arr[r].
// Return the root node of the tree
TreeNode* BinarySearchTree::arrayToBST(vector<int>& arr) {
  if (arr.size() == 0) return nullptr;
  for (int i=0; i<arr.size()-1; i++)
    if (arr[i] > arr[i+1]) return nullptr;
  
  int middle = ceil((float)arr.size() / 2) - 1;
  TreeNode* root = new TreeNode(arr[middle]);

  if (arr.size() == 2)
    root->right = new TreeNode(arr[1]);
  else {
    vector<int> left_item(arr.begin(), arr.begin() + middle);
    vector<int> right_item(arr.begin() + middle + 1, arr.end());
    root->left = BinarySearchTree::arrayToBST(left_item);
    root->right = BinarySearchTree::arrayToBST(right_item);
  }

  return root;
}

// Return the node with the minimum value 
TreeNode* BinarySearchTree::findMin() {
  TreeNode* ptr = root;
  while (ptr->left != nullptr)
    ptr = ptr->left;
  return ptr;
}

// Return the node with the maximum value 
TreeNode* BinarySearchTree::findMax() {
  TreeNode* ptr = root;
  while (ptr->right != nullptr)
    ptr = ptr->right;
  return ptr;
}

int BinarySearchTree::_getHeight(TreeNode* curr) {
  if (curr == nullptr) 
    return 0;
  return 1 + max(_getHeight(curr->left), _getHeight(curr->right));
}

void BinarySearchTree::_printSpaces(double n, TreeNode* curr) {
  for(double i = 0; i < n; ++i) 
    cout<<" ";
  if (curr == nullptr)
    cout<<" ";
  else
    cout<<curr->key;
}

void BinarySearchTree::printTree() {
  if (root == nullptr)
    return;
  queue<TreeNode*> q;
  q.push(root);
  queue<TreeNode*> temp;
  int cnt = 0;
  int height = _getHeight(root) - 1;
  double nMaxNodes = pow(2, height + 1) - 1;
  while (cnt <= height) {
    TreeNode* curr = q.front();
    q.pop();
    if (temp.empty())
      _printSpaces(nMaxNodes / pow(2, cnt + 1) + height - cnt, curr);
    else
      _printSpaces(nMaxNodes / pow(2, cnt), curr);
    if (curr == nullptr) {
      temp.push(nullptr);
      temp.push(nullptr);
    }
    else {
      temp.push(curr->left);
      temp.push(curr->right);
    }
    if (q.empty()) {
      cout<<endl<<endl;
      q = temp;
      queue<TreeNode*> empty;
      swap(temp, empty);
      ++cnt;
    }
  }
}

int main() {
  BinarySearchTree tree;
  ifstream inFile("input.txt");
  ofstream outFile("output.txt");
  string line;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(1));
    int k;
    TreeNode* found = nullptr;
    vector<int> data;
    switch(op)
    {
      case BUILD:
        while (iss >> k)
          data.push_back(k);
        tree.root = tree.arrayToBST(data);
        if (tree.root) {
          outFile<<BUILD<<endl;
        }
        else {
          cerr<<"BUILD: invalid input"<<endl;
          exit(1);
        }
        tree.printTree();
        break;
      case FIND_MIN:
        found = tree.findMin();
        if (found == nullptr) {
          cerr<<"FindMin failed"<<endl;
          exit(1);
        }
        else {
          outFile<<found->key<<endl;
        }
        break;
      case FIND_MAX:
        found = tree.findMax();
        if (found == nullptr) {
          cerr<<"FindMax failed"<<endl;
          exit(1);
        }
        else {
          outFile<<found->key<<endl;
        }
        break;
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
