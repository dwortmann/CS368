#include "Book.h"
#include <string>
#include <iostream>
using namespace std;
/*
 * Book class
 *
 * A Book object contains a book ID, publication year, and a rating.
 * 
 */
    Book::Book(){
    // Constructs a default book with an ID of 0, year 0, and 0.0 rating.
	bookID = 0;
	year = 0;
	rating = 0.0;
    }

    Book::Book(int ID){
    // Constructs a book with the given ID, 0 year, and 0.0 rating.
	bookID = ID;
	year = 0;
	rating = 0.0;
    }

    Book::Book(int ID, string title, int yr, double rating){
    // Constructs a book with the given ID, year , and rating.
	bookID = ID;
	this->title = title;
	year = yr;
	this->rating = rating;
    }

    // Accessors
    int Book::getID() const          // returns the book ID
    {return bookID;}

    string Book::getTitle() const    // returns the title
    {return title;}

    int Book::getYear() const        // returns the publication year
    {return year;}

    double Book::getRating() const   // returns the rating
    {return rating;}

    // Methods
    void Book::updateBook(int bookID, int yr, double rating)
    {
	this->bookID = bookID;
	year = yr;
	this->rating = rating;
    }

    void Book::print() const   // print out the book information 
    {                    // as ID title year rating 
	cout << bookID << " " << title << " " << year << " " << rating << endl;
    }

