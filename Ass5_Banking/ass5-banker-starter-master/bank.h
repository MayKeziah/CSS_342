
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
    string HistoryRequests;
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
    bool deposit(int AccountID, int Fund, int Amount);

    // if can withdraw 'from', deposits 'to'
    bool transfer(int FromID, int FromFund, int ToID, int ToFund, int Amount);

    // Display all bank balances to console
    void displayAllBankBalances() const;

    // Read and process transaction requests
    void parse();

    // store account history in HistoryRequest string to output
    void history(string AccountHistory);

    // Open a new account
    bool open(int AccountID, string LastName, string FirstName);

    // Parses an open account request
    void parseOpen(stringstream &Request, int &Account);

    // Parses an account history request
    void
    parseHistory(Account *ToRetreive, stringstream &Request, int &Account);

    // Parses a deposit request
    void parseDeposit(stringstream &Request, int &Account, int &Amount);

    // Parses a withdrawal request
    void parseWithdrawal(stringstream &Request, int &Account, int &Amount);

    // Parses a transfer request
    void parseTransfer(stringstream &Request, int &Account, int &Amount);
};
#endif // ASS5_BANK_H
