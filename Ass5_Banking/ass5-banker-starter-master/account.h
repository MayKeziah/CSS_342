
#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H

#include "fund.h"
#include <string>
#include <iostream>
#include <cassert>

using namespace std;

class Account {
    friend ostream& operator<<(ostream& Os, Account& Account);
public:
    Account(int ID, string LName, string FName);
    ~Account();
    int getID() const;

private:
    string FirstName;
    string LastName;
    int ID;
    const static int FUNDCOUNT = 10;
    const static string FundName[];
    Fund* Funds[FUNDCOUNT];
};
#endif // ASS5_ACCOUNT_H
