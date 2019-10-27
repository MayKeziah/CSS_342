//
// Created by E on 10/20/2019.
//

#include "Stack.h"
#include <cassert>

template <class ItemType>
Stack<ItemType>::Stack() : theTop(-1), canPush(true){}

template <class ItemType>
bool Stack<ItemType>::isEmpty(){
 return theTop < 0;
}
template <class ItemType>
bool Stack<ItemType>::push(const ItemType& newEntry){
    if (theTop == DEFAULT_CAPACITY - 1){
        canPush = false;
    }
    else {
        theStack[++theTop] = newEntry;
    }
    return canPush;
}

template <class ItemType>
bool Stack<ItemType>::pop() {
    if (isEmpty()){
        return false;
    }
    theTop--;
    canPush = true;
    return true;
}

template <class ItemType>
ItemType Stack<ItemType>::peek() const{
    assert(!isEmpty());
    return theStack[theTop];
}

template <class ItemType>
Stack<ItemType>::~Stack() = default;