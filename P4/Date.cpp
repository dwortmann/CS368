#include "Date.h"
#include <iostream>

using namespace std;

/*
 * Date class
 *
 * The Date class is used to represent dates and to define operations on
 * dates.
 *
 */

    // constructors
      Date::Date()
      {
        //cout << "default " << endl;
        // Because pie day is the best day //
	day = 14;
	month = 3;
	year = 1592;//illegal but funny
      }

      Date::Date(int month, int day, int year)
      {
      	//cout << "contructor called" << endl;
	if(checkValidDate(month,day,year))
	{
	this->day = day;
	this->month = month;
	this->year = year;
	}
      }

      Date::Date(const Date& dt)
      {
        //cout << "copy constructor" << endl;
	// copy operator //
	day = dt.day;
	month = dt.month;
	year = dt.year;
      }

      Date::~Date()
      {
	// destructor //
      }
    
    // Member functions
      void Date::print(ostream& out) const
      {
        //cout << "print called" << endl;
	out << this->month << "/" << this->day << "/" << this->year << endl;
	return;
      }

      int Date::getDay() const
      {
        //cout << "getDay" << endl;
	return day;
      }

      int Date::getMonth() const
      {
      	//cout << "getMonth" << endl;
	return month;
      }

      int Date::getYear() const
      {
      	//cout << "getYear" << endl;
	return year;
      }

      // Check if we have a valid date //
      bool Date::checkValidDate(int m, int d, int y)
      {
        //cout << "checking valid Date:" << endl;
        bool leap = false;
	// check leap years, day, month, year bounds etc. //
	// ex. February can't have more than 30 days...
	if(m < 1 || d < 1 || y < 1 || y < 1900)
		return false;

	// check 31 day months: Jan, March, May, July, Aug, Oct, Dec
	if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
	{
         	if(d > 31)
		    return false;
	}
	
	// check 30 day months: April, June, Sept, Nov
	else if(m == 4 || m == 6 || m == 9 || m == 11)
	{
         	if(d > 30)
		    return false;
	}
	
	// check February (28) and leap years (29)
	// 2016 is a leap year so ((2016 - year) % 4) == 0 gives leap year
	else if(m == 2)
	{
		// determine leap year //
		leap = ( ((2016 - y) % 4) == 0 );

		if(leap && d > 29)
		  return false;
		else if(d > 28)
		  return false;
	}
	else
	   return false; //not a valid month
	
	// date checks out, so lets put it in the system //
	
	return true;
      }

      void Date::set(const int m,const int d, const int y)
      {
	month = m;
	day = d;
	year = y;
      }

      bool Date::setDate(int m, int d, int y)
      {
        //cout << "setting date" << endl;
        // Check basic dates //
	if(!checkValidDate(m,d,y))
	{
		cerr << "Invalid date entered ( 1/1/1900 and later are valid dates )" << endl;
		return false;
	}
	
	set(m,d,y);

	return true;
      }

   // Assignment operators ----------------------------------------------

      const Date& Date::operator=(const Date& dt)
      {
	// assignment //
	this->setDate( dt.getMonth(), dt.getDay(), dt.getYear() );
      }

   // Relational operators ----------------------------------------------

      bool operator!=(const Date& date1, const Date& date2)
      {
	// not equal //
	if(date1.getMonth() != date2.getMonth())
	  return true;

	if(date1.getDay() != date2.getDay())
	  return true;

	if(date1.getYear() != date2.getYear())
	  return true;

	return false;
      }
       
      bool operator <(const Date& date1, const Date& date2)
      {
	// Less than //
	if( date1.getYear() >= date2.getYear() 
	 && date1.getMonth() >= date2.getMonth() 
	 && date1.getDay() >= date2.getDay() )
	    return false;

	return true;
	
      }

      bool operator<=(const Date& date1, const Date& date2)
      {
	// Less that or equal //
	if( date1.getYear() > date2.getYear() 
	 && date1.getMonth() > date2.getMonth() 
	 && date1.getDay() > date2.getDay() )
	    return false;

      }

      bool operator >(const Date& date1, const Date& date2)
      {
	// Greater than //
	if( date1.getYear() <= date2.getYear() 
	 && date1.getMonth() <= date2.getMonth() 
	 && date1.getDay() <= date2.getDay() )
	    return false;

      }

      bool operator>=(const Date& date1, const Date& date2)
      {
	// Greater than or equal //
	if( date1.getYear() < date2.getYear() 
	 && date1.getMonth() < date2.getMonth() 
	 && date1.getDay() < date2.getDay() )
	    return false;

      }


// Arithmetic operators //
// We should also have the enumeration of order for the operators in case we do
// Date + literal  and literal + date... I didn't do it in this case for sake of 
// time.
Date operator+(const Date& dt, const int n)
{
  // add days to date //
  int m, d, y;
  int days = n;
  bool leap = false;

  m = dt.getMonth();
  d = dt.getDay();
  y = dt.getYear();

  while(days > 0)
  {
    switch(m){
	case(1):
		if(d == 31)
		{
		  d = 1;
		  m = 2;
		}
		else
		  d++;
	break;
	case(2):
		leap = ( ((2016 - y) % 4) == 0 );

		if(leap && d == 29)
		{
		  d = 1;
		  m = 3;
		}
		else if(d == 28)
		{
		  d = 1;
		  m = 3;
		}
		else
		  d++;
	break;

	case(3):
		if(d == 31)
		{
		  d = 1;
		  m = 4;
		}
		else
		  d++;
	break;

	case(4):
		if(d == 30)
		{
		  d = 1;
		  m = 5;
		}
		else
		  d++;
	break;

	case(5):
		if(d == 31)
		{
		  d = 1;
		  m = 6;
		}
		else
		  d++;
	break;

	case(6):
		if(d == 30)
		{
		  d = 1;
		  m = 7;
		}
		else
		  d++;
	break;

	case(7):
		if(d == 31)
		{
		  d = 1;
		  m = 8;
		}
		else
		  d++;
	break;

	case(8):
		if(d == 31)
		{
		  d = 1;
		  m = 9;
		}
		else
		  d++;
	break;

	case(9):
		if(d == 30)
		{
		  d = 1;
		  m = 10;
		}
		else
		  d++;
	break;

	case(10):
		if(d == 31)
		{
		  d = 1;
		  m = 11;
		}
		else
		  d++;
	break;

	case(11):
		if(d == 30)
		{
		  d = 1;
		  m = 12;
		}
		else
		  d++;
	break;

	case(12):
		if(d == 31)
		{
		  d = 1;
		  m = 1;
		  y = y + 1;
		}
		else
		  d++;
	break;

	default: days = 0;
    }

    days--;
  }

  // set new date //
  return Date(m,d,y);

}

Date operator-(const Date& dt, const int n)
{
  // sub days from date //
  int m, d, y;
  int days = n;
  bool leap = false;

  m = dt.getMonth();
  d = dt.getDay();
  y = dt.getYear();

  cout << m << "/" << d << "/" << y << endl;

  while(days > 0)
  {
    switch(m){
	case(1):
		if(d == 1)
		{
		  d = 31;
		  m = 12;
		  y = y - 1;
		}
		else
		  d--;
	break;
	case(2):
		leap = ( ((2016 - y) % 4) == 0 );

		if(leap && d == 29)
		{
		  d = 31;
		  m = 1;
		}
		else if(d == 28)
		{
		  d = 31;
		  m = 1;
		}
		else
		  d--;
	break;

	case(3):
		leap = ( ((2016 - y) % 4) == 0 );

		if(leap && d == 1)
		{
		  d = 29;
		  m = 2;
		}
		else if(d == 1)
		{
		  d = 28;
		  m = 2;
		}
		else
		  d--;
	break;

	case(4):
		if(d == 1)
		{
		  d = 31;
		  m = 3;
		}
		else
		  d--;
	break;

	case(5):
		if(d == 1)
		{
		  d = 30;
		  m = 4;
		}
		else
		  d--;
	break;

	case(6):
		if(d == 1)
		{
		  d = 31;
		  m = 5;
		}
		else
		  d--;
	break;

	case(7):
		if(d == 1)
		{
		  d = 30;
		  m = 6;
		}
		else
		  d--;
	break;

	case(8):
		if(d == 1)
		{
		  d = 31;
		  m = 7;
		}
		else
		  d--;
	break;

	case(9):
		if(d == 1)
		{
		  d = 31;
		  m = 8;
		}
		else
		  d--;
	break;

	case(10):
		if(d == 1)
		{
		  d = 30;
		  m = 9;
		}
		else
		  d--;
	break;

	case(11):
		if(d == 1)
		{
		  d = 31;
		  m = 10;
		}
		else
		  d--;
	break;

	case(12):
		if(d == 1)
		{
		  d = 30;
		  m = 11;
		}
		else
		  d--;
	break;

	default: days = 0;
    }

    days--;
  }

  // set new date //
  return Date(m,d,y);

}

// I/O operators
ostream& operator<< (ostream& out, const Date& dt)
{
  // output stream //
  out << dt.month << "/" << dt.day << "/" << dt.year;

  return out;
  
}

istream& operator>> (istream& in, Date& dt)
{
  // input stream //
  char ch, ch_next;
  int d, m, y, temp;

  ch_next = in.peek(); //get character from input stream

  while(ch_next == ' ' || ch_next == '\t' || ch_next == '\n' || ch_next == '/'
        || ch_next == '-')
  {
     ch = in.get();
     ch_next = in.peek();
  }
  // while( isspace(ch) ) { ch = in.get()  } //same thing

  in >> m; //month

  ch_next = in.peek(); //get character from input stream

  while(ch_next == ' ' || ch_next == '\t' || ch_next == '\n' || ch_next == '/'
        || ch_next == '-')
  {
     ch = in.get();
     ch_next = in.peek();
  }
  // while( isspace(ch) ) { ch = in.get()  } //same thing

  in >> d; //day

  ch_next = in.peek();

  while(ch_next == ' ' || ch_next == '\t' || ch_next == '\n' || ch_next == '/'
        || ch_next == '-')
  {
     ch = in.get();
     ch_next = in.peek();
  }
  // while( isspace(ch) ) { ch = in.get()  } //same thing

  in >> y; //year

  if(!dt.checkValidDate(m,d,y)){
	cerr << "The date is invalid in istream" << endl;
	return in;
  }

  dt.month = m;
  dt.year = y;
  dt.day = d;

  return in;
}

