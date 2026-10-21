#include "book.h"
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>

using std::string;

// constructeur vide
Book::Book() : title(""), author(""), isbn(""), isAvailable(true), borrowerId("")
{
}
// constructeur avec parametre title author isbn
Book::Book(const string &title, const string &author, const string &isbn)
    : title(title), author(author), isbn(isbn), isAvailable(true), borrowerId("")
{

    if (title.empty() || author.empty() || isbn.empty())
    {
        throw invalid_argument("Le titre, autheur, et le ISBN ne peuvent pas etre vides.Saisissez de nouveau.");
    }
}

// getters

string Book::getTitle() const
{
    return title;
}

string Book::getAuthor() const
{
    return author;
}

string Book::getISBN() const
{
    return isbn;
}

bool Book::getAvailability() const
{
    return isAvailable;
}

string Book::getBorrowerId() const
{
    return borrowerId;
}

// setters

void Book::setTitle(const string &title)
{
    this->title = title;
}

void Book::setAuthor(const string &author)
{
    this->author = author;
}

void Book::setISBN(const string &isbn)
{
    this->isbn = isbn;
}

void Book::setAvailability(bool available)
{
    isAvailable = available;
}

void Book::setBorrowerId(const string &name)
{
    borrowerId = name;
}

// methodes

// methode checkout
void Book::checkOut(const string &borrower)
{
    isAvailable = false;
    borrowerId = borrower;
}

// methode retour
void Book::returnBook()
{
    isAvailable = true;
    borrowerId = "";
}

// methode tostring modifiee
string Book::toString(std::string borrowerName) const
{
    string available = isAvailable ? "Oui" : "Non";
    string borrower = isAvailable ? "/" : borrowerId;

    return "Titre: " + title + "\n" +
           "Auteur: " + author + "\n" +
           "ISBN: " + isbn + "\n" +
           "Disponible?: " + available + "\n" +
           "Emprunteur: " + borrowerName + "\n";
}

// methode pour formatter la sauvegarde dans le fichier
string Book::toFileFormat() const
{
    return title + "|" + author + "|" + isbn + "|" + (isAvailable ? "1" : "0") + "|" + borrowerId;
}

// methode pour extraire ce quon lit du fichier
void Book::fromFileFormat(const string &line)
{
    stringstream ss(line);
    string token;

    // titre
    if (getline(ss, token, '|'))
    {
        title = token;
    }

    // auteur
    if (getline(ss, token, '|'))
    {
        author = token;
    }

    // isbn
    if (getline(ss, token, '|'))
    {
        isbn = token;
    }

    // dispo + convertir true a 1
    if (getline(ss, token, '|'))
    {
        isAvailable = token == "1";
    }

    // id du emprunteur
    if (getline(ss, token, '|'))
    {
        borrowerId = token;
    }
}
