
#ifndef ASS5_ACCOUNTTREE_H
#define ASS5_ACCOUNTTREE_H

#include "account.h"
#include <iostream>

class AccountTree {
    // Inorder list of AccountID's
    friend ostream& operator<<(ostream& Os, AccountTree& Tree);

private:

    class Node {
    public:
        explicit Node(Account *Account)
                : NodeAccount{Account}, Right{nullptr}, Left{nullptr} {};
        Account *NodeAccount;
        Node *Right;
        Node *Left;

        // Account ID
        friend ostream& operator<<(ostream& Os, Node& Node){
            Os << Node.NodeAccount->getID();
            return Os;
        };
    };

    Node *Root;

    // Recursively insert new account
    bool insertAccount(Account *Account, Node *Current);

    // Recursively search for account
    // returns true if successful AND *Account points to account
    bool retreiveAccount
    (const int &AccountNumber, Account *&Account, Node* Current) const;

    // Recursively clear tree
    void clearTree(Node*& Current);

    //recursively send AccountID's to ostream InOrder
    void outInOrder(ostream &Os, Node *Current) const;

public:

  // Create BST
  AccountTree();

  // Delete all nodes in BST
  ~AccountTree();

  // Insert new account
  bool insert(Account *Account);

  // Retrieve account
  // returns true if successful AND *Account points to account
  bool retrieve(const int &AccountNumber, Account *&Account) const;

  // Display information on all accounts
  void display() const;

  // delete all information in AccountTree
  void clear();

  // check if tree is empty
  bool isEmpty() const;
};
#endif // ASS5_ACCOUNTTREE_H
