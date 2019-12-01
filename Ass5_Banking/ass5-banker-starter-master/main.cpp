
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
        cout << "Pass: ";
    } else {
        cout << "Got: " << Got << endl;
        cout << "Expected: " << Expected << endl;
        cout << "Error: ";
    }
}

void bankTest(){
    Bank Test0;

    string FileName = R"(C:\Users\E\Documents\UWB\1_F19\CSS_342\Code)";
    FileName += R"(\Ass5_Banking\ass5-banker-starter-master\BankTransIn.txt)";

    Test0.processTransactions(FileName);
}

void accountTreeTest(){
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
    Test0.clear();

    /*****************************************
     * Test clear/insert/retrieve/<</outInOrder
     * for populated tree
     *****************************************/
    int IDs[8] = {3333, 1111, 2222, 4444, 1234, 5555, 6666, 2345};
    for (auto Id : IDs){
        Test0.insert(new Account(Id, "", ""));
    }

    stringstream Expected;
    Expected << "1111 1234 2222 2345 3333 4444 5555 6666 ";

    stringstream Got;
    Got << Test0;

    check(Got.str(), Expected.str());
    cout << "Populated tree InOrder to ostream" << endl;


}

void fundTest(){
    /*****************************************
     * Test single parameter constructor
     *****************************************/
    Fund Test0("Money Market");

    stringstream Expected;
    Expected << "Money Market: $0";

    stringstream Got;
    Got << Test0;

    check(Got.str(), Expected.str());
    cout << "Single parameter fund constructor" << endl;

    /*****************************************
     * Test bal
     *****************************************/
    Expected.str("");
    Got.str("");

    check(Test0.bal(), 0);
    cout << "Starting fund balance == 0" << endl;

    /*****************************************
     * Test bal / deposit
     *****************************************/
    Test0.deposit(100);
    check(Test0.bal(), 100);
    cout << "Fund balance is as expected following deposit" << endl;

    /*****************************************
     * Test bal / deposit invalid amount
     *****************************************/
    Test0.deposit(-1);
    check(Test0.bal(), 100);
    cout << "Fund balance is as expected following invalid deposit" << endl;

    /*****************************************
     * Test bal / withdraw when insufficient
     *****************************************/
    check(Test0.withdraw(101), false);
    cout << "Fund rejects withdrawal when balance insufficient" << endl;

    /*****************************************
     * Test bal / withdraw when sufficient
     *****************************************/
    check(Test0.withdraw(25), true);
    cout << "Fund accepts withdrawal when balance is sufficient" << endl;
    check(Test0.bal(), 75);
    cout << "Fund balance is as expected following withdrawal" << endl;

    /*****************************************
     * Test bal / withdraw when invalid
     *****************************************/
    check(Test0.withdraw(-1), false);
    cout << "Fund rejects withdrawal when amount is " << endl;
    check(Test0.bal(), 75);
    cout << "Fund balance is as expected following withdrawal" << endl;
}

void accountTest(){
    /*****************************************
     * Test account constructor
     *****************************************/
    Account Test0(1234, "Last", "First");

    stringstream Expected;
    Expected << "1234: Last, First";

    stringstream Got;
    Got << Test0;
    check(Got.str(), Expected.str());
    cout << "Regular account constructor" << endl;

}

int main(int Argc, char *Argv[]) {
//    Bank Bank;
//    //Note that tests were done in BankTransIn.txt
//    for(int I = 1; I < Argc; ++I) {
//        cout << "The command line argument(s) was " << Argv[I] << std::endl;
//        string FileName = Argv[I];
//        Bank.processTransactions(FileName);
//    }
    accountTest();
    fundTest();
    accountTreeTest();
    bankTest();

    cout << endl << "Total: " << endl
    << "\t" << TestsPassed << "/" << Tests << endl;
//    cout << "Done" << endl;
    return 0;
}