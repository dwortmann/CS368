#include "SortedList.h"
#include "Book.h"
#include <iostream>

/*
 * SortedList class
 *
 * A SortedList is an ordered collection of Books. The Books are ordered
 * from lowest numbered book ID to highest numbered  book ID.
 */
    
    SortedList::SortedList(){
    // Constructor for the class to initialize the list.
    	head = tail = NULL; //no list yet
    }

    bool SortedList::addBook(Book *b){
    // If a book with the same ID is not already in the list, inserts 
    // the given book into the list in the appropriate place and returns
    // true.  If there is already a book in the list with the same ID
    // then the list is not changed and false is returned.
        Listnode* currNode;
	Listnode* prevNode;
	Listnode* nextNode;
	int newID, compareID, currID;

	newID = (*b).getID();

	//cout << "ID being added: " << newID << endl;

	// Add node with given book //
	if(head == NULL)
	{
	    cout << "FIRST node" << endl;
	    // first node //
	    head = new Listnode;
	    head->book = b;
	    head->next = NULL;

	    tail = head;

	    return true;
	}
	else
	{
	   compareID = (*(head->book)).getID();
	   //cout << "head ID: " << compareID << endl;
 	   // compare to head first
	   if(compareID == newID)
	   {
	   	//cout << "ID found" << endl;

		return false;
	   }
	   else if(compareID > newID)
	   {
		//new head 
		currNode = new Listnode;
		currNode->next = head;
		currNode->book = b;

		head = currNode;//assign head

		//cout << "New ID added @head" << endl;


		return true;
	   }
	  
	   // only one node //
	   if(head->next == NULL)
	   {
		nextNode = new Listnode;
		nextNode->next = NULL;
		nextNode->book = b;
		head->next = nextNode;
		tail = nextNode;

		//cout << "New ID added after head" << endl;


		return true;
	   }

	   currNode = head;
	   nextNode = head->next;
	   //otherwise traverse list looking for ID
	   while(nextNode != NULL)
	   {
	   	currID = (*(currNode->book)).getID();
		compareID = (*(nextNode->book)).getID();

		//cout << "added ID: " << newID << "currID: " << currID << "nextID: " << compareID << endl;

		if(currID == newID)
		{
			//cout << "ID found" << endl;

		    return false;
		}
		else if(compareID > newID)
		{
		    //add between curr/next nodes
		    prevNode = new Listnode;
		    prevNode->next = nextNode;
		    prevNode->book = b;
		    currNode->next = prevNode;

		    //cout << "New ID added" << endl;


		    return true;
		}

		currNode = nextNode;
		nextNode = currNode->next;
	   }

	   // we reached end of the list
	   if( (*(currNode->book)).getID() == newID)
	   {
	   	//cout << "ID found" << endl;
	       return false;
	   }
	   else
	   {
	   	//cout << "New ID added" << endl;
		prevNode = new Listnode;
		prevNode->next = NULL;
		prevNode->book = b;
		currNode->next = prevNode;
		tail = prevNode; //update tail

		return true;
	   }

	   

	}
    }

    Book* SortedList::search(int bookID){
    // Searches the list for a book with the given book ID.  If the
    // book is found, it is returned; if it is not found, NULL is returned.
    	Listnode* curr;
	Listnode* next;
	int currID;

	if(head == NULL)
		return NULL;

	curr = head;

	//cout<<"Searching for: " << bookID << endl;

	while(curr != NULL)
	{
	   currID = (*(curr->book)).getID();

	   //cout<<"Current: " << currID << endl;

	   if(currID == bookID)
	   	return curr->book;
	
	   curr = curr->next;
	}

	return NULL;
    }
    
    bool SortedList::printBooksByYear(int year){
    // Searches the list for a book for a given year.  If a
    // book is found, it is printed; if it is not found, false is returned. 
	bool atLeastOneFound = false;
	int currYear;
	Listnode* curr;

	if(head == NULL)
	 return false;

	curr = head;

	//cout << "Looking for year: " << year << endl;

	while(curr != NULL)
	{
	   currYear = (*(curr->book)).getYear();

	   //cout << "curr year: " << currYear << endl;

	   if(currYear == year)
	   {
		atLeastOneFound = true;
		(*(curr->book)).print();
	   }

	   curr = curr->next;
	}

	return atLeastOneFound;
    }

    bool SortedList::updateBook(int ID, int year, double rating){
    //Updates a book, returns true if bookID to be updated is found, false otherwise
    	Listnode* curr;
	int currID;

	if(head == NULL)
	   return false;

	curr = head;

	//cout << "Looking for ID: " << ID << endl;

	while(curr != NULL)
	{
	    currID = (*(curr->book)).getID();

	    //cout << "curr ID: " << currID << endl;

	    if(currID == ID)
	    {
		(*(curr->book)).updateBook(ID, year, rating);
		return true;
	    }

	    curr = curr->next;
	}

	return false;
    }


    double SortedList::calculateAverageRating(){
    //Calculates average rating for all the books in the list
    	double numBooks = 0;
	double cumRating = 0;
	Listnode* curr;

	if(head == NULL)
	   return 0.0;

	curr = head;

	while(curr != NULL)
	{
	    cumRating += (*(curr->book)).getRating();
	    numBooks++;

	    curr = curr->next;
	}

	//cout << "cumalative rating: " << cumRating << " numBooks " << numBooks;

	return cumRating/numBooks;
    }

    Book* SortedList::removeBook(int bookID){
    // Searches the list for a book with the given bookID.  If the 
    // book is found, the book is removed from the list and returned;
    // if no book is found with the given ID, NULL is returned.
    // Note that the Book itself is NOT deleted - it is returned - however,
    // the corresponding list node should be deleted.
    	Listnode* curr;
	Listnode* prev;
	Listnode* temp;
	Book* retBook;
	int currID;

	cout << "Removing book: " << bookID << endl;
	//cout << "Next after head: " << head->next << endl;


	if(head == NULL)
	{
	   cout << "NULL head" << endl;
	   return NULL;
	}

	//just head
	if(head->next == NULL)
	{
	   cout << "head is only node atm" << endl;

	   if( (*(head->book)).getID() == bookID)
	   {
		retBook = head->book;//save return
		temp = head;
		delete temp;
		head = tail = NULL;

		cout << "head removed" << endl;

		return retBook;
	   }
	}

	//check head itself
	if(  (*(head->book)).getID() == bookID  )
	{
		temp = head;//save return
		head = head->next;
		retBook = temp->book;

		delete temp;

		cout << "head removed 2" << endl;

		return retBook;
	}

	//else traverse list past the head
	prev = head;
	curr = head->next;

	//cout << "Traverse List" << endl;

	while(curr != NULL)
	{
	   currID = (*(curr->book)).getID();

	   if(currID == bookID)
	   {
	        cout << "Current ID Matched: " << currID << endl;

		//remove
		retBook = curr->book;
		prev->next = curr->next;

		if(curr->next == NULL)
		  tail = prev; //in case its last book in list

		delete curr;

		//cout << "Successfully removed book!" << endl;

		return retBook;
	   }

	   prev = curr;
	   curr = curr->next;
	}

	return NULL;
    }

    void SortedList::print() const{
    // Prints out the list of books to standard output.  The books are
    // printed in order of book ID (from smallest to largest), one per line
       Listnode* curr;

       curr = head;

       while(curr != NULL)
       {
	  (*(curr->book)).print();
	  curr = curr->next;
       }
    }
