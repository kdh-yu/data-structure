#include <iostream>
using namespace std;

// Node
class Node {
public:
    int key;
    Node* next;

    Node(int k): key(k), next(nullptr) {};
};

// Linked List
class LinkedList {
public:
    Node* head;
    Node* Search(int);
    void Traverse();
    void Insert(int, int);
    void Delete(int);

    LinkedList(): head(nullptr) {};
};

Node* LinkedList::Search(int k) {
    Node* ptr = this->head;
    while (ptr != nullptr) {
        if (ptr->key == k) break;
        ptr = ptr->next;
    }
    return ptr;
}

void LinkedList::Traverse() {
    Node* ptr = this->head;
    while (ptr != nullptr) {
        cout << ptr->key << " ";
        ptr = ptr->next;
    }
    cout << endl;
}

void LinkedList::Insert(int k, int i) {
    Node* newNode = new Node(k);

    // If empty
    if (this->head == nullptr)
        this->head = newNode;
    
    else {
        Node* ptr = this->head;
        for (int t=0; t<i; t++) {
            if (ptr->next == nullptr) break;
            ptr = ptr->next;
        }

        // Insert node at the beginning
        if (ptr == this->head) {
            newNode->next = this->head;
            this->head = newNode;
        }

        // Insert node at the end
        else if (ptr->next == nullptr)
            ptr->next = newNode;
        
        // Insert node in the middle
        else {
            newNode->next = ptr->next;
            ptr->next = newNode;
        }
    }
}

void LinkedList::Delete(int k) {
    Node* ptr = this->head;

    // Find location
    while (true) {
        if (ptr == nullptr) break;
        if (ptr->key == k || ptr->next->key == k) break;
        ptr = ptr->next;
    }

    // Failed
    if (ptr == nullptr);

    // Delete node at the beginning
    else if (ptr == this->head && ptr->key == k)
        this->head = this->head->next;
    
    // Delete node at the end
    else if (ptr->next->next == nullptr && ptr->next->key == k)
        ptr->next = nullptr;
    
    // Delete node in the middle
    else
        ptr->next = ptr->next->next;
}