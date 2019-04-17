# Library-Book-Rental-Program

This program serves as a local public library that utilizes a rental system that is outdated and no longer fulfills their growing needs.

The system works with the following files:
checkout.cpp
book.h
book.cpp
person.h
person.cpp
books.txt
persons.txt
Rentals.txt

The program deals with 2 vectors.  
The books vector holds pointers of type Book and the cardholders vector holds pointers of type Person.
vector<Book *> books;
vector<Person *> cardholders;

Below are the menu options for the user.

1. Book checkout
Asks for the card ID. Confirms that the card ID is valid. Asks for the book ID to check out the book. If the card ID is not active, handle the same as an invalid card ID.
2. Book return
Asks for the book ID to perform a return. Confirms that the book ID is valid. Updates the book object.
3. View all available books
Searches the books vector and outputs all books that are available, if any.
4. View all outstanding rentals
Searches the books vectors and outputs a status report of the books that are currently checked out, if any.
5. View outstanding rentals for a cardholder
Asks for the card ID. Confirms that the card ID is valid and active. Displays a list of books they currently have checked out.
6. Open new library card
Asks for the person’s name. Creates a Person object using the new operator and inserts into the cardholders vector (use push_back). 

XXXX is the next sequential card number if this is their first time opening a card. Otherwise the old card is reactivated.
Assumptions: There are no duplicate names
7. Close library card
Asks for the card ID. Confirms that the card ID is valid and that it is not already inactive. Asks for confirmation and proceeds to deactivate the card ID.
