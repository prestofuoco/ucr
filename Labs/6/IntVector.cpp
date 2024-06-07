#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "IntVector.h"

using namespace std;

IntVector::IntVector (unsigned capacity, int value) {
    _size = capacity;
    _capacity = capacity;
    if (capacity != 0) {
        _data = new int[capacity];
        for (unsigned int i = 0; i < capacity; ++i) {
            _data[i] = value;
        }
    }
    else {
        _data = nullptr;
    }
}

IntVector::~IntVector() {
    delete[] _data;
    _capacity = 0;
    _size = 0;
}

unsigned IntVector::size() const {
    return _size;
}

unsigned IntVector::capacity() const {
    return _capacity;
}

bool IntVector::empty() const {
    return _size == 0;
}

const int & IntVector::at (unsigned index) const {
    if (index >= _capacity) {
        throw out_of_range("IntVector::at_range_check");
    }
    return _data[index];
}

const int & IntVector::front() const {
    return _data[0];
}

const int & IntVector::back() const {
    return _data[_size - 1];
}