//
// Created by E on 10/20/2019.
//

#ifndef NON_CLASS_STACK_H
#define NON_CLASS_STACK_H

template <class ItemType>
class Stack {
private:
    static const int DEFAULT_CAPACITY = 100;
    ItemType theStack[DEFAULT_CAPACITY];
    int theTop;
    bool canPush;


public:
    Stack();
    virtual bool isEmpty();
    virtual bool push(const ItemType& newEntry);
    virtual bool pop();
    virtual ItemType peek() const;
    virtual ~Stack();

};


#endif //NON_CLASS_STACK_H
