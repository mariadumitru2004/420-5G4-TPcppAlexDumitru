#include "book.h"
#include <iostream>
#include <bits/stdc++.h> 

using std::string;

//constructeur vide
Book::Book() :  title(""), author(""), isbn(""), isAvailable(true), borrowerId("")
{

}
//constructeur avec parametre title author isbn
Book::Book(const string& title, const string& author, const string& isbn)
    : title(title), author(author), isbn(isbn), isAvailable(true), borrowerId("") {

        if (title.empty() || author.empty() || isbn.empty()) {
        throw invalid_argument("Le titre, autheur, et le ISBN ne peuvent pas etre vides.Saisissez de nouveau.");
    }
    }

    
//getters

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

string Book::getISBN() const {
    return isbn;
}

bool Book::getAvailability() const {
    return isAvailable;
}

string Book::getBorrowerId() const {
    return borrowerId;
}

// setters

void Book::setTitle(const string& title) {
    this->title = title;
}

void Book::setAuthor(const string& author) {
    this->author = author;
}

void Book::setISBN(const string& isbn) {
    this->isbn = isbn;
}

void Book::setAvailability(bool available) {
    isAvailable = available;
}

void Book::setBorrowerId(const string& name) {
    borrowerId = name;
}


