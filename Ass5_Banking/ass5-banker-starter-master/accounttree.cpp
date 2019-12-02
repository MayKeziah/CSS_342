#include "accounttree.h"
// empty
AccountTree::AccountTree() : Root{nullptr}{}

// Delete all nodes in BST
AccountTree::~AccountTree() {
    clear();
}

// Insert new account
bool AccountTree::insert(Account *Account) {
    if (Account->getID() > 9999){
        return false;
    }
    if (isEmpty()){
        Root = new Node(Account); //TODO delete
        return true;
    }
    return insertAccount(Account, Root);
}

// Recursively insert new account
bool
AccountTree::insertAccount(Account *Account, AccountTree::Node *Current) {
    if (Account->getID() == Current->Account->getID() ){
        return false;
    }
    else if(Account->getID() < Current->Account->getID() ){
        if (Current->Left == nullptr){
            Current->Left = new Node(Account);
            return true;
        }
        return insertAccount(Account, Current->Left);
    }
    else if (Current->Right == nullptr){
        Current->Right = new Node(Account);
        return true;
    }
    return insertAccount(Account, Current->Right);
}

// Display information on all accounts
void AccountTree::display() const {
    outInOrder(cout, Root);
}

// delete all information in AccountTree
void AccountTree::clear() {
    if (!isEmpty()){
        clearTree(Root);
    }
}

// Recursively clear tree
void AccountTree::clearTree(AccountTree::Node *&Current) {
    if (Current == nullptr){
        return;
    }
    clearTree(Current->Left);
    clearTree(Current->Right);

    delete Current;
    Current = nullptr;
}

// check if tree is empty
bool AccountTree::isEmpty() const {
  return Root == nullptr;
}

// Retrieve account
// returns true if successful AND *Account points to account
bool AccountTree::retrieve(const int &AccountNumber, Account *&Account) const {
    return retreiveAccount(AccountNumber, Account, Root);
}

bool AccountTree::retreiveAccount
(const int &AccountNumber, Account *&Account, AccountTree::Node *Current)
const {
    if(Current == nullptr){
        Account = nullptr;
        return false;
    }
    else if (Current->Account->getID() == AccountNumber){
        Account = Current->Account;
        return true;
    }
    if (AccountNumber < Current->Account->getID() ){
        return retreiveAccount(AccountNumber, Account, Current->Left);
    }
    return retreiveAccount(AccountNumber, Account, Current->Right);
}

// Inorder list of AccountID's
ostream &operator<<(ostream &Os, AccountTree &Tree) {
    Tree.outInOrder(Os, Tree.Root);
    return Os;
}


//recursively send AccountID's to ostream InOrder
void AccountTree::outInOrder(ostream &Os, AccountTree::Node *Current) const {
    if(Current->Left != nullptr){
        outInOrder(Os, Current->Left);
    }
    Os << *(Current->Account) << endl;
    if(Current->Right != nullptr){
        outInOrder(Os, Current->Right);
    }
}
