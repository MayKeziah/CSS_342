
#include "bank.h"

// empty


Bank::Bank() = default;

Bank::~Bank() = default;

void Bank::processTransactions(const string &FileName) {
    ifstream File;
    File.open(FileName, fstream::in);

    if(File.is_open()){
        while(!File.eof()){
            string Line;
            getline(File, Line);
            Transactions.push(Line); // TODO check line
        }
    }
    File.close();

}

void Bank::displayAllBankBalances() const {

}