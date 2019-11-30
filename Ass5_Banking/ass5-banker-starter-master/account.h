
#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H

#include "fund.h"
#include <string>
#include <iostream>

using namespace std;

class Account {
    friend ostream& operator<<(ostream& Os, Account& Account);
public:
    Account(int ID, string LName, string FName);
    ~Account();
    int getID() const;

private:
    const static int FUNDCOUNT = 10;
    Fund* Funds[FUNDCOUNT];
    string FirstName;
    string LastName;
    int ID;
    const static string FundName[];
};
#endif // ASS5_ACCOUNT_H
