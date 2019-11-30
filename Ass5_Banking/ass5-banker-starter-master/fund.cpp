//
// Created by E on 11/27/2019.
//

#include "fund.h"

Fund::Fund(string Name) :
Name{Name}, Balance{0}, TransactionHistory{""}{}

ostream &operator<<(ostream &Os, Fund &TheFund) {
    Os << TheFund.Name << ": $" << TheFund.Balance;
    return Os;
}

Fund::~Fund() {} //TODO

