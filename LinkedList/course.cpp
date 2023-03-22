#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#pragma warning(once)
using namespace std;

const char ADD = 'A';
const char DELETE = 'D';
const char FIND = 'F';

// Node
class Student {
public:
  int id;
  string name;
  Student* next = nullptr;

  Student(int i, string n): id(i), name(n) {}
};

// Linked List
class Course {
public:
  Student* head = nullptr;

  bool isEmpty() {return (head == nullptr);}
  bool addStudent(int id, string name);
  bool deleteStudent(int id);
  Student* find(int id);
  void write(ofstream& outFile);
};

bool Course::addStudent(int id, string name) {
  Student* stu = new Student(id, name);

  // if empty
  if (Course::head == nullptr)
    head = stu;

  else {
    Student* p = head;
    while (p->id < id && p->next != nullptr) {
      p = p->next;
    }
    // Same ID
    if (p->id == id)
      return false;

    // Insert node at the beginning
    if (p == head) {
      stu->next = p;
      head = stu;
    }

    // Insert node at the end
    else if (p->next == nullptr) {
      p->next = stu;
    }

    // Insert node in the middle
    else {
      stu->next = p->next;
      p->next = stu;
    }
  } 

  return true;
}

bool Course::deleteStudent(int id) {
  Student* p = head;
  while (true) {
    // If last node
    if (p->next == nullptr) {
      // Delete the first node
      if (p->id == id) {
        head = nullptr;
        return true;
      }
      // Failed to search
      else {
        return false;
      }
    }
    // Delete the first node
    else if (p == head && p->id == id) {
      head = p->next;
      return true;
    }
    else if (p->next->id == id) {
      // Delete the last node
      if (p->next->next == nullptr) {
        p->next = nullptr;
        return true;
      }
      // Delete intermediate node
      else {
        p->next = p->next->next;
        return true;
      }
    }
    else {
      // Failed to search
      if (p->next == nullptr) return false;
      // Traverse
      else p = p->next;
    }
  }
}

Student* Course::find(int id) {
  Student* p = head;
  while (p != nullptr && p->id != id) {
    p = p->next;
  }
  return p;
}

void Course::write(ofstream& outFile) {
  Student* p = head;
  while (p != nullptr) {
    outFile << p->id << " " << p->name << " ";
    p = p->next;
  }
  outFile << endl;
}

int main() {
  Course course;
  ifstream inFile("infile.txt");
  ofstream outFile("outfile_cpp.txt");
  string line;

  while (getline(inFile, line)) {
    char op = line[0];
    istringstream iss(line.substr(1));
    int id;
    string name;
    Student* found = nullptr;
    cout << line << endl;
    
    switch(op)
    {
      case ADD:
        if (!(iss >> id >> name)) {
          cerr<<"ADD: invalid input"<<endl;
          exit(1);
        }
        if (course.addStudent(id, name))
          course.write(outFile);
        else
          outFile<<"Addition failed"<<endl;
        break;

      case DELETE:
        if (!(iss >> id)) {
          cerr<<"DELETE: invalid input"<<endl;
          exit(1);
        }
        if (course.deleteStudent(id))
          course.write(outFile);
        else
          outFile<<"Deletion failed"<<endl;
        break;
        
      case FIND:
        if (!(iss >> id)) {
          cerr<<"FIND: invalid input"<<endl;
          exit(1);
        }
        found = course.find(id);
        if (found == nullptr)
          outFile<<"Search failed"<<endl;
        else
          outFile<<found->id<<" "<<found->name<<endl;
        break;

      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
  return 0;
}
