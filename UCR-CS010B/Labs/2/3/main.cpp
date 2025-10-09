#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
   
   string inputFile;
   string outputFile;
   int num;
   int sum = 0;
   char c;
   vector<int> v;

   if (argc != 3) {
      return 1;
   }

   inputFile = argv[1];
   outputFile = argv[2];

   ifstream inFS;

   inFS.open(inputFile);
   if (!inFS.is_open()) {
      cout << "Error opening " << inputFile << endl;
      exit(EXIT_FAILURE); 
   }
   while (inFS >> num) {
      v.push_back(num);
      inFS >> c;
   }
   inFS.close();

   for (unsigned int i = 0; i < v.size(); ++i) {
      sum += v.at(i);
   }

   int avg = sum/v.size();

   for (unsigned int i = 0; i < v.size(); ++i) {
      v.at(i) = v.at(i) - avg;
   }

   ofstream outFS;

   outFS.open(outputFile);
   if (!outFS.is_open()) {
      cout << "Error opening " << outputFile << endl;
      exit(EXIT_FAILURE); 
   }
   for (unsigned int i = 0; i < v.size(); ++i) {
      outFS << v.at(i);
      if (i != v.size() - 1) {
         outFS << ',';
      }
   }
   outFS.close();
   
   return 0;
}