// Practice 13. Sorting 
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
const char MERGE_SORT = 'M';
const char QUICK_SORT = 'Q';

void Merge(vector<int>& L, vector<int>& T, int lPos, int rPos, int rEnd) {
  int lEnd = rPos - 1;
  int tPos = lPos;
  int size = rEnd - lPos + 1;
  while (lPos <= lEnd && rPos <= rEnd) {
    if (L[lPos] > L[rPos]) 
      T[tPos++] = (L[lPos++]);
    else
      T[tPos++] = (L[rPos++]);
  }

  while (lPos <= lEnd)
    T[tPos++] = L[lPos++];
  while (rPos <= rEnd)
    T[tPos++] = L[rPos++];
  for (int i=0; i<size; ++i, --rEnd) {
    L[rEnd] = T[rEnd];
  }
}

void MergeSort(vector<int>& L, vector<int>& T, int left, int right) {
  if (left < right) {
    int mid = (left + right) / 2;
    MergeSort(L, T, left, mid);
    MergeSort(L, T, mid+1, right);
    Merge(L, T, left, mid+1, right);
  }
}

int Partition(vector<int>& L, int low, int high) {
  int pivot = L[high];
  int left = low, right = high;
  
  while (left < right) {
    while (L[left] < pivot)
      left++;
    while (L[right] >= pivot)
      right--;
    if (left < right)
      swap(L[left], L[right]);
  }

  L[high] = L[left];
  L[left] = pivot;
  return left;
}

void QuickSort(vector<int>& L, int low, int high) {
  if (low < high) {
    int p = Partition(L, low, high);
    QuickSort(L, low, p-1);
    QuickSort(L, p+1, high);
  }
}

int main() {
  ifstream inFile("input.txt");
  ofstream outFile("output.txt");
  string line;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(2));
    vector<int> arr;
    int size;
    vector<int> tempArray(10, 10);
    // cout <<line<<endl;
    getline(inFile, line);
    istringstream is(line);
    int n;
    while (is >> n)
      arr.push_back(n);

    switch(op)
    {
      case MERGE_SORT:
        // TODO
        MergeSort(arr, tempArray, 0, arr.size()-1);
        for (int i=0; i<arr.size(); i++)
          outFile << arr[i] << " ";
        outFile << endl;
        break;

      case QUICK_SORT:
        // TODO
        QuickSort(arr, 0, arr.size()-1);
        for (int i=0; i<arr.size(); i++)
          outFile << arr[i] << " ";
        outFile << endl;
        break;

      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
