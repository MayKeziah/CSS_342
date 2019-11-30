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
    explicit Fund(string Name);
    ~Fund(); //TODO
};


#endif //ASS5_BANKER_FUND_H
