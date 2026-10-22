#include <fstream>
#include <iostream>
#include <filesystem>
#include "filemanager.h"

// includes pour le log dactivite
#include <chrono>  //get le temps
#include <ctime>   // convertir en date calendar
#include <iomanip> //formatter le temps en texte lisible

using namespace std;

// Constructor
FileManager::FileManager(const string &booksFile, const string &usersFile)
    : booksFileName(booksFile), usersFileName(usersFile) {}

// Save all library data
bool FileManager::saveLibraryData(Library &library)
{
    if (booksFileName.empty() || usersFileName.empty())
    {
        cout << "Il n'y a pas de --data-dir de specifie. Relancez en specifiant SVP.";
        return false;
    }
    return saveBooksToFile(library) && saveUsersToFile(library);
}

// Load all library data
bool FileManager::loadLibraryData(Library &library)
{
    bool booksLoaded = loadBooksFromFile(library);
    bool usersLoaded = loadUsersFromFile(library);
    return booksLoaded || usersLoaded; // Return true if at least one file was loaded
}

// Save books to file
bool FileManager::saveBooksToFile(Library &library)
{
    ofstream file(booksFileName);
    if (!file.is_open())
    {
        cout << "Erreur : Impossible d'ouvrir " << booksFileName << " en écriture.\n";
        return false;
    }

    auto books = library.getAllBooks();
    for (Book *book : books)
    {
        file << book->toFileFormat() << "\n";
    }

    file.close();
    return true;
}

// Save users to file
bool FileManager::saveUsersToFile(Library &library)
{
    ofstream file(usersFileName);
    if (!file.is_open())
    {
        cout << "Erreur : Impossible d'ouvrir " << usersFileName << " en écriture.\n";
        return false;
    }

    auto users = library.getAllUsers();
    for (User *user : users)
    {
        file << user->toFileFormat() << "\n";
    }

    file.close();
    return true;
}

// Load books from file
bool FileManager::loadBooksFromFile(Library &library)
{
    ifstream file(booksFileName);
    if (!file.is_open())
    {
        cout << "Aucun fichier de livres existant trouvé. Démarrage avec une bibliothèque vide.\n";
        return false;
    }

    string line;
    int count = 0;
    while (getline(file, line))
    {
        if (!line.empty())
        {
            Book book;
            book.fromFileFormat(line);
            library.addBook(book);
            count++;
        }
    }

    file.close();
    cout << "Chargé " << count << " livre(s) depuis le fichier.\n";
    return true;
}

// Load users from file
bool FileManager::loadUsersFromFile(Library &library)
{
    ifstream file(usersFileName);
    if (!file.is_open())
    {
        cout << "Aucun fichier d'utilisateurs existant trouvé. Démarrage sans utilisateurs enregistrés.\n";
        return false;
    }

    string line;
    int count = 0;
    while (getline(file, line))
    {
        if (!line.empty())
        {
            User user;
            user.fromFileFormat(line);
            library.addUser(user);
            count++;
        }
    }

    file.close();
    cout << "Chargé " << count << " utilisateur(s) depuis le fichier.\n";
    return true;
}

// Check if file exists
bool FileManager::fileExists(const string &filename)
{
    ifstream file(filename);
    return file.good();
}

// Create backup
void FileManager::createBackup()
{
    if (fileExists(booksFileName))
    {
        filesystem::copy_file(booksFileName, booksFileName + ".backup");
    }

    if (fileExists(usersFileName))
    {
        filesystem::copy_file(usersFileName, usersFileName + ".backup");
    }

    cout << "Fichiers de sauvegarde créés.\n";
}

// fonction log activite

void FileManager::logActivity(const string &action, const string &details) // argument action pour savoir c quoi laction performee et argument details pour les details du livre
{
    ofstream file("activity.log", ios::app); // ouvre le ficher log en append mode (rajouter sans effacer) + on cree le file sil existe pas

    // validation pour gerer si louverture ne fonctionne pas + afficher message console
    if (!file.is_open())
    {
        cerr << "Erreur : Impossible d'ouvrir le journal d'activités.\n";
        return;
    }

    auto now = chrono::system_clock::now();                    // get le current time
    time_t currentTime = chrono::system_clock::to_time_t(now); // convertir le temps que les utilitaires C time peuvent travailler avec

    file << put_time(localtime(&currentTime), "%Y-%m-%d %H:%M:%S") // formatter de la bonne facon et on write to the file
         << " - [" << action << "] "
         << details << "\n";
}
