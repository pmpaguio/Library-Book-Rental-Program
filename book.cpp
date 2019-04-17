#include "book.h"

Book::Book(int id, string bookName, string auth, string cat) {
    // complete constructor
    this->bookID = id;
    this->title = bookName;
    this->author = auth;
    this->category = cat;
}

string Book::getTitle() {
    return title; // complete
}

string Book::getAuthor() {
    return author; // complete
}

string Book::getCategory() {
    return category; // complete
}

int Book::getId() {
    return bookID; // complete
}

void Book::setPersonPtr(Person * ptr) {
  personPtr = ptr;
} // complete


Person * Book::getPersonPtr() {
    return personPtr; // complete
}
