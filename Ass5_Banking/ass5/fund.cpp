//
// Created by E on 11/27/2019.
//

#include "fund.h"

// Gives a name and balance of zero
Fund::Fund(string Name) :
Name{Name}, Balance{0}, TransactionHistory{""}{}

ostream &operator<<(ostream &Os, Fund &TheFund) {
    Os << TheFund.Name << ": $" << TheFund.Balance;
    return Os;
}

// Destructor
Fund::~Fund() {}

// Returns the name of the fund
string Fund::getName() {
    return Name;
}

// Withdraw amount
bool Fund::withdraw(int Amount) {
    if (Amount <= 0){
//        TransactionHistory += "Error: Amount to withdraw from, "
//                + to_string(Amount) + ", is negative or zero\n";
        return false;
    }
    if (Amount <= Balance){
        Balance -= Amount;
        TransactionHistory += "                  - $" + to_string(Amount) + "\n";
        return true;
    }
    return false;
}

// check balance
int Fund::bal() {
    return Balance;
}

// deposit
void Fund::deposit(int Amount) {
    if (Amount <= 0){
//        TransactionHistory += "Error: Amount to deposit, "
//                + to_string(Amount) + ", is negative or zero\n";
    } else{
        Balance += Amount;
        TransactionHistory += "                  + $" + to_string(Amount) + "\n";
    }
}

string Fund::history() {
    string History;
    History += Name + ":\n" + TransactionHistory;
    History += "           Balance: $" + to_string(Balance) + "\n\n";
    return History;
}

