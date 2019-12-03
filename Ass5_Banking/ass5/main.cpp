
#include "bank.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int TestsPassed = 0;
int Tests = 0;

template <typename Type> void check(const Type &Got, const Type &Expected){
    Tests++;
    if(Got == Expected){
        TestsPassed++;
        cout << "\tPass: ";
    } else {
        cout << "\t-- Got: " << Got << endl;
        cout << "\t-- Expected: " << Expected << endl;
        cout << "\tError: ";
    }
}

void bankTest(){
    cout << "\nTesting bank class..." << endl;

    Bank Test0;

    string FileName = R"(C:\Users\E\Documents\UWB\1_F19\CSS_342\Code)";
    FileName += R"(\Ass5_Banking\ass5-banker-starter-master\BankTransIn.txt)";

    Test0.processTransactions(FileName);
}

void accountTreeTest(){
    cout << "\nTesting account tree class..." << endl;

    /*****************************************
     * Test single Node AccountTree
     *****************************************/
    auto* ExpectedAccount = new Account(1234, "Last", "First");
    AccountTree Test0;
    Test0.insert(ExpectedAccount);
    Account* RetrievedAccount;
    Test0.retrieve(ExpectedAccount->getID(), RetrievedAccount);

    check(RetrievedAccount, ExpectedAccount);

    cout << "Single node AccountTree insert/retrieve" << endl;

    delete ExpectedAccount;
    ExpectedAccount = nullptr;

    /*****************************************
     * Test clear/isEmpty
     *****************************************/
    check(Test0.isEmpty(), false);
    cout << "Tree not empty" << endl;

    Test0.clear();
    check(Test0.isEmpty(), true);
    cout << "Tree is empty" << endl;

    /*****************************************
     * Test insert/<< for populated tree
     *****************************************/
    int IDs[8] = {3333, 1111, 2222, 4444, 1234, 5555, 6666, 2345};
    for (auto Id : IDs){
        Test0.insert(new Account(Id, "", ""));
    }

//    stringstream Expected;
//    Expected << "1111 1234 2222 2345 3333 4444 5555 6666 ";
//
//    stringstream Got;
//    Got << Test0;

//    check(Got.str(), Expected.str());
//    cout << "Populated tree InOrder to ostream" << endl;

    /*****************************************
     * Test good retrieve for populated tree
     *****************************************/
    Test0.retrieve(2345, RetrievedAccount);
    check(RetrievedAccount->getID(), 2345);
    cout << "Tree retrieves from populated tree" << endl;

    /*****************************************
     * Test bad retrieve for populated tree
     *****************************************/
    Test0.retrieve(1010, RetrievedAccount);
    check(RetrievedAccount, ExpectedAccount);
    cout << "Tree bad-retrieve gives nullptr from populated tree" << endl;

}

void fundTest(){
    cout << "\nTesting fund class..." << endl;
    /*****************************************
     * Test Fund single parameter constructor
     *****************************************/
    Fund Test0("Money Market");

    stringstream Expected;
    Expected << "Money Market:  $0";

    stringstream Got;
    Got << Test0;

    check(Got.str(), Expected.str());
    cout << "Fund single parameter constructor" << endl;

    /*****************************************
     * Test Fund bal
     *****************************************/
    Expected.str("");
    Got.str("");

    check(Test0.bal(), 0);
    cout << "Fund starting balance == 0" << endl;

    /*****************************************
     * Test Fund bal / deposit
     *****************************************/
    Test0.deposit(100); // Added to historu
    check(Test0.bal(), 100);
    cout << "Fund balance is as expected following deposit" << endl;

    /*****************************************
     * Test Fund bal / deposit invalid amount
     *****************************************/
    Test0.deposit(-1);
    check(Test0.bal(), 100);
    cout << "Fund balance is as expected following invalid deposit" << endl;

    /*****************************************
     * Test Fund bal / withdraw when insufficient
     *****************************************/
    check(Test0.withdraw(101), false);
    cout << "Fund rejects withdrawal when balance insufficient" << endl;

    /*****************************************
     * Test Fund bal / withdraw when sufficient
     *****************************************/
    check(Test0.withdraw(25), true); // added to hist
    cout << "Fund accepts withdrawal when balance is sufficient" << endl;
    check(Test0.bal(), 75);
    cout << "Fund balance is as expected following withdrawal" << endl;

    /*****************************************
     * Test Fund bal / withdraw when invalid
     *****************************************/
    check(Test0.withdraw(-1), false);
    cout << "Fund rejects withdrawal when amount is " << endl;
    check(Test0.bal(), 75);
    cout << "Fund balance is as expected following withdrawal" << endl;

    /*****************************************
     * Test Fund history
     *****************************************/
//    Got << Test0.history();
//    Expected << Test0.getName() << ":\n"
//    << "\t\t+ $100\n\t\t- $25\n Balance: $75\n";
//    check(Got.str(), Expected.str());
//    cout << "Fund history recorded for successful transactions" << endl;
}

void accountTest(){
    cout << "\nTesting account class..." << endl;

    /*****************************************
     * Test account constructor
     *****************************************/
    Account Test0(1234, "Last", "First");

//    stringstream Expected;
//    Expected << "1234: Last, First";
//
//    stringstream Got;
//    Got << Test0;
//    check(Got.str(), Expected.str());
//    cout << "Account constructor" << endl;

    /*****************************************
     * Test account deposit/withdrawal/balance normal
     *****************************************/
     for (int Fund = 0; Fund < 10; Fund++){
         Test0.deposit(Fund, Fund + 100);
         check(Test0.balance(Fund), Fund + 100);
         cout << "Account Deposit adjusts fund balance" << endl;

         Test0.withdrawal(Fund, Fund);
         check(Test0.balance(Fund), 100);
         cout << "Account withdrawal adjusts fund balance" << endl;
     }

    /*****************************************
     * Test account over-withdrawal covered for Money Market
     *****************************************/
     Test0.withdrawal(0, 150);
     check(Test0.balance(0), 0);
     cout << "Account can cover a MM withdrawal with PMM fund" << endl;
     check(Test0.balance(1), 50);
     cout << "Account supplemented withdrawal correctly for MM" << endl;

    /*****************************************
     * Test account over-withdrawal covered for Bond
     *****************************************/
    Test0.withdrawal(3, 150);
    check(Test0.balance(3), 0);
    cout << "Account can cover a MM withdrawal with PMM fund" << endl;
    check(Test0.balance(2), 50);
    cout << "Account supplemented withdrawal correctly for MM" << endl;

    /*****************************************
     * Test account over-withdrawal covered for Bond
     *****************************************/
    Test0.withdrawal(4, 150);
    check(Test0.balance(4), 100);
    cout << "Account rejects over-withdrawal on regular fund" << endl;
}

int main(int Argc, char *Argv[]) {
    Bank Bank;
    //Note that tests were done in BankTransIn.txt
    for(int I = 1; I < Argc; ++I) {
        cout << "The command line argument(s) was " << Argv[I] << std::endl;
        string FileName = Argv[I];
        Bank.processTransactions(FileName);
        cout << endl
        <<
        "___________________________________________________________________"
        "_____________________" << endl << endl;
    }
//    accountTest();
//    fundTest();
//    accountTreeTest();
//    bankTest();

//    cout << endl << "Total: " << endl
//    << "\t" << TestsPassed << "/" << Tests << endl;
    cout << "Done" << endl;
    return 0;
}