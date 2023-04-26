// Practices 6&7. Binary Search Tree Operations
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
const char BUILD = 'B';
const char FIND_MIN = 'm';
const char FIND_MAX = 'M';
const char SEARCH = 'S';
const char INSERT = 'I';
const char DELETE = 'D';
const char INORDER = 'N';
const char PREORDER = 'R';
const char POSTORDER = 'O';

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
  ~BinarySearchTree();

  TreeNode* arrayToBST(vector<int>&);
  // Return true if tree is empty; false otherwise
  // O(1)
  bool isEmpty() { return (root == nullptr); }
  TreeNode* findMin();
  TreeNode* findMax();
  TreeNode* search(TreeNode*, int);
  void insertNode(int);
  TreeNode* deleteNode(TreeNode*, int);
  void writeInorder(ofstream&, TreeNode*);
  void writePreorder(ofstream&, TreeNode*);
  void writePostorder(ofstream&, TreeNode*);
  void printTree();
private:
  int _getHeight(TreeNode*);
  void _printSpaces(double, TreeNode*);
};

BinarySearchTree::~BinarySearchTree() {
  // Practice 4
  vector<TreeNode*> stack;
  vector<TreeNode*> nodes;
  TreeNode* curr = root;
  TreeNode* prev = nullptr;
  while (curr != nullptr || !stack.empty()) {
    while (curr != nullptr) {
      stack.push_back(curr);
      curr = curr->left;
    }
    curr = stack.back();
    if (curr->right == nullptr || curr->right == prev) {
      stack.pop_back();
      nodes.push_back(curr);
      prev = curr;
      curr = nullptr;
    }
    else {
      curr = curr->right;
    }
  }
  vector<TreeNode*>::iterator it;
  for (it = nodes.begin(); it != nodes.end(); ++it)
    delete *it;
}

// Given a sequence arr of integers, start index l, the end index r, 
// build a binary search (sub)tree that contains keys in arr[l], ..., arr[r].
// Return the root node of the tree
// It is almost similar to divide part in merge sort.
// So time complexity is O(NlogN)
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
// in balanced tree, height is O(logN).
// so time complexity is O(logN)
// Here, N is the number of nodes in tree.
TreeNode* BinarySearchTree::findMin() {
  TreeNode* ptr = root;
  while (ptr->left != nullptr)
    ptr = ptr->left;
  return ptr;
}

// Return the node with the maximum value 
// in balanced tree, height is O(logN).
// so time complexity is O(logN)
// Here, N is the number of nodes in tree.
TreeNode* BinarySearchTree::findMax() {
  TreeNode* ptr = root;
  while (ptr->right != nullptr)
    ptr = ptr->right;
  return ptr;
}

// Given a query, search for the node whose key is equal to query.
// If the node exists, return the key
// Otherwise, return nullptr
// on average, time complexity is O(logN)
// Here, N is the number of nodes in tree.
TreeNode* BinarySearchTree::search(TreeNode* ptr, int query) {
  if (ptr == nullptr) return nullptr;
  // Practice 6
  if (ptr->key == query)
    return ptr;
  else if (ptr->key > query && ptr->left != nullptr)
    return BinarySearchTree::search(ptr->left, query);
  else if (ptr->key < query && ptr->right != nullptr)
    return BinarySearchTree::search(ptr->right, query);
  return ptr;
}

// If node with key k alreay exists in the tree, do nothing
// Otherwise, insert a new node with key k 
// Find location to insert : same with search, so O(logN)
// Adding Nodes : O(1)
// So, time complexity is O(logN)
void BinarySearchTree::insertNode(int k) {
  // TODO. Practice 7
  if (root == nullptr) 
    root = new TreeNode(k);
  else {
    TreeNode* ptr = BinarySearchTree::search(root, k);
    if (k < ptr->key)
      ptr->left = new TreeNode(k);
    else if (k > ptr->key)
      ptr->right = new TreeNode(k);
  }
}
// If deletion fails, immediately terminate the program
// Otherwise, delete the node with key k
// It takes tree's root and key to remove, and returns root node of that subtree.
// When calling, we just need to call like this:
// tree->root = tree->deleteNode(tree->root, key)
// On average, time complexity is O(logN).
// Here, N is the number of nodes in tree.
TreeNode* BinarySearchTree::deleteNode(TreeNode* root_, int k) {
  if (root_ == nullptr) return nullptr;
  if (k < root_->key) 
    root_->left = BinarySearchTree::deleteNode(root_->left, k);
  else if (k > root_->key)
    root_->right = BinarySearchTree::deleteNode(root_->right, k);
  else {
    if (root_->left == nullptr)
      return root_->right;
    else if (root_->right == nullptr)
      return root_->left;
    
    TreeNode* ptr = root_;
    while (ptr->left != nullptr)
      ptr = ptr->left;
    root_->key = ptr->key;
    root_->right = BinarySearchTree::deleteNode(root_->right, root_->key);
  }
  return root_;
}

// Given an output file stream, write the keys of all the nodes 
// visited in inorder traversal
// We need to visit all N nodes, so time complexity is O(N)
void BinarySearchTree::writeInorder(ofstream& outFile, TreeNode* ptr) {
  // Practice 6
  if (ptr != nullptr) {
    BinarySearchTree::writeInorder(outFile, ptr->left);
    outFile << to_string(ptr->key) << " ";
    BinarySearchTree::writeInorder(outFile, ptr->right);
  }
}

// Given an output file stream, write the keys of all the nodes 
// visited in preorder traversal
// We need to visit all N nodes, so time complexity is O(N)
void BinarySearchTree::writePreorder(ofstream& outFile, TreeNode* ptr) {
  // Practice 6
  if (ptr != nullptr) {
    outFile << to_string(ptr->key) << " ";
    BinarySearchTree::writePreorder(outFile, ptr->left);
    BinarySearchTree::writePreorder(outFile, ptr->right);
  }
}

// Given an output file stream, write the keys of all the nodes 
// visited in postorder traversal
// We need to visit all N nodes, so time complexity is O(N)
void BinarySearchTree::writePostorder(ofstream& outFile, TreeNode* ptr) {
  // Practice 6
  if (ptr != nullptr) {
    BinarySearchTree::writePostorder(outFile, ptr->left);
    BinarySearchTree::writePostorder(outFile, ptr->right);
    outFile << to_string(ptr->key) << " ";
  }
}

// O(logN)
int BinarySearchTree::_getHeight(TreeNode* curr) {
  if (curr == nullptr) 
    return 0;
  return 1 + max(_getHeight(curr->left), _getHeight(curr->right));
}

void BinarySearchTree::_printSpaces(double n, TreeNode* curr) {
  for(double i = 0; i < n; ++i) 
    cout<<"   ";
  if (curr == nullptr)
    cout<<"  ";
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
        }
        tree.printTree();
        break;

      case FIND_MIN:
        found = tree.findMin();
        if (found == nullptr) {
          cerr<<"FindMin failed"<<endl;
        }
        else {
          outFile<<found->key<<endl;
        }
        break;

      case FIND_MAX:
        found = tree.findMax();
        if (found == nullptr) {
          cerr<<"FindMax failed"<<endl;
        }
        else {
          outFile<<found->key<<endl;
        }
        break;

      case SEARCH:
        if (!(iss >> k)) {
          cerr<<"SEARCH: invalid input"<<endl;
        }
        // Practice 6. Call the function for search
        if (tree.root != nullptr) {
          if (tree.search(tree.root, k) != nullptr)
            outFile << "S " << k << endl;
        }
        break;

      case INORDER:
        // Practice 6. Call the function for inorder traversal;
        tree.writeInorder(outFile, tree.root);
        outFile << endl;
        break;

      case PREORDER:
        // Practice 6. Call the function for preorder traversal;
        tree.writePreorder(outFile, tree.root);
        outFile << endl;
        break;

      case POSTORDER:
        // Practice 6. Call the function for postorder traversal;
        tree.writePostorder(outFile, tree.root);
        outFile << endl;
        break;

      case INSERT:
        if (!(iss >> k)) {
          cerr<<"INSERT: invalid input"<<endl;
        }
        // TODO. Practice 7. Call the function for insertion
        tree.insertNode(k);
        outFile << "I " << k << endl;
        break;

      case DELETE:
        if (!(iss >> k)) {
          cerr<<"DELETE: invalid input"<<endl;
        }
        // TODO. Practice 7. Call the function for deletion
        tree.root = tree.deleteNode(tree.root, k);
        if (tree.search(tree.root, k)->key != k)
          outFile << "D " << k << endl;
        break;

      default:
        cerr<<"Undefined operator"<<endl;
    }
  }
  outFile.close();
  inFile.close();
}
