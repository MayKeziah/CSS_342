
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
    parse();
    displayAllBankBalances();

}

// Display all bank balances to console
void Bank::displayAllBankBalances() const {
    Accounts.display();
}

// if can withdraw 'from', deposits 'to'
void
Bank::transfer(int FromID, int FromFund, int ToID, int ToFund, int Amount) {
    if(withdraw(FromID, FromFund, Amount)){
        deposit(ToID, ToFund, Amount);
    }
}

// increases balance by amount
void Bank::deposit(int AccountID, int Fund, int Amount) {
    Account* SendMoney;
    Accounts.retrieve(AccountID, SendMoney);
    if (SendMoney != nullptr){
        SendMoney->deposit(Fund, Amount);
    }
}

// True if Account Fund contains sufficient funds,
// Withdraws amount. False if insufficient
bool Bank::withdraw(int AccountID, int Fund, int Amount) {
    Account* RequestMoney;
    Accounts.retrieve(AccountID, RequestMoney);
    if(RequestMoney == nullptr){
        return false;
    }
    return RequestMoney->withdrawal(Fund, Amount);
}

// Read and process transaction requests
void Bank::parse() {
    while(!Transactions.empty()){
        stringstream Request;
        Account* ToRetreive = nullptr;
        int Account;

        Request << Transactions.front();
        if (Request.str() != ""){

        }
        Transactions.pop();
        string Transaction;
        Request >> Transaction;

        if(Transaction == "O"){ // Open account
            string Last;
            string First;
            Request >> Last >> First >> Account;
            open(Account, Last, First);
        }
        else if (Transaction == "H"){
            Request >> Account;
            if (Account > 9999){
                Accounts.retrieve(Account / 10, ToRetreive);
                if (ToRetreive != nullptr){
                    cout << ToRetreive->history(Account % 10);
                }
            }else {
                Accounts.retrieve(Account, ToRetreive);
                if (ToRetreive != nullptr){
                    cout << ToRetreive->history();
                }
            }

        }
        else {
            int Amount;
            if (Transaction == "D") {
                Request >> Account >> Amount;
                deposit(Account / 10, Account % 10, Amount);
            } else if (Transaction == "W") {
                Request >> Account >> Amount;
                withdraw(Account / 10, Account % 10, Amount);
            } else if (Transaction == "T"){
                int ToAccount;
                Request >> Account >> Amount >> ToAccount;
                transfer(Account / 10, Account % 10, ToAccount / 10,
                        ToAccount % 10, Amount);
            }
        }
    }
}

bool Bank::open(int AccountID, string LastName, string FirstName) {
    return Accounts.insert
    (new Account(AccountID, LastName, FirstName) );
}
