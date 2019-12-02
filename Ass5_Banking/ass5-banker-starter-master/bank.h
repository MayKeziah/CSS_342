
#ifndef ASS5_BANK_H
#define ASS5_BANK_H

#include "accounttree.h"
#include <fstream>
#include <string>
#include <queue>
#include <sstream>

using namespace std;

class Bank {
private:
    AccountTree Accounts;
    queue<string> Transactions;
public:
    Bank();
    ~Bank();

    // Takes a file of transaction requests
    // and processes them in order (FIFO)
    void processTransactions(const string &FileName);

    // True if Account Fund contains sufficient funds,
    // Withdraws amount. False if insufficient
    bool withdraw(int AccountID, int Fund, int Amount);

    // increases balance by amount
    void deposit(int AccountID, int Fund, int Amount);

    // if can withdraw 'from', deposits 'to'
    void transfer(int FromID, int FromFund, int ToID, int ToFund, int Amount);

    // Display all bank balances to console
    void displayAllBankBalances() const;

    // Read and process transaction requests
    void parse();

    // Open a new account
    bool open(int AccountID, string LastName, string FirstName);
};
#endif // ASS5_BANK_H
