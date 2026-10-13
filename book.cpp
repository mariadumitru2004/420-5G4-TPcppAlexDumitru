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


