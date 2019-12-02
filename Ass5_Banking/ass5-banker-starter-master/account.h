
#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H

#include "fund.h"
#include <string>
#include <iostream>
#include <cassert>

using namespace std;

class Account {
    friend ostream& operator<<(ostream& Os, Account& Account);
private:
    string FirstName;
    string LastName;
    int ID;
    const static int FUNDCOUNT = 10;
    const static string FundName[];
    Fund* Funds[FUNDCOUNT];
public:
    Account(int ID, string LName, string FName);
    ~Account();

    //returns accountID
    int getID() const;

    // if refers to bond or money market index, returns another like fund
    // otherwise, it returns -1
    int coverWithdrawal(int FailedFund);

    // Deposit amount into Fund (given index)
    void deposit(int Into, int Amount);

    // if sufficient funds, withdraws the amount from the fund index
    bool withdrawal(int From, int Amount);

    // return transaction history for this account
    string history();

    // return transaction history for a specific fund
    string history(int Of);

    // Balance of given fund index
    int balance(int Of);

    // Sends funds to ostream
    void fundsOut(ostream &Os) const;

};
#endif // ASS5_ACCOUNT_H
