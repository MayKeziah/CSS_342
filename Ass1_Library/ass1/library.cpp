/**
 * Created by Keziah May on 10/02/2019.
 * Library class demonstrating partially filled arrays
 * Can add/remove books from library find
 * books in library.
 * @version 1.1
 * */


#include "library.h"
#include <iostream>

// constructor with default name
Library::Library(const string &Name) : LibraryName(Name), NumberOfBooks(0){
}

// destructor
// nothing on heap
Library::~Library() {
  // destructor
}

/*******************************************************
 * Public functions
 *******************************************************/

/**
 * @post adds new book to library.
 * @param BookName string name of book to add
 * @return true if successful, false if book already in library or library full
 * */
bool Library::addBook(const string &BookName) {
    if (canAdd(BookName)){
        Books[NumberOfBooks] = BookName;
        NumberOfBooks++;
        return Books[NumberOfBooks - 1] == BookName;
    } return false;
}

/**
 * @param BookName string name of book to search
 * @return true if book found in library
 * */
bool Library::isInLibrary(const string &BookName) const {
    return findBook(BookName) != -1;
}


void Library::listAllBooks() const {
    cout << *this;
}

/**
 * @post remove a book from library
 * @param BookName string name of book to remove
 * @return true if successfully removed, false if book not in library
 */
bool Library::removeBook(const string &BookName) {
    int Index = findBook(BookName);
    if (Index != -1) {
        Books[Index] = Books[--NumberOfBooks];
        return true;
    } return false;
}

/**
 * @post Overrides the "<<" operator.
 * When used with a reference to a library object,
 * lists the contents of the library.
 * @return ostream listing the numbered contents of the library
 */
ostream &operator<<(ostream &Out, const Library &Lib) {
    Out << Lib.LibraryName << " Library Book List:\n";
    for (int I = 0; I < Lib.NumberOfBooks; I++) {
        Out << I + 1 << ") " << Lib.Books[I] << endl;
    }  return Out;
}

/*******************************************************
 * Private functions
 *******************************************************/

/**
 * @param BookName string name of book to add
 * @return true if book can be added, false if duplicate title or library full
 * */
bool Library::canAdd(const string &BookName) const {
    return (NumberOfBooks < MAX) && !(isInLibrary(BookName));
}

/**
 * @param BookName string name of book to search
 * @return the valid index if book is in library, or -1 if book is not in library
 * */
int Library::findBook(const string &BookName) const {
    for (int I = 0; I < NumberOfBooks; I++){
        if (Books[I] == BookName){
            return I;
        }
    }
    return -1;
}


