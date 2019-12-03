
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
    cout << "The following requests were denied:\n" << endl;
    parse();
    cout << "---------------------------------------------------" << endl;
    cout << "\nHistory requests: \n\n" << HistoryRequests << endl;
    cout << "---------------------------------------------------" << endl
    << "\nAll Bank Balances:\n" << endl;
    displayAllBankBalances();
    cout << "---------------------------------------------------" << endl;
}

// Display all bank balances to console
void Bank::displayAllBankBalances() const {
    Accounts.display();
}

// if can withdraw 'from', deposits 'to'
bool
Bank::transfer(int FromID, int FromFund, int ToID, int ToFund, int Amount) {
    if(withdraw(FromID, FromFund, Amount)){
        return deposit(ToID, ToFund, Amount);
    } return false;
}

// increases balance by amount
bool Bank::deposit(int AccountID, int Fund, int Amount) {
    ErrorLog.str("");
    Account* SendMoney;
    Accounts.retrieve(AccountID, SendMoney);
    if (SendMoney != nullptr){
        return SendMoney->deposit(Fund, Amount, ErrorLog);
    }
    ErrorLog << "Account " << AccountID << " does not exist." << endl;
    return false;
}

// True if Account Fund contains sufficient funds,
// Withdraws amount. False if insufficient
bool Bank::withdraw(int AccountID, int Fund, int Amount) {
    ErrorLog.str("");
    Account* RequestMoney;
    Accounts.retrieve(AccountID, RequestMoney);
    if(RequestMoney == nullptr){
        ErrorLog << "Account " << AccountID << " does not exist." << endl;
        return false;
    }
    return RequestMoney->withdrawal(Fund, Amount, ErrorLog);
}

// Read and process transaction requests
void Bank::parse() {
    while(!Transactions.empty()) {
        stringstream Request;
//        auto *ToRetreive = new Account(1234, "", ""); //TODO
        Account *ToRetreive = nullptr;
        int Account;
        int Amount;

        Request << Transactions.front();
        Transactions.pop();
        string Transaction; //TODO quick science
        Request >> Transaction;

        if (Transaction == "O") { // Open account
            parseOpen(Request, Account);
        } else if (Transaction == "H") { // View account history
            parseHistory(ToRetreive, Request, Account);

        } else if (Transaction == "D") {
                parseDeposit(Request, Account, Amount);
        } else if (Transaction == "W") {
                parseWithdrawal(Request, Account, Amount);
        } else if (Transaction == "T") {
                parseTransfer(Request, Account, Amount);
        }
//        delete ToRetreive;
    }
}

// Parses a transfer request
void Bank::parseTransfer(stringstream &Request, int &Account, int &Amount) {
    int ToAccount;
    Request >> Account >> Amount >> ToAccount;
    if (!transfer(Account / 10, Account % 10, ToAccount / 10,
                  ToAccount % 10, Amount)) {
        cout << "ERROR: T " << Account << " " << Amount
             << " " << ToAccount << endl
             << "    Transfer request fail. " << ErrorLog.str() << endl;
    }
}

// Parses a withdrawal request
void Bank::parseWithdrawal(stringstream &Request, int &Account, int &Amount) {
    Request >> Account >> Amount;
    if (!withdraw(Account / 10, Account % 10, Amount)) {
        cout << "ERROR: W " << Account << " " << Amount << endl
             << "    Withdrawal request fail. " << ErrorLog.str() << endl;
    }
}

// Parses a deposit request
void Bank::parseDeposit(stringstream &Request, int &Account, int &Amount) {
    Request >> Account >> Amount;
    if (!deposit(Account / 10, Account % 10, Amount)) {
        cout << "ERROR: D " << Account << " " << Amount << endl
             << "    Deposit request fail. " << ErrorLog.str() << endl;
    }
}

// Parses an account history request
void
Bank::parseHistory(Account *ToRetreive, stringstream &Request, int &Account) {
    Request >> Account;
    if (Account > 9999) { // For specific fund
                Accounts.retrieve(Account / 10, ToRetreive);
        if (ToRetreive != nullptr) {
            history(ToRetreive->history(Account % 10));
        } else {
            cout << "ERROR: H " << Account << endl
                 << "    History request fail. Account number "
                 << Account << " does not exist." << endl;
        }
    } else { // For entire account
                Accounts.retrieve(Account, ToRetreive);
        if (ToRetreive != nullptr) {
            history(ToRetreive->history());
        } else {
            cout << "ERROR: H " << Account << endl
                 << "    History request fail. Account number "
                 << Account << " does not exist." << endl;
        }
    }
}

// Parses an open account request
void Bank::parseOpen(stringstream &Request, int &Account) {
    string Last;
    string First;
    Request >> Last >> First >> Account;
    if (!open(Account, Last, First)) { // If open fails
        cout << "ERROR: O " << Last << " " << First << " " << Account
             << endl << "    Open Fail. Account number "
             << Account << " already exists." << endl << endl;
    }
}

bool Bank::open(int AccountID, string LastName, string FirstName) {
    return Accounts.insert
    (new Account(AccountID, LastName, FirstName) );
}

void Bank::history(string AccountHistory) {
    HistoryRequests += AccountHistory;
}
