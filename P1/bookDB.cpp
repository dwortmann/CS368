/*******************************************************************************
Author: Dan Wortmann
CS Login: dwortman
Course: CS 368, Fall l2014
Assignment: Programming Assignment 1
*******************************************************************************/
#include <iostream>

//*****************************************************************************
// Defines
//*****************************************************************************
using namespace std;

struct Book {
    int ID;
    int year;
    double rating;
};

int addBook(int bookID, int year, double rating);
int updateBook(int bookID, int year, double rating);
int deleteBook(int bookID);
void findBooks(int year);
void calculateAverageRating(void);
void print(void);
bool checkID(int id);
bool checkYear(int y);
bool checkRating(double r);
void expandDatabase(void);
bool findID(int id, int* found);

//*****************************************************************************
// Global Variables
//*****************************************************************************
volatile int DATABASE_SIZE = 1;
volatile int numBooks = 0;
volatile Book *database;

//*****************************************************************************
// External Functions
//*****************************************************************************


//*****************************************************************************
// MAIN
//*****************************************************************************
int main()
{
    bool done = false;

    //initialize all constants and variables here
    string choice; //the command
    int bookID, year, ret;
    double rating; //attributes
    char ch;
    bool error;

    database = new Book[DATABASE_SIZE]; //start database at 100 books

    cout << "Enter your commands at the > prompt:" << endl;

    while (!done)
    {
        error = false; //always reset to no error
        cout << "> ";
        cin >> ch;

        switch (ch)
        {
            //enter the command choices and their functions here
            case 'a':
                //Add a book to database
                cin >> bookID >> year >> rating;

                //check valid ID
                error = checkID(bookID);
                if(error)
                {
                    cout << "ERROR: Invalid bookID " << endl;
                    break;
                }

                //check valid year
                error = checkYear(year);
                if(error)
                {
                    cout << "ERROR: Invalid year " << endl;
                    break;
                }

                //check valid rating
                error = checkRating(rating);
                if(error)
                {
                    cout << "ERROR: Invalid rating " << endl;
                    break;
                }

                //add book to database
                ret = addBook(bookID, year, rating);

                if(ret == 0)
                {
                    //success
                    cout << "book " << bookID << " " << year << " " << rating << endl;
                }
                else
                {
                    cout << "ERROR: Book " << bookID << " already exists in database" << endl;
                }

                break;

            case 'd':
                //delete the book with ID
                cin >> bookID;

                //check valid ID
                error = checkID(bookID);
                if(error)
                {
                    cout << "ERROR: Invalid bookID " << endl;
                    break;
                }

                ret = deleteBook(bookID);

                if(ret == 0)
                {
                    //success
                    cout << "Book removed" << endl;
                }
                else
                {
                    cout << "ERROR: Book not found " << bookID << endl;
                }

                break;

            case 'u':
                //update book of give ID, with the year/rating
                cin >> bookID >> year >> rating;

                //check valid ID
                error = checkID(bookID);
                if(error)
                {
                    cout << "ERROR: Invalid bookID " << endl;
                    break;
                }

                //check valid year
                error = checkYear(year);
                if(error)
                {
                    cout << "ERROR: Invalid year " << endl;
                    break;
                }

                //check valid rating
                error = checkRating(rating);
                if(error)
                {
                    cout << "ERROR: Invalid rating " << endl;
                    break;
                }

                ret = updateBook(bookID, year, rating);

                if(ret == 0)
                {
                    //success
                    cout << "Successfully updated" << endl;
                }
                else
                {
                    cout << "ERROR: Book not found " << bookID << endl;
                }

                break;

            case 'c':
                // calculate and print average rating of all books
                calculateAverageRating();

                break;

            case 'f':
                //find and print all books in given year
                cin >> year;

                //check valid year
                error = checkYear(year);
                if(error)
                {
                    cout << "ERROR: Invalid year " << endl;
                    break;
                }

                findBooks(year);

                break;

            case 'p':
                //print all contents of database (ID, year, rating \n)
                print();

                break;

            case 'q':
                done = true;
                cout << "quit" << endl;
                break;

                // If the command is not one listed in the specification, for the purposes of this
                // assignment, we will ignore it.
            default: break;
        } // end switch

    } // end while

    return 0;
}

/****************************************************************************
* This functions adds a given book to the database given the bookID, year and
* rating. If the book is found already it is NOT added and returns -1.
*
* int bookID - ID of the book
* int year - year of the book
* double rating - rating of the book
*
* return 0 on success, -1 if book already found
****************************************************************************/
int addBook(int bookID, int year, double rating)
{
	Book current;
	int retID;

	//search if book already exists
	if(findID(bookID, &retID))
	{
		cout << retID << endl;
		return -1;
	}

	//otherwise add to database
	//current = database[numBooks];
	database[numBooks].ID = bookID;
	database[numBooks].year = year;
	database[numBooks].rating = rating;

	//increment number of books
	numBooks++;

	//increase size if needed
	if(numBooks == DATABASE_SIZE)
	{
		expandDatabase();
	}

    return 0;
}

/****************************************************************************
* Check if book with given ID already exists
*
* int bookID - ID of the book
* int* found - index of found ID
*
* return true if book exists, false if not
****************************************************************************/
bool findID(int id, int* found)
{
	int i;
	Book temp;

	//search for id in existing books
	for(i = 0; i < numBooks; i++)
	{
		if(database[i].ID == id)
		{
			*found = i;
			//cout << i << endl;
			return true;
		}
	}

	return false;
}

/****************************************************************************
* Update a books year and rating within the database. If book does not exist
* return -1;
*
* int bookID - ID of the book
* int year - year of the book
* double rating - rating of the book
*
* return 0 on success, -1 if book not found
****************************************************************************/
int updateBook(int bookID, int year, double rating)
{
	int retID;
	
	if(!findID(bookID, &retID))
	{
		//book not found
		return -1;
	}

	//cout << i << endl;

	//use returned ID to update contents - eliminates 2 searches
	database[retID].year = year;
	database[retID].rating = rating;

    return 0;
}

/****************************************************************************
* Delete a book with given ID from the database
*
* int bookID - ID of book
*
* return 0 on success, -1 if book does not exist with give ID
****************************************************************************/
int deleteBook(int bookID)
{
	int retID;
	int i;

	if(!findID(bookID, &retID))
	{
		//no such book
		return -1;
	}

	//remove book and shift remaining books to fill gap
	for(i = retID; i < (numBooks - 1); i++)
	{
		database[i].ID = database[i+1].ID;
		database[i].year = database[i+1].year;
		database[i].rating = database[i+1].rating;
	}

	//decrement number of books
	numBooks--;


    return 0;
}

/****************************************************************************
* Find all books in database with given year and print out to user. If no
* books are found return an error message.
*
* int year - year of books to find
****************************************************************************/
void findBooks(int year)
{
	int i;
	bool found;

	found = false; //see if one book exists

	//search database
	for(i = 0; i < numBooks; i++)
	{
		if(year == database[i].year)
		{
			found = true;
			cout << database[i].ID << ", " << database[i].year << ", " << database[i].rating << endl;
		}
	}

	if(!found)
		cout << "No books were found published in given year" << endl;
}

/****************************************************************************
* Calculate the average rating of all books contained in database, and print
* out to the user.
****************************************************************************/
void calculateAverageRating(void)
{
	int i;
	double sum;

	if(numBooks == 0)
		cout << 0.0 << endl;

	//add up all ratings and average
	for(i = 0; i < numBooks; i++)
	{
		sum += database[i].rating;
	}

	cout << "Average Rating: " << sum/numBooks << endl; //return
	
}

/****************************************************************************
* Print out the contents of database in specified format:
*
* "ID, year, rating\n"
****************************************************************************/
void print(void)
{
	int i;

	for(i = 0; i < numBooks; i++)
	{
		//print
		cout << database[i].ID << ", " << database[i].year << ", " << database[i].rating << endl;
	}
}

/****************************************************************************
* Check for a valid 5 digit ID, without 0 in the first digit.
*
* return true on error, false on valid
****************************************************************************/
bool checkID(int id)
{
	if(id < 10000 || id > 99999)
		return true;

    return false;
}

/****************************************************************************
* Check for valid year <= 2014
*
* return true on error, false on valid
****************************************************************************/
bool checkYear(int y)
{
	if(y < 0 || y > 2014)
		return true;

    return false;
}

/****************************************************************************
* Check for valid rating 0.00 <= rating <= 5.00
*
* return true on error, false on valid
****************************************************************************/
bool checkRating(double r)
{
	if(r < 0.00 || r > 5.00)
		return true;

    return false;
}

/****************************************************************************
* Expand current database to accommodate more books. Double size each time.
****************************************************************************/
void expandDatabase(void)
{
	int i;
	Book* temp;

	DATABASE_SIZE *= 2; //double size

	temp = new Book[DATABASE_SIZE];

	for(i = 0; i < numBooks; i++)
	{
		//copy over contents to larger array - could implement shadow array...
		temp[i].ID = database[i].ID;
		temp[i].year = database[i].year;
		temp[i].rating = database[i].rating;		
	}

	//free up old space
	delete database;

	//reassign to larger database
	database = temp;

}

