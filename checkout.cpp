// Name: Paul Paguio
// Section #1
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}

// You are not obligated to use these function declarations - they're just given as examples

void readBooks(vector<Book *> & myBooks) {

  ifstream theFile;
	theFile.open("books.txt");

  int bookID;
  string author, category, title, inLine;

  while (theFile)
  {
    getline(theFile, inLine);
    if (!theFile)
			break;
    bookID = atoi(inLine.c_str());
    getline(theFile, title);
    getline(theFile, author);
    getline(theFile, category);
    getline(theFile, inLine);

      Book *newBook = new Book(bookID, title, author, category);
      myBooks.push_back(newBook);
		//myBooks.emplace_back(bookID, title, author, category);
  }

    return;
}

int readPersons(vector<Person *> & myCardholders) {

    ifstream theFile;
    theFile.open("persons.txt");

    int largestId = 0;
    int cardID;
    string firstName, lastName, strAct;
    bool active;

    while (theFile)
    {
      theFile >> cardID >> active >> firstName >> lastName;
      if(!theFile)
        break;
      Person *newPerson = new Person(cardID, active, firstName, lastName);
      myCardholders.push_back(newPerson);

      if (cardID > largestId)
      {
        largestId = cardID;
      }
    }
    return largestId + 1;
}

void openCard(vector<Person *> & myCardholders, int nextID) {
    return;
}

Book * searchBook(vector<Book *> myBooks, int id) {

    for (int i = 0; i < myBooks.size(); i++)
    {
      if(myBooks.at(i)->getId() == id)
        return myBooks.at(i);
    }
    return nullptr;
}

Person * searchPerson(vector<Person *> myPerson, int id) {

    for (int i = 0; i < myPerson.size(); i++)
    {
      if(myPerson.at(i)->getId() == id)
        return myPerson.at(i);
    }
    return nullptr;
}

void writeData (vector<Person *> cardholders, vector<Book *> books)
{
	ofstream theFile;

  theFile.open("persons.txt");
  for (int j = 0; j < cardholders.size(); j++)
  {
    theFile << cardholders.at(j)->getId() << " " << cardholders.at(j)->isActive()
      << " " << cardholders.at(j)->fullName() << endl;
  }
  theFile.close();

  theFile.open("rentals.txt");
  Person *tempPerson;
	for (int i = 0; i < books.size(); i++)
	{
    tempPerson = books.at(i)->getPersonPtr();
    if (tempPerson != nullptr)
    {
      theFile << books.at(i)->getId() << " " << tempPerson->getId() << endl;
    }
	}
	theFile.close();
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {

    Book *tempBook;
    ifstream theFile;
    theFile.open("rentals.txt");

    int bookID, cardID;

    while (theFile)
    {
       theFile >> bookID >> cardID;
       if(!theFile)
         break;
       tempBook = searchBook(myBooks, bookID);
       tempBook->setPersonPtr(searchPerson(myCardholders, cardID));
    }

    return;
}

int main()
{
    int choice, inputID, bookID, nextId = 0;
    int active = 1;
    string fname, lname, cardholderId, bookTitle;
    char yesNo;
    bool availExists, availablExists, checkExists;

    vector<Book *> books;
    vector<Person *> cardholders;

    readBooks(books);
    nextId = readPersons(cardholders);
    readRentals(books, cardholders);
    Book *tempBook;
    Person *tempPerson;
    Person *newPerson;

    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                // Book checkout
                cout << endl << "Please enter the card ID: ";
                cin >> inputID;

                tempPerson = searchPerson(cardholders, inputID);
                if (tempPerson != nullptr)
                {
                  cout << "Cardholder: " << tempPerson->fullName() << endl;
                  cout << "Please enter the book ID: ";
                  cin >> bookID;
                  tempBook = searchBook(books, bookID);
                  if (tempBook != nullptr)
                  {
                    if (tempBook->getPersonPtr() == nullptr)
                    {
                      cout << "Title: " << tempBook->getTitle() << endl;
                      tempBook->setPersonPtr(tempPerson);
                      cout << "Rental Completed " << endl;
                    }
                    else
                      cout << "Book already checked out" << endl;
                  }
                  else
                    cout << "Book ID not found" << endl;
                }
                else
                  cout << "Card ID not found" << endl;
                break;

            case 2:
                // Book return
                cout << endl;
                cout << "Please enter the book ID to return: ";
                cin >> bookID;
                tempBook = searchBook(books, bookID);
                if (tempBook != nullptr)
                {
                  tempBook->setPersonPtr(nullptr);
                  cout << "Title: " << tempBook->getTitle() << endl;
                  cout << "Return Completed " << endl;
                }

                else
                  cout << "Book ID not found " << endl;

                break;

            case 3:
                // View all available books

                cout << endl;
                availExists = false;
                for (int i = 0; i < books.size(); i++)
                {
                  if (books.at(i)->getPersonPtr() == nullptr)
                  {
                    cout << "Book ID: " << books.at(i)->getId() << endl;
                    cout << "Title: " << books.at(i)->getTitle() << endl;
                    cout << "Author: " << books.at(i)->getAuthor() << endl;
                    cout << "Category: " << books.at(i)->getCategory() << endl;
                    cout << endl;
                    availExists = true;
                  }
                }
                if (!availExists)
                  cout << "No available books" << endl;

                break;

            case 4:
                // View all outstanding rentals
                cout << endl;
                availExists = false;
                for (int i = 0; i < books.size(); i++)
                {
                  tempPerson = books.at(i)->getPersonPtr();
                  if (tempPerson != nullptr)
                  {
                    cout << "Book ID: " << books.at(i)->getId() << endl;
                    cout << "Title: " << books.at(i)->getTitle() << endl;
                    cout << "Author: " << books.at(i)->getAuthor() << endl;
                    cout << "Cardholder: " << tempPerson->fullName() << endl;
                    cout << endl;
                    availExists = true;
                  }
                }
                if (!availExists)
                  cout << "No outstanding rentals" << endl;

                break;

            case 5:
                // View outstanding rentals for a cardholder
                cout << "Please enter the card ID: ";
                cin >> inputID;
                availablExists = false;
                tempPerson = searchPerson(cardholders, inputID);
                if (tempPerson != nullptr)
                {
                  cout << "Cardholder: " << tempPerson->fullName() << endl;

                  for (int i = 0; i < books.size(); i++)
                  {
                    if (books.at(i)->getPersonPtr() == nullptr)
                    continue;

                    tempPerson = books.at(i)->getPersonPtr();
                    if (tempPerson->getId() == inputID)
                    {
                      cout << "Book ID: " << books.at(i)->getId() << endl;
                      cout << "Title: " << books.at(i)->getTitle() << endl;
                      cout << "Author: " << books.at(i)->getAuthor() << endl;
                      cout << endl;
                      availablExists = true;
                    }
                  }
                  if (!availablExists)
                    cout << "No books currently checked out" << endl;

                }
                else
                  cout << "Card ID not found" << endl;

                break;

            case 6:
                // Open new library card
                cout << "Please enter the first name: ";
                cin >> fname;
                cout << "Please enter the last name: ";
                cin >> lname;

                cout << "Card ID " << nextId << " active" << endl;
                cout << "Cardholder: " << fname << " " << lname << endl;

                newPerson = new Person(nextId, active, fname, lname);
                cardholders.push_back(newPerson);
                nextId++;

                break;

            case 7:
                // Close library card
                cout << "Please enter the card ID: ";
                cin >> inputID;
                tempPerson = searchPerson(cardholders, inputID);
                if (tempPerson != nullptr)
                {
                  cout << "Cardholder: " << tempPerson->fullName() << endl;

                  if(tempPerson->isActive())
                  {
                    cout << "Are you sure you want to deactivate card (y/n)? ";
                    cin >> yesNo;
                    if (yesNo == 'y')
                    {
                      tempPerson->setActive(0);
                      cout << "Card ID deactivated" << endl;
                      nextId--;
                    }
                  }
                  else
                    cout << "Card ID is already inactive" << endl;
                }
                else
                  cout << "Card ID not found" << endl;

                break;

            case 8:
                // Must update records in files here before exiting the program
                writeData(cardholders, books);
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}
