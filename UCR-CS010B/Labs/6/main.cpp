#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "IntVector.h"

using namespace std;

int main() {
    IntVector vector1;
    cout << "Vector 1: " << endl;
    cout << "Test 1 - Empty vector size: " << vector1.size() << ", Capacity: " << vector1.capacity() << endl;
    cout << "Test 2 - Is empty: " << vector1.empty() << endl << endl;

    IntVector vector2(5, 10);
    cout << "Vector 2: " << endl;
    cout << "Test 2 - Size: " << vector2.size() << ", Capacity: " << vector2.capacity() << endl;

    cout << "Test 3 - All values (at): ";
    for (unsigned i = 0; i < vector2.size(); ++i) {
        cout << vector2.at(i) << " ";
    }
    cout << endl;

    cout << "Test 4 - Front: " << vector2.front() << ", Back: " << vector2.back() << endl;

    cout << "Test 5 - Is empty: " << vector2.empty() << endl;

    cout << "Test 6 - Out of range: " << vector2.at(10) << endl;

    return 0;
}