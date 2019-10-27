//
// Created by E on 10/20/2019.
//

#include "Stack.h"
#include <cassert>

template <class ItemType>
Stack<ItemType>::Stack() : topPtr(nullptr){

}

template<class ItemType>
Stack<ItemType>::Stack(const Stack &other) {
    copy(other.topPtr);
}

template <class ItemType>
bool Stack<ItemType>::isEmpty() const{
    return topPtr == nullptr;
}

template <class ItemType>
bool Stack<ItemType>::push(const ItemType& newEntry){
    topPtr = new Node(newEntry, topPtr);
    return topPtr->data == newEntry;
}

template <class ItemType>
bool Stack<ItemType>::pop(){
    if(isEmpty()){
        return false;
    }
    Node* toDelete = topPtr;
    topPtr = topPtr->next;

    toDelete->next = nullptr;
    delete toDelete;
    toDelete = nullptr;

    return true;
}

template <class ItemType>
ItemType Stack<ItemType>::peek() const throw(PrecondViolatedExcept){
    if(isEmpty()){
        throw PrecondViolatedExcept("Linked Stack::peek() called on empty stack.\n");
    }
    else{
        return topPtr->data;
    }
}

template <class ItemType>
Stack<ItemType>::~Stack() {
    clear();
}

template<class ItemType>
bool Stack<ItemType>::clear() {
    while(!isEmpty()){
        pop();
    }
    return isEmpty();
}

template<class ItemType>
void Stack<ItemType>::copy(const Stack::Node& other) {
    if(!isEmpty()){
        clear();
    }
    if(other == nullptr) {
        topPtr = nullptr;
    }
    else {
        topPtr = new Node(other.data);
        Node* currentOther = other;
        Node* currentThis = topPtr;
        currentOther = currentOther->next;
        while(currentOther != nullptr){
            currentThis->next = new Node(currentOther->data);

            currentThis  = currentThis->next;
            currentOther = currentOther->next;
        }

    }
}
