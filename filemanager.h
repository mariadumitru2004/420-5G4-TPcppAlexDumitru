#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

#include "library.h"

using namespace std;

class FileManager
{
private:
    string booksFileName;
    string usersFileName;

public:
    // Constructor
    FileManager(const string &booksFile, const string &usersFile);

    // File operations
    bool saveLibraryData(Library &library);
    bool loadLibraryData(Library &library);

    // Individual file operations
    bool saveBooksToFile(Library &library);
    bool saveUsersToFile(Library &library);
    bool loadBooksFromFile(Library &library);
    bool loadUsersFromFile(Library &library);
    // ajout de methode logactivity pour le journal dactivite
    void logActivity(const string &action, const string &details);
    // Utility methods
    bool fileExists(const string &filename);
    void createBackup();
};

#endif
