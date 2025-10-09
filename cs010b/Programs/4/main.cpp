#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "IntVector.h"

using namespace std;

int main() {
    IntVector a;
    cout << "default constructor vector size value test: " << a.size() << endl << endl;

    IntVector b (10, 10);
    cout << "new vector, parameters 10 10" << endl;
    cout << "size: " << b.size() << endl;
    cout << "capacity: " << b.capacity() << endl;
    cout << "empty: " << b.empty() << endl;
    cout << "at 5: " << b.at(5) << endl;
    cout << "front: " << b.front() << endl;
    cout << "back: " << b.back() << endl;

    b.front() = 1;
    b.at(5) = 1;
    b.back() = 1;
    cout << endl << endl << "changing front, .at(5), and back to 1:" << endl;
    cout << "new vector: ";
    for (unsigned int i = 0; i < b.size(); ++i) {
        cout << b.at(i) << ' ';
    }

    cout << endl << "popping back:" << endl;
    b.pop_back();
    for (unsigned int i = 0; i < b.size(); ++i) {
        cout << b.at(i) << ' ';
    }

    cout << endl << "pushing back 2: " << endl;
    b.push_back(2); 
    for (unsigned int i = 0; i < b.size(); ++i) {
        cout << b.at(i) << ' ';
    }

    cout << endl << "erasing index 5: " << endl;
    b.erase(5);
    for (unsigned int i = 0; i < b.size(); ++i) {
        cout << b.at(i) << ' ';
    }

    cout << endl << "using reserve 20 and resizing to 12: " << endl;
    b.reserve(20);
    b.resize(12);
    for (unsigned int i = 0; i < b.size(); ++i) {
        cout << b.at(i) << ' ';
    }
    cout << endl << "capacity: " << b.capacity() << endl;

    cout << endl << "inserting 7 at index 6: " << endl;
    b.insert(6, 7);
    for (unsigned int i = 0; i < b.size(); ++i) {
        cout << b.at(i) << ' ';
    }
    
    cout << endl << "clearing vector..." << endl;
    b.clear();

    cout << "out of range check .at(1): " << b.at(1) << endl;

    return 0;
}