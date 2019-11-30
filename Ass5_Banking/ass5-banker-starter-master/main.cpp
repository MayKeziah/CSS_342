
#include "bank.h"
#include "Account.h"
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

void accountTreeTest(){

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

    cout << endl << "Total: " << endl
    << "\t" << TestsPassed << "/" << Tests << endl;
//    cout << "Done" << endl;
    return 0;
}