
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

}

void accountTreeTest(){
    /*****************************************
     * Test single Node AccountTree
     *****************************************/
    auto* ExpectedAccount = new Account(1234, "Last", "First");
    AccountTree test0;
    test0.insert(ExpectedAccount);
    Account* RetrievedAccount;
    test0.retrieve(ExpectedAccount->getID(), RetrievedAccount);

    check(RetrievedAccount, ExpectedAccount);

    cout << "Single node AccountTree insert/retrieve" << endl;

    delete ExpectedAccount;
    ExpectedAccount = nullptr;
    test0.clear();

    /*****************************************
     * Test clear/insert/retrieve/<</outInOrder
     * for populated tree
     *****************************************/
    int IDs[8] = {3333, 1111, 2222, 4444, 1234, 5555, 6666, 2345};
    for (auto Id : IDs){
        test0.insert(new Account(Id, "", ""));
    }

    stringstream Expected;
    Expected << "1111 1234 2222 2345 3333 4444 5555 6666 ";

    stringstream Got;
    Got << test0;

    check(Got.str(), Expected.str());
    cout << "Populated tree InOrder to ostream" << endl;


}

void fundTest(){
    /*****************************************
     * Test single parameter constructor
     *****************************************/
    Fund test0("Money Market");

    stringstream Expected;
    Expected << "Money Market: $0";

    stringstream Got;
    Got << test0;

    check(Got.str(), Expected.str());
    cout << "Single parameter fund constructor" << endl;

}

void accountTest(){
    /*****************************************
     * Test account constructor
     *****************************************/
    Account test0(1234, "Last", "First");

    stringstream Expected;
    Expected << "1234: Last, First";

    stringstream Got;
    Got << test0;
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