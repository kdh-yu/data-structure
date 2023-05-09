#include <iostream>
#include <deque>
using namespace std;
const int SIZE = 5;

int main() {
    deque<int> stack;  // Make Stack
    stack.push_back(1);  // Push
    stack.pop_back();  // Pop
    stack.empty();  // IsEmpty
    stack.size() == SIZE;  // IsFull

    deque<int> queue;  // Make Queue
    queue.push_back(1); // Push
    queue.pop_front();  // Pop
    queue.empty();  // IsEmpty
    queue.size() == SIZE;  // IsFull
}