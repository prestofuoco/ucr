#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

//  - Passes in an array along with the size of the array.
//  - Returns the mean of all values stored in the array.
double mean(const double array[], int arraySize) {
   double sum = 0;
   for (int i = 0; i < arraySize; ++i) {
      sum += array[i];
   }
   return sum / arraySize;
}

//  - Passes in an array, the size of the array by reference, and the index of a value to be removed from the array.
//  - Removes the value at this index by shifting all of the values after this value up, keeping the same relative order of all values not removed.
//  - Reduces arraySize by 1.
void remove(double array[], int &arraySize, int index) {
   if (index >= 0 && index < arraySize) {
      for (int i = index; i < arraySize - 1; ++i) {
         array[i] = array[i + 1];
      }
      --arraySize;
   }
}


// - Passes in an array and the size of the array.
// - Outputs each value in the array separated by a comma and space, with no comma, space or newline at the end.
void display(const double array[], int arraySize) {
   for (int i = 0; i < arraySize; ++i) {
      cout << array[i];
      if (i < arraySize - 1) {
         cout << ", ";
      }
   }
}


const int ARR_CAP = 100;

int main(int argc, char *argv[]) {
   // verify file name provided on command line
   if (argc != 2) {
      return 1;
   }
   
   string inputFile = argv[1];
   
   // open file and verify it opened   
   ifstream inFS;
   inFS.open(inputFile);
   if (!inFS.is_open()) {
      cout << "Error opening " << inputFile << endl;
      exit(EXIT_FAILURE); 
   }

   // Declare an array of doubles of size ARR_CAP.
   double arr1[ARR_CAP];
    
   // Fill the array with up to ARR_CAP doubles from the file entered at the command line.
   int i = 0;
   while (inFS >> arr1[i] && i < ARR_CAP) {
      ++i;
   }

   // Call the mean function passing it this array and output the 
   // value returned.
   cout << "Mean: " << mean(arr1, i) << endl;

   // Ask the user for the index (0 to size - 1) of the value they want to remove.
   int index;
   cout << "Enter index of value to be removed (0 to " <<  i - 1 << "): ";
   cin >> index;
	
   // Call the display function to output the array.
   cout << endl << "Before removing value: ";
   display(arr1, i);

   // Call the remove function to remove the value at the index
   // provided by the user.
   remove(arr1, i, index);

   // Call the display function again to output the array
   // with the value removed.
   cout << endl << "After removing value: ";
   display(arr1, i);

   // Call the mean function again to get the new mean
   cout << endl << "Mean: " << mean(arr1, i) << endl;
   
	return 0;
}