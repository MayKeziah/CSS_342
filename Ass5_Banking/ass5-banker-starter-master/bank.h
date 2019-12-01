
#ifndef ASS5_BANK_H
#define ASS5_BANK_H

#include "accounttree.h"
#include <fstream>
#include <string>
#include <queue>

using namespace std;

class Bank {
private:
    AccountTree Accounts;
    queue<string> Transactions;
public:
    Bank();
    ~Bank();
    void processTransactions(const string &FileName);

  void displayAllBankBalances() const;
};
#endif // ASS5_BANK_H
