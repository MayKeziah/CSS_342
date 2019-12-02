//
// Created by E on 11/27/2019.
//

#ifndef ASS5_BANKER_FUND_H
#define ASS5_BANKER_FUND_H
#include <iostream>
#include <string>

using namespace std;

class Fund {
    friend ostream& operator<<(ostream& Os, Fund& TheFund);
private:
    string Name;
    int Balance;
    string TransactionHistory;
public:
    // Gives a name and balance of zero
    explicit Fund(string Name);
    ~Fund(); //TODO

    // Returns the name of the fund
    string getName();

    // Withdraw amount false if insufficient funds
    bool withdraw(int Amount);

    // check balance
    int bal();

    // deposit
    void deposit(int Amount);

    // return transaction history for this fund
    string history();

};


#endif //ASS5_BANKER_FUND_H
