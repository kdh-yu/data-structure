// Practice 9. Max Heap
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
using namespace std;
const char INSERT = 'I';
const char DELETE = 'D';
const char MAXIMUM = 'M';
const int MAX_CAPACITY = 1000;

class MaxHeap {
  // Define member variables 
  int capacity;
  int count;
  int* elements;
  
  // Given the index i of element, return the index of that element's parent in the heap
  int parent(int i) {
    return (i - 1) / 2;
  }
  // Given the index i of element, return the index of that element's left child in the heap
  int left(int i) {
    return 2 * i + 1;
  }
  // Given the index i of element, return the index of that element's right child in the heap
  int right(int i) {
    return 2 * i + 2;
  }

  // Funciton for heapify (Percolate Down)
  void maxHeapify(int i);

public:
  MaxHeap(int num = MAX_CAPACITY) {
    elements = new int[num];
    count = 0;
    capacity = num;
  }
  ~MaxHeap() {
    delete elements;
  }
  
  //Insert a given element elem into the heap
  //If the insertion fails, immediately terminate the program with the error message.
  void insertElement(int);

  // Return the maximum of the heap if it exists
  // Otherwise, terminate program with an error
  int maximum();

  // Delete the maximum from the heap and return the maximum
  // If deletion fails, terminate program with an error
  int deleteMaximum();

  // Write elements at outfile
  // I made it to access to private element
  void writeElement(ofstream&);
};

void MaxHeap::maxHeapify(int i) {
  int l, r, largest, temp;
  l = this->left(i);
  r = this->right(i);
  if (l != -1 && this->elements[l] > this->elements[i])
    largest = l;
  else
    largest = i;
  
  if (r != -1 && this->elements[r] > this->elements[largest])
    largest = r;
  if (largest != i) {
    temp = this->elements[i];
    this->elements[i] = this->elements[largest];
    this->elements[largest] = temp;
    this->maxHeapify(largest);
  }
}

void MaxHeap::insertElement(int x) {
  int i = this->count;
  int p = this->parent(i);
  while (i > 0 && this->elements[p] < x) {
    this->elements[i] = this->elements[p];
    i = p;
    p = this->parent(i);
  }
  this->elements[i] = x;
  this->count++;
}

int MaxHeap::maximum() {
  if (this->count == 0) {
    cerr << "no elements" << endl;
    exit(1);
  }
  return this->elements[0];
}

int MaxHeap::deleteMaximum() {
  if (this->count == 0) {
    cerr << "heap underflow" << endl;
    exit(1);
  }
  int largest = this->elements[0];
  this->elements[0] = this->elements[this->count - 1];
  this->count--;
  this->maxHeapify(0);
  return largest;
}

void MaxHeap::writeElement(ofstream& outfile) {
  for (int i=0; i<this->count; i++)
    outfile << to_string(this->elements[i]) << " ";
  outfile << endl;
}

int main() {
  MaxHeap h;
  ifstream inFile("input.txt");
  ofstream outFile("output.txt");
  string line;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(1));
    int key;
    string name;
    // cout <<line<<endl; skipped this code
    switch(op)
    {
      case INSERT:
        if (!(iss >> key)) {
          cerr<<"INSERT: invalid input"<<endl;
          exit(1);
        }
        // TODO. Call the insertion method
        // If the insertion succeeds, write every element in the array into output file.
        h.insertElement(key);
        h.writeElement(outFile);
        break;

      case DELETE:
        // TODO. Call the deletion method
        // If the deletion succeeds, write every element in the array into output file.
        h.deleteMaximum();
        h.writeElement(outFile);
        break;

      case MAXIMUM:
        // TODO. Call the function to get the maximum
        // If getting the maximum succeeds, write the maximum into output file.
        outFile << to_string(h.maximum()) << endl;
        break;
        
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
