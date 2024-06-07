#include <iostream>
#include <cmath>
using namespace std;

#include "Distance.h"

Distance::Distance() {
    _feet = 0;
    _inches = 0.0;
}

Distance::Distance(unsigned ft, double in) {
    _feet = ft;
    _inches = in;
    init();
}

Distance::Distance(double in) {
    _feet = 0;
    _inches = in;
    init();
}

unsigned Distance::getFeet() const {
    return _feet;
}

double Distance::getInches() const {
    return _inches;
}

double Distance::distanceInInches() const {
    double result = _inches + _feet * 12.0;
    return result;
}

double Distance::distanceInFeet() const {
    double result = _feet + _inches / 12.0;
    return result;
}

double Distance::distanceInMeters() const {
    double result = (_feet * 12 + _inches) * 0.0254;
    return result;
}

Distance Distance::operator+(const Distance &rhs) const {
    Distance result;
    double tempInches;
    int tempFeet = 0;
    tempInches = (_inches + rhs._inches);
    while (tempInches >= 12) {
        tempInches -= 12;
        ++tempFeet;
    }
    result._inches = tempInches;
    result._feet = _feet + rhs._feet + tempFeet;
    return result;
}

Distance Distance::operator-(const Distance &rhs) const {
    Distance result;
    if (_feet > rhs._feet) {
        result._feet = _feet - rhs._feet;
        result._inches = _inches - rhs._inches;
    }
    else if (_feet < rhs._feet) {
        result._feet = rhs._feet - _feet;
        result._inches = rhs._inches - _inches;
    }
    else if (_feet == rhs._feet) {
        result._feet = _feet - rhs._feet;
        if (_inches >= rhs._inches) {
            result._inches = _inches - rhs._inches;
        }
        else if (_inches < rhs._inches) {
            result._inches = rhs._inches - _inches;
        }
    }
    while (result._inches >= 12) {
        result._inches -= 12;
        ++result._feet;
    }
    while (result._inches < 0) {
        result._inches += 12;
        --result._feet;
    }
    return result;
}

ostream& operator<<(ostream &out, const Distance &rhs) {
    out << rhs._feet << "\' " << rhs._inches << "\"";
    return out;
}

void Distance::init() { 
    _inches = fabs(_inches);
    _feet = fabs(_feet);
    while (_inches >= 12) {
        ++_feet;
        _inches -= 12;
    }
}