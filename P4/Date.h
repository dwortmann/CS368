#ifndef DATE_H
#define DATE_H

#include <iostream>
using namespace std;

class Date {

  public:

    // constructors
      Date();

      Date(int month, int day, int year);

      ~Date(); // destructor

      Date(const Date& dt); //copy constructor
    
    // Member functions ( = cout) is default paramter ONLY in .h
      void print(ostream& out = cout) const;

      int getDay() const;

      int getMonth() const;

      int getYear() const;

      void set(const int m, const int d, const int y);

      bool setDate(int m, int d, int y);

      bool checkValidDate(int m, int d, int y);

// Relational operators
friend bool operator!=(const Date& date1, const Date& date2);
       
friend bool operator <(const Date& date1, const Date& date2);

friend bool operator<=(const Date& date1, const Date& date2);

friend bool operator >(const Date& date1, const Date& date2);

friend bool operator>=(const Date& date1, const Date& date2);

// Arithmetic operators
friend Date operator+(const Date& dt, const int n);

friend Date operator-(const Date& dt, const int n);

// I/O operators
friend ostream& operator<< (ostream& out, const Date& dt);

friend istream& operator>> (istream& in, Date& dt);



   // Assignment operators
   const Date& operator=(const Date& dt);

  private:
    int day;      
    int month; 
    int year;
};

#endif
