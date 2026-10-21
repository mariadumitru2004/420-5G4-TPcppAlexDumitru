#include <iostream>
#include <algorithm>
#include <vector>
#include "library.h"

using namespace std;

// Constructor
Library::Library() {}

// Add book to library
void Library::addBook(const Book &book)
{
    books.push_back(make_unique<Book>(book));
}

// Remove book from library
bool Library::removeBook(const string &isbn)
{
    auto it = find_if(books.begin(), books.end(),
                      [&isbn](const unique_ptr<Book> &book)
                      {
                          return book->getISBN() == isbn;
                      });

    if (it != books.end())
    {
        books.erase(it);
        return true;
    }
    return false;
}

// Find book by ISBN
Book *Library::findBookByISBN(const string &isbn)
{
    auto it = find_if(books.begin(), books.end(),
                      [&isbn](const unique_ptr<Book> &book)
                      {
                          return book->getISBN() == isbn;
                      });

    return (it != books.end()) ? it->get() : nullptr;
}

// Search books by title (case-insensitive partial match)
vector<Book *> Library::searchBooksByTitle(const string &title)
{
    vector<Book *> results;
    string lowerTitle = title;
    transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);

    for (auto &book : books)
    {
        string bookTitle = book->getTitle();
        transform(bookTitle.begin(), bookTitle.end(), bookTitle.begin(), ::tolower);

        if (bookTitle.find(lowerTitle) != string::npos)
        {
            results.push_back(book.get());
        }
    }
    // fonction de tri encore utilise dans search avant retour
    sort(results.begin(), results.end(), [](Book *a, Book *b)
         {
         if (a->getTitle() != b->getTitle())
         {
             return a->getTitle() < b->getTitle();
         }

         return a->getAuthor() < b->getAuthor(); });
    return results;
}

// Search books by author (case-insensitive partial match)
vector<Book *> Library::searchBooksByAuthor(const string &author)
{
    vector<Book *> results;
    string lowerAuthor = author;
    transform(lowerAuthor.begin(), lowerAuthor.end(), lowerAuthor.begin(), ::tolower);

    for (auto &book : books)
    {
        string bookAuthor = book->getAuthor();
        transform(bookAuthor.begin(), bookAuthor.end(), bookAuthor.begin(), ::tolower);

        if (bookAuthor.find(lowerAuthor) != string::npos)
        {
            results.push_back(book.get());
        }
    }
    // fonction de tri reutilisee dans search books by author
    sort(results.begin(), results.end(), [](Book *a, Book *b)
         {
         if (a->getTitle() != b->getTitle())
         {
             return a->getTitle() < b->getTitle();
         }

         return a->getAuthor() < b->getAuthor(); });
    return results;
}

// Get all available books
vector<Book *> Library::getAvailableBooks()
{
    vector<Book *> available;
    for (auto &book : books)
    {
        if (book->getAvailability())
        {
            available.push_back(book.get());
        }
    }
    // algorithme de tri avec expression lambda comme dans les notes de cours
    sort(available.begin(), available.end(), [](Book *a, Book *b)
         {
            //si les titres ne sont pas pareils on trie par titre 
             if (a->getTitle() != b->getTitle())
             {
                 return a->getTitle() < b->getTitle();
             }
            //si les titres sint pareils on trie par autheur 
             return a->getAuthor() < b->getAuthor(); });

    return available;
}

// Get all books
vector<Book *> Library::getAllBooks()
{
    vector<Book *> allBooks;
    for (auto &book : books)
    {
        allBooks.push_back(book.get());
    }

    // algorithme de tri avec expression lambda comme dans les notes de cours
    sort(allBooks.begin(), allBooks.end(), [](Book *a, Book *b)
         {
            //si les titres ne sont pas pareils on trie par titre 
             if (a->getTitle() != b->getTitle())
             {
                 return a->getTitle() < b->getTitle();
             }
            //si les titres sint pareils on trie par autheur 
             return a->getAuthor() < b->getAuthor(); });

    return allBooks;
}

// Add user to library
void Library::addUser(const User &user)
{
    users.push_back(make_unique<User>(user));
}

// Find user by ID
User *Library::findUserById(const string &userId)
{
    auto it = find_if(users.begin(), users.end(),
                      [&userId](const unique_ptr<User> &user)
                      {
                          return user->getUserId() == userId;
                      });

    return (it != users.end()) ? it->get() : nullptr;
}

// Get all users
vector<User *> Library::getAllUsers()
{
    vector<User *> allUsers;
    for (auto &user : users)
    {
        allUsers.push_back(user.get());
    }
    return allUsers;
}

// Check out book
bool Library::checkOutBook(const string &isbn, const string &userId)
{
    Book *book = findBookByISBN(isbn);
    User *user = findUserById(userId);

    if (book && user && book->getAvailability())
    {
        book->checkOut(user->getUserId());
        user->borrowBook(isbn);
        return true;
    }
    return false;
}

// Return book
bool Library::returnBook(const string &isbn)
{
    Book *book = findBookByISBN(isbn);

    if (book && !book->getAvailability())
    {
        // Find the user who borrowed this book
        for (auto &user : users)
        {
            if (user->hasBorrowedBook(isbn))
            {
                user->returnBook(isbn);
                break;
            }
        }
        book->returnBook();
        return true;
    }
    return false;
}

// Display all books
void Library::displayAllBooks()
{
    // petits changements pour utiliser le vecteur deja trie de getallbooks
    auto allBooks = getAllBooks();

    if (allBooks.empty())
    {
        cout << "Aucun livre dans la bibliothèque.\n";
        return;
    }

    cout << "\n=== TOUS LES LIVRES ===\n";
    for (size_t i = 0; i < books.size(); ++i)
    {
        cout << "\nLivre " << (i + 1) << " :\n";
        // on met le id du borrower the chaque livre et on le met dans la varuable temporaire borrowerID
        string borrowerID = allBooks[i]->getBorrowerId();
        // on cree un pointer user ou on va mettre le pointer du userID en utilisant la methode finduserbyid deja existsante
        User *borrowerpointer = findUserById(borrowerID);

        if (borrowerpointer)
        { // si le pointer nest pas null on appelle la methode tostring que jai modifie pour accepter le nom
            // sur le livre actuel
            cout << allBooks[i]->toString(borrowerpointer->getName());
        }
        else
        {
            cout << allBooks[i]->toString() << "\n";
        }
        cout << "-------------------------\n";
    }
}

// Display available books
void Library::displayAvailableBooks()
{
    auto available = getAvailableBooks();

    if (available.empty())
    {
        cout << "Aucun livre disponible pour emprunt.\n";
        return;
    }

    cout << "\n=== LIVRES DISPONIBLES ===\n";
    for (size_t i = 0; i < available.size(); ++i)
    {
        cout << "\nLivre " << (i + 1) << " :\n";
        cout << available[i]->toString() << "\n";
        cout << "---------------------------\n";
    }
}

// Display all users
void Library::displayAllUsers()
{
    if (users.empty())
    {
        cout << "Aucun utilisateur enregistré.\n";
        return;
    }

    cout << "\n=== TOUS LES UTILISATEURS ===\n";
    for (size_t i = 0; i < users.size(); ++i)
    {
        cout << "\nUtilisateur " << (i + 1) << " :\n";
        cout << users[i]->toString() << "\n";
        cout << "------------------------------\n";
    }
}

// Statistics
int Library::getTotalBooks() const { return books.size(); }
int Library::getAvailableBookCount() const
{
    return count_if(books.begin(), books.end(),
                    [](const unique_ptr<Book> &book)
                    {
                        return book->getAvailability();
                    });
}
int Library::getCheckedOutBookCount() const { return getTotalBooks() - getAvailableBookCount(); }