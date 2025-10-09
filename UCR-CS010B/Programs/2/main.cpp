#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Date {
 private:
   unsigned day;
   unsigned month;
   string monthName;
   unsigned year;

 public:
   // creates the date January 1st, 2000.
   Date ();


   /* parameterized constructor: month number, day, year 
       - e.g. (3, 1, 2010) will construct the date March 1st, 2010

       If any of the arguments are invalid (e.g. 15 for month or 32 for day)
       then the constructor will construct instead a valid Date as close
       as possible to the arguments provided - e.g. in above example,
       Date(15, 32, 2010), the Date would be corrected to Dec 31st, 2010.
       In case of such invalid input, the constructor will issue a console error message: 

       Invalid date values: Date corrected to 12/31/2010.
       (with a newline at the end).
   */
   Date (unsigned m, unsigned d, unsigned y);


   /* parameterized constructor: month name, day, year
      - e.g. (December, 15, 2012) will construct the date December 15th, 2012

       If the constructor is unable to recognize the string argument as a valid month name,
       then it will issue a console error message: 

       Invalid month name: the Date was set to 1/1/2000.
       (with a newline at the end).
 
       If the day argument is invalid for the given month (but the month name was valid),
       then the constructor will handle this error in the same manner as the other
       parameterized constructor. 

       This constructor will recognize both "december" and "December"
       as month name.
   */
   Date (const string &mn, unsigned d, unsigned y);


   /* Outputs to the console (cout) a Date exactly in the format "3/15/2012". 
      Does not output a newline at the end.
   */
   void printNumeric () const;


   /* Outputs to the console (cout) a Date exactly in the format "March 15, 2012".
      The first letter of the month name is upper case, and the month name is
      printed in full - January, not Jan, jan, or january. 
      Does not output a newline at the end.
   */
   void printAlpha () const;

 private:

   /* Returns true if the year passed in is a leap year, otherwise returns false.
   */
   bool isLeap (unsigned y) const;


   /* Returns number of days allowed in a given month
      -  e.g. daysPerMonth(9, 2000) returns 30.
      Calculates February's days for leap and non-leap years,
      thus, the reason year is also a parameter.
   */
   unsigned daysPerMonth (unsigned m, unsigned y) const;

   /* Returns the name of a given month
      - e.g. name(12) returns the string "December"
   */
   string name (unsigned m) const;

   /* Returns the number of a given named month
      - e.g. number("March") returns 3
   */
   unsigned number (const string &mn) const;
};

bool Date::isLeap (unsigned y) const {
   bool result = false;

   if (y % 4 == 0) {
      result = true;
      if (y % 100 == 0) {
         result = false;
         if (y % 400 == 0) {
            result = true;
         }
      }
   }

   return result;
}

unsigned Date::daysPerMonth (unsigned m, unsigned y) const {
   unsigned result;

   if (m == 2) {
      result = 28;
      if (isLeap (y)) {
         result = 29;
      }
   }

   if (m == 4 || m == 6 || m == 9 || m == 11) {
      result = 30;
   }

   if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
      result = 31;
   }

   return result;
}

string Date::name (unsigned m) const {
   string result;
   
   if (m == 1) {
      result = "January";
   }
   if (m == 2) {
      result = "February";
   }
   if (m == 3) {
      result = "March";
   }
   if (m == 4) {
      result = "April";
   }
   if (m == 5) {
      result = "May";
   }
   if (m == 6) {
      result = "June";
   }
   if (m == 7) {
      result = "July";
   }
   if (m == 8) {
      result = "August";
   }
   if (m == 9) {
      result = "September";
   }
   if (m == 10) {
      result = "October";
   }   
   if (m == 11) {
      result = "November";
   }
   if (m == 12) {
      result = "December";
   }

   return result;
}

unsigned Date::number (const string &mn) const {
   unsigned result = 0;
   string upper;

   for (unsigned int i = 0; i < mn.size(); ++i) {
      upper += toupper(mn.at(i));
   }

   if (upper == "JANUARY") {
      result = 1;
   }
   if (upper == "FEBRUARY") {
      result = 2;
   }
   if (upper == "MARCH") {
      result = 3;
   }
   if (upper == "APRIL") {
      result = 4;
   }
   if (upper == "MAY") {
      result = 5;
   }
   if (upper == "JUNE") {
      result = 6;
   }
   if (upper == "JULY") {
      result = 7;
   }
   if (upper == "AUGUST") {
      result = 8;
   }
   if (upper == "SEPTEMBER") {
      result = 9;
   }
   if (upper == "OCTOBER") {
      result = 10;
   }
   if (upper == "NOVEMBER") {
      result = 11;
   }
   if (upper == "DECEMBER") {
      result = 12;
   }

   return result;
}

Date::Date () {
   day = 1;
   month = 1;
   monthName = "January";
   year = 2000;
}

Date::Date (unsigned m, unsigned d, unsigned y) {
   bool error = false;

   if (m > 12 || m < 1) {
      while (m > 12) {
         m -=1;
      }
      if (m < 1) {
         m = 1;
      }

      error = true;
   }

   if (d > daysPerMonth(m, y) || d < 1) {
      while (d > daysPerMonth(m, y)) {
         d -= 1;
      }
      if (d < 1) {
         d = 1;
      }

      error = true;
   }

   day = d;
   month = m;
   monthName = name (m);
   year = y;

   if (error == true) {
      cout << "Invalid date values: Date corrected to " << m << '/' << d << '/' << y << '.' << endl;
   }
}

Date::Date (const string &mn, unsigned d, unsigned y) {
   unsigned m = number (mn);

   bool error1 = false;
   bool error2 = false;

   if (m == 0) {
      error1 = true;
   }

   if (d > daysPerMonth(m, y) || d < 1) {
      while (d > daysPerMonth(m, y)) {
         d -= 1;
      }
      if (d < 1) {
         d = 1;
      }

      error2 = true;
   }

   day = d;
   month = m;
   monthName = mn;
   year = y;

   if (error1 == true) {
      day = 1;
      month = 1;
      monthName = "January";
      year = 2000;
      cout << "Invalid month name: the Date was set to 1/1/2000." << endl;
   }
   else if (error2 == true) {
      cout << "Invalid date values: Date corrected to " << m << '/' << d << '/' << y << '.' << endl;
   }
}

void Date::printNumeric () const {
   cout << month << '/' << day << '/' << year;
}

void Date::printAlpha () const {
   string mn = monthName;
   mn.at(0) = toupper(mn.at(0));
   cout << mn << ' ' << day << ", " << year;
}


// Don't change the code below this line.
// You may comment them out if you want to build your own test harness
// while in develope mode, but you will need these to pass tets in submit mode.

Date getDate();

int main() {
   
   Date testDate;
   testDate = getDate();
   cout << endl;
   cout << "Numeric: ";
   testDate.printNumeric();
   cout << endl;
   cout << "Alpha:   ";
   testDate.printAlpha();
   cout << endl;
   
   return 0;
}

Date getDate() {
   int choice;
   unsigned monthNumber, day, year;
   string monthName;

   cout << "Which Date constructor? (Enter 1, 2, or 3)" << endl
      << "1 - Month Number" << endl
      << "2 - Month Name" << endl
      << "3 - default" << endl;
   cin >> choice;
   cout << endl;

   if (choice == 1) {
      cout << "month number? ";
      cin >> monthNumber;
      cout << endl;
      cout << "day? ";
      cin >> day;
      cout << endl;
      cout << "year? ";
      cin >> year;
      cout << endl;
      return Date(monthNumber, day, year);
   } else if (choice == 2) {
      cout << "month name? ";
      cin >> monthName;
      cout << endl;
      cout << "day? ";
      cin >> day;
      cout << endl;
      cout << "year? ";
      cin >> year;
      cout << endl;
      return Date(monthName, day, year);
   } else {
      return Date();
   }
}
