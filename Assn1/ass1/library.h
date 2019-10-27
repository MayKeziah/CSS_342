//
// Created by Yusuf Pisan on 3/26/18.
//

#ifndef ASS1_LIBRARY_H
#define ASS1_LIBRARY_H

#include <string>

// Only for class code, OK to use namespace
using namespace std;

// Library holds Books - can add, remove, and list Books
class Library {
  // display all Books in library
  friend ostream &operator<<(ostream &Out, const Library &Lib);

public:
  // constructor with default name
  explicit Library(const string &Name);

  // destructor
  virtual ~Library();

  /**
   * @post adds new book to library.
   * @param BookName string name of book to add
   * @return true if successful, false if book already in library or library full
   * */
  bool addBook(const string &BookName);

  /**
   * @param BookName string name of book to search
   * @return true if book found in library
   * */
  bool isInLibrary(const string &BookName) const;

  /**
   * list all books
   */
  void listAllBooks() const;

  /**
   * @post remove a book from library
   * @param BookName string name of book to remove
   * @return true if successfully removed, false if book not in library
   */
  bool removeBook(const string &BookName);

private:
    static const int MAX = 100;
    string  Books[MAX];
    int     NumberOfBooks;
    string  LibraryName;

    /**
     * @param BookName string name of book to add
     * @return true if book can be added, false if duplicate title or library full
     * */
    bool canAdd(const string &BookName) const;

    /**
     * @param Name string name of book to search
     * @return the valid index if book is in library, or -1 if book is not in library
     * */
    int findBook(const string &Name) const;
};

#endif  // ASS1_LIBRARY_H
