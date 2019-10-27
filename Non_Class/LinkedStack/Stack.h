//
// Created by E on 10/20/2019.
//
#ifndef LINKEDSTACK_STACK_H
#define LINKEDSTACK_STACK_H
#include "PrecondViolatedExcept.cpp"


template <class ItemType>
class Stack {
private:
    struct Node{
        ItemType data;
        Node* next;
        Node(const ItemType& newData, Node* newNode = nullptr) : data(newData), next(newNode){}
    };
    bool clear();
    void copy(const Node& from);
    Node* topPtr;

public:
    Stack();
    Stack(const Stack& other);
    virtual bool isEmpty() const;
    virtual bool push(const ItemType& newEntry);
    virtual bool pop();
    virtual ItemType peek() const throw(PrecondViolatedExcept);
    virtual ~Stack();

};


#endif //LINKEDSTACK_STACK_H
