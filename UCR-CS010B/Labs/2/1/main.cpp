#include <fstream>
#include <iostream>
#include <cstdlib> //needed for exit function

using namespace std;

int fileSum (const string& filename);

int main() {

   string filename;
   int sum = 0;
   
   cout << "Enter the name of the input file: ";
   cin >> filename;
   cout << endl;
   
   sum = fileSum(filename);

   cout << "Sum: " << sum << endl;
   
   return 0;
}

int fileSum (const string& filename) {
   int sum = 0;
   int temp;
   ifstream inFS;

   inFS.open(filename);
   if (!inFS.is_open()) {
      cout << "Error opening " << filename << endl;
      exit(EXIT_FAILURE); 
   }

   while (inFS >> temp) {
      sum += temp;
   }

   inFS.close();
   return sum;
}