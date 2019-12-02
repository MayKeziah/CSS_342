
// empty

#include "account.h"

//name of funds
const string Account::FundName[] =
    {
    "      Money Market",
    "Prime Money Market",
    "    Long-Term Bond",
    "   Short-Term Bond",
    "    500 Index Fund",

    "Capital Value Fund",
    "Growth Equity Fund",
    " Growth Index Fund",
    "        Value Fund",
    " Value Stock Index"
    };

// Constructor
Account::Account(int ID, string LName, string FName) :
ID{ID}, LastName{LName}, FirstName{FName} {
//    assert( (ID > 999) && (ID < 10000) );
    for (int I = 0; I < FUNDCOUNT; I++){
        Funds[I] = new Fund(FundName[I]);
    }
}

// Destructor
Account::~Account() {
    for (int I = 0; I < FUNDCOUNT; I++){
        delete Funds[I];
    }
}

//Sends account information to the ostream
ostream &operator<<(ostream &Os, Account &TheAccount) {
    Os << "------- " << TheAccount.ID
    << ": " << TheAccount.LastName << ", " << TheAccount.FirstName
    << " -------\n";
    TheAccount.fundsOut(Os);
    return Os;
}

//returns accountID
int Account::getID() const {
    return ID;
}

// if sufficient funds, withdraws the amount from the fund index
bool Account::withdrawal(int From, int Amount) {
    if (From > FUNDCOUNT - 1) {
//        cerr << "Error: Fund " << From << " does not exist." << endl;
        return false;
    } if (Amount <= 0) {
//        cerr << "Error: Amount to withdraw from " << Funds[From]->getName() <<
//             ", " << Amount << ", is negative or zero" << endl;

        return Funds[From]->withdraw(Amount);
    }
    if (!Funds[From]->withdraw(Amount)) {
        int OtherFund = coverWithdrawal(From);
        int Remainder = Amount - Funds[From]->bal();
        if (OtherFund != -1 && Funds[OtherFund]->bal() >= Remainder) {
            Funds[From]->withdraw(Funds[From]->bal());
            Funds[OtherFund]->withdraw(Remainder);
            return true; // Covered by other account
        } return false; // No other account to cover

    } return true; // Sufficient funds in original account

}

// if FailedFund was a bond or money market account,
// returns the other fund (of the same type) index
// otherwise, it returns -1
int Account::coverWithdrawal(int FailedFund) {
    if (FailedFund > 3 || FailedFund < 0){ // if invalid
        return -1;
    }
    if(FailedFund % 2){ // if 1 or 3
        return FailedFund - 1;
    }
    return FailedFund + 1; // if 0 or 2
}

// Deposit amount into Fund (given index)
void Account::deposit(int Into, int Amount) {
    Funds[Into]->deposit(Amount);
}

// return transaction history for this account
string Account::history() {
    string AccountHistory;
    AccountHistory += "------- History of " + to_string(ID) + ": "
            + LastName + ", " + FirstName + " -------\n";
    for (int Fund = 0; Fund < FUNDCOUNT; Fund++){
        AccountHistory += Funds[Fund]->history();
    }
    return AccountHistory;
}

// return transaction history for a specific fund
string Account::history(int Of) {
    string AccountHistory;
    AccountHistory += "------- History of " + to_string(ID) + to_string(Of) +
            ": "
                      + LastName + ", " + FirstName + " -------\n";
    return AccountHistory + Funds[Of]->history();
}

// Balance of given fund index
int Account::balance(int Of) {
    return Funds[Of]->bal();
}

// Sends funds to ostream
void Account::fundsOut(ostream &Os) const{
    for(auto* Fund : Funds){
        Os << *Fund << endl;
    }
}