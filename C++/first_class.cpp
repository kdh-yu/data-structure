#include <iostream>
using namespace std;

class Person {
    static const int NAME_SIZE = 100;
    int id;
    char name[NAME_SIZE];
    // Person (int a, char b) : id(a), name(b){} // ERROR!
public:
    void aboutMe() {
        cout << "test" << endl;
    }
};

int main() {
    Person* p = new Person();  // ERROR! We need to match with constructor
    return 0;
}