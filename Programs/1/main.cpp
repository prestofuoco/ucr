#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void readData (const string &inputFile, vector<double> &angle, vector<double> &coefficient) {
    double num;
    ifstream inFS;
    
    inFS.open(inputFile);
    if (!inFS.is_open()) {
        cout << "Error opening " << inputFile << endl;
        exit(EXIT_FAILURE); 
    }

    while (inFS >> num) {
        angle.push_back(num);
        inFS >> num;
        coefficient.push_back(num);
    }

    inFS.close();
}

double interpolation (double input, const vector<double> &angle, const vector<double> &coefficient) {
    double result;
    unsigned int i;
    double less = 0;
    double more;

    if (input < angle.at(0) || input > angle.back()) {
        return -1; 
    }
    
    if (input == angle.at(0) || input == angle.back()) {
        if (input == angle.at(0)) {
            return coefficient.at(0);
        }
        if (input == angle.back()) {
            return coefficient.back();
        }
    }

    else {
        for (i = 0; i < angle.size() - 1; ++i) {
            if (angle.at(i) < input && angle.at(i + 1) > input) {
                less = i;
                more = i + 1;
            }

            else if (input == angle.at(i) || input == angle.back()) {
                return coefficient.at(i);
            }
        }

        result = coefficient.at(less) + ((input - angle.at(less)) / (angle.at(more) - angle.at(less))) * (coefficient.at(more) - coefficient.at(less));

        return result;
    }

    exit(EXIT_FAILURE);
}

bool isOrdered (const vector<double> &angle) {
    unsigned int i;

    for (i = 1; i < angle.size(); ++i) {
        if (angle.at(i) < angle.at(i-1)) {
            return false;
        }
    }

    return true;
}

void reorder (vector<double> &angle, vector<double> &coefficient) {
    unsigned int i;
    unsigned int j;
    double temp;

    for (i = 0; i < angle.size(); ++i) {
        for (j = i + 1; j < angle.size(); ++j) {
            if (angle.at(j) < angle.at(i)) {
                temp = angle.at(j);
                angle.at(j) = angle.at(i);
                angle.at(i) = temp;

                temp = coefficient.at(j);
                coefficient.at(j) = coefficient.at(i);
                coefficient.at(i) = temp;
            }
        }
    }
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    string inputFile = argv[1];
    vector<double> angle;
    vector<double> coefficient;

    readData (inputFile, angle, coefficient);
    double user;
    string option = "Yes";
    
    while (option != "No" && option == "Yes") {
        cout << "Input flight-path angle:" << endl;
        cin >> user;

        if (!isOrdered (angle)) {
            reorder (angle, coefficient);
        }

        if (user == angle.at(0) || user == angle.back()) {
            if (user == angle.at(0)) {
                cout << coefficient.at(0) << endl;
            }
            if (user == angle.back()) {
                cout << coefficient.back() << endl;
            }
        }
        
        if (user > angle.at(0) && user < angle.back()) {
            cout << interpolation (user, angle, coefficient) << endl;
        }

        else {
            cout << "Invalid input" << endl;
        }
        
        cout << "Would you like to enter another flight-path angle?" << endl;
        cin >> option;
    }

    return 0;
}