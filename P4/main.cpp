#include <iostream>
#include "Date.h"

using namespace std;

int main() 
{
    // Start of main //
    Date d1, d2, d3;
    cout << "enter a date after 1/1/1900 " << endl;
    cin >> d1;
    cout << "entered: " << d1 << endl;

    cout << "enter another date after 1/1/1900 " << endl;
    cin >> d2;
    cout << "entered: " << d2 << endl;

    cout << "enter a third date after 1/1/1900 " << endl;
    cin >> d3;
    cout << "entered: " << d3 << endl;	

    cout << "\nthe earliest date entered is: " << endl;

    if( d1 < d2 && d1 < d3)
    	cout << d1;
    else if(d2 < d1 && d2 < d3)
        cout << d2;
    else if(d3 < d1 && d3 < d2)
        cout << d3;
   
    cout << "\n\nare any of the dates identical?" << endl;

    if(d1 != d2 && d2 != d3)
    	cout << "no, they are all unique" << endl;
	else
	cout << "yes, so they are the same" << endl;

    cout << "\nhow about now?" << endl;
    d3 = d2;

    if(d1 != d2 && d2 != d3)
    	cout << "no, they are all unique still" << endl;
	else
	cout << "yes, some are the same now" << endl;

    cout << "\nLets add some days, maybe subtract some" << endl;

    cout << "\n100 days after " << d1 << " is:" << d1 + 100 << endl;
    cout << "31 days after " << d1 << " is:" << d1 + 31 << endl;
    cout << "30 days after " << d1 << " is:" << d1 + 30 << endl;
    cout << "10000 days after " << d1 << " is:" << d1 + 10000 << endl;

    cout << "\n100 days before " << d2 << " is:" << d2 - 100 << endl;
    cout << "30 days before " << d2 << " is:" << d2 - 30 << endl;
    cout << "31 days before " << d2 << " is:" << d2 - 31 << endl;
    cout << "10000 days before " << d2 << " is:" << d2 - 10000 << endl;


		
    return 0;
}

