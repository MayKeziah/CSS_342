#include "accounttree.h"
// empty
AccountTree::AccountTree() : Root{nullptr}{}

// Delete all nodes in BST
AccountTree::~AccountTree() {
    clear();
}

// Inorder list of AccountID's
ostream &operator<<(ostream &Os, AccountTree &Tree) {
    Tree.outInOrder(Os, Tree.Root);
    return Os;
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

// Display information on all accounts
void AccountTree::display() const {
    outInOrder(cout, Root);
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
    if (Account->getID() == Current->NodeAccount->getID() ){
        return false;
    }
    else if(Account->getID() < Current->NodeAccount->getID() ){
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
// check if tree is empty
bool AccountTree::isEmpty() const {
  return Root == nullptr;
}

//recursively send AccountID's to ostream InOrder
void AccountTree::outInOrder(ostream &Os, AccountTree::Node *Current) const {
    if(Current->Left != nullptr){
        outInOrder(Os, Current->Left);
    }
    Os << *(Current->NodeAccount) << endl;
    if(Current->Right != nullptr){
        outInOrder(Os, Current->Right);
    }
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
    else if (Current->NodeAccount->getID() == AccountNumber){
        Account = Current->NodeAccount;
        return true;
    }
    if (AccountNumber < Current->NodeAccount->getID() ){
        return retreiveAccount(AccountNumber, Account, Current->Left);
    }
    return retreiveAccount(AccountNumber, Account, Current->Right);
}
