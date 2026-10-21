#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

class Book
{
private:
    string title;
    string author;
    string isbn;
    bool isAvailable;
    string borrowerId;

public:
    // Constructors
    Book();
    Book(const string &title, const string &author, const string &isbn);

    // Getters
    string getTitle() const;
    string getAuthor() const;
    string getISBN() const;
    bool getAvailability() const;
    string getBorrowerId() const;

    // Setters
    void setTitle(const string &title);
    void setAuthor(const string &author);
    void setISBN(const string &isbn);
    void setAvailability(bool available);
    void setBorrowerId(const string &id);

    // Methods
    void checkOut(const string &borrowerId);
    void returnBook();
    // modifier la methode tostring pour recevoir largument borrowername
    string toString(std::string borrowerName = "") const;
    string toFileFormat() const;
    void fromFileFormat(const string &line);
};

#endif
