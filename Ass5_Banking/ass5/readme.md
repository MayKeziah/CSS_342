#Banker Project: ass5
##Files
* **account (.h, .cpp)**: 
    * an account with 10 Fund accounts
    * manages transactions for its Fund accounts
* **accounttree (.h, .cpp)**
    * A binary tree of accounts sorted by a 4 digit account ID.
    * Manages adding, retreiving, and displaying the accounts.
* **bank (.h, .cpp)**
    * Takes a file containing formatted transaction requests
    * Processes each request in the order it comes.
    * the output is sent to the console in three stages:
       * First, any denied requests are listed and explained.
       * Second, any account history requests are displayed.
       * Third, all the balances for every bank account are displayed. 
* **fund (.h, .cpp)**
    * A sub-account
    * Controls withdrawals and deposits into this sub-account
    * Keeps a transaction log of successful transactions for this fund.
* **main.cpp**
    * Takes a list of file names
    * Sends each file name to bank class
    * Commented out tests were incremental unit tests.
* **BankTransIn.txt, BankTransIn2.txt**
    * Input files which are properly formatted for use in main and bank.
* **output.txt**
    * The output generated with the following script:
    ```shell script
  $ g++ -std=c++11 *.cpp -o banker
  $ ./banker BankTransIn.txt BankTransIn2.txt > output.txt 2>&1
  $ rm banker
    ```
##Warnings
The warnings generated for my class are for things like my includes being in
an order that is not preferred or that I initialize my member variables
in an order that is not preferred. At this point, I am more worried about 
generating working code than I am about alphabetical ordering. 

There are no memory leaks in my program. 