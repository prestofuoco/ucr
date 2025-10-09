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
    if (index >= _size) {
        throw out_of_range("IntVector::at_range_check");
    }
    return _data[index];
}

int & IntVector::at (unsigned index) {
    if (index >= _size) {
        throw out_of_range("IntVector::at_range_check");
    }
    return _data[index]; 
}

void IntVector::insert (unsigned index, int value) {
    if (index > _size) {
        throw out_of_range("IntVector::insert_range_check");
    }
    if (_size == _capacity) {
        expand();
    }
    for (unsigned i = _size; i > index; i--) {
        _data[i] = _data[i - 1];
    }
    _data[index] = value;
    ++_size;
}

void IntVector::erase (unsigned index) {
    if (index >= _size) {
        throw out_of_range("IntVector::erase_range_check");
    }
    for (unsigned int i = index; i < _size - 1; ++i) {
        _data[i] = _data[i+1];
    }
    --_size;
}

const int & IntVector::front() const {
    return _data[0];
}

int & IntVector::front() {
    return _data[0];
}

const int & IntVector::back() const {
    return _data[_size - 1];
}

int & IntVector::back() {
    return _data[_size - 1];
}

void IntVector::assign (unsigned n, int value) {
    if (n > _capacity) {
        if (_capacity * 2 >= n - _capacity) {
            expand();
        } 
        else {
            expand(n - _capacity);
        }
    }
    int* temp = new int[n];
    for (unsigned int i = 0; i < n; ++i) {
        temp[i] = value;
    }
    delete[] _data;
    _data = temp;
    _size = n;
    if (n > _capacity) {
        _capacity = n;
    }
}

void IntVector::push_back (int value) {
    if (_size == _capacity) {
        expand();
    }
    _data[_size] = value;
    ++_size;
}

void IntVector::pop_back() {
    --_size;
}

void IntVector::clear() {
    _size = 0;
}

void IntVector::resize (unsigned size, int value) {
    if (size > _capacity) {
        if (_capacity * 2 >= size - _capacity) {
            expand();
        } 
        else {
            expand(size - _capacity);
        }
    }
    int* temp = new int[size];
    for (unsigned int i = 0; i < _size && i < size; ++i) {
        temp[i] = _data[i];
    }
    for (unsigned int i = _size; i < size; ++i) {
        temp[i] = value;
    }
    delete[] _data;
    _data = new int[size];    
    for (unsigned int i = 0; i < size; ++i) {
        _data[i] = temp[i];
    }
    if (size > _capacity) {
        _capacity = size;
    }
    delete[] temp;
    _size = size;
}

void IntVector::reserve (unsigned n) {
    if (n > _capacity) {
        _capacity = n;
    }
}

void IntVector::expand() {
    if (_capacity == 0) {
        _capacity = 1;
        _data = new int[_capacity];
    }
    else {
        _capacity *= 2;
        int* temp = new int[_capacity];
        for (unsigned int i = 0; i < _size; ++i) {
            temp[i] = _data[i];
        }
        delete[] _data;
        _data = new int[_capacity];
        for (unsigned int i = 0; i < _size; ++i) {
            _data[i] = temp[i];
        }
        delete[] temp;
    }
}

void IntVector::expand(unsigned amount) {
    _capacity += amount;
    int* temp = new int[_capacity];
    for (unsigned int i = 0; i < _size; ++i) {
        temp[i] = _data[i];
    }
    delete[] _data;
    _data = new int[_capacity];
    for (unsigned int i = 0; i < _size; ++i) {
        _data[i] = temp[i];
    }
    delete[] temp;
}