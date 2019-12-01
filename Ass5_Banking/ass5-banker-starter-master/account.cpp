
// empty

#include "account.h"

const string Account::FundName[] =
    {
    "Money Market",
    "Prime Money Market",
    "Long-Term Bond",
    "Short-Term Bond",
    "500 Index Fund",

    "Capital Value Fund",
    "Growth Equity Fund",
    "Growth Index Fund",
    "Value Fund",
    "Value Stock Index"
    };

Account::Account(int ID, string LName, string FName) :
ID{ID}, LastName{LName}, FirstName{FName} {
//    assert( (ID > 999) && (ID < 10000) );
    for (int I = 0; I < FUNDCOUNT; I++){
        Funds[I] = new Fund(FundName[I]); //TODO delete
    }
}

Account::~Account() {
    for (int I = 0; I < FUNDCOUNT; I++){
        delete Funds[I];
    }
} //TODO

//Sends account information to the ostream
ostream &operator<<(ostream &Os, Account &TheAccount) {
    if (TheAccount.ID == 0){
        Os << "Empty Account";
    }
    else{
        Os << TheAccount.ID;
        Os << ": " << TheAccount.LastName << ", " << TheAccount.FirstName;
    }
    return Os;
}

int Account::getID() const {
    return ID;
}

