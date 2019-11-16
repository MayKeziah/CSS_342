//
// Created by Yusuf Pisan on 4/26/18.
//

#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

// Insert a representation of this Skiplst into an ostream
ostream &operator<<(ostream &Out, const SkipList &SkipL) {
    string* Levels = new string[SkipL.Depth];
    for (int I = SkipL.Depth - 1; I > -1 ; I--) {
        Levels[I] += "L" + to_string(I) + ":\t"; // "L0:  "
    }
    SkipL.toString(Levels);
    return Out;
}

// Explicit constructor. Data is the value to store in the SNode
SkipList::SNode::SNode(int Data): Data{Data},
Prev{nullptr}, Next{nullptr}, UpLevel{nullptr}, DownLevel {nullptr}{}

// Convert SNode to string for output
string SkipList::SNode::toString() const {
    string Out;
    if (Data == INT_MIN || Data == INT_MAX){
        Out += "|";
    } else{
        Out += "(" + to_string(Data) + ")";
    }
    return Out;
}

// Explicit Constructor. Depth is the number of levels in list. Default = 1.
// Throws Invalid Argument Exception for Depths less than 1.
SkipList::SkipList(int Depth) {
    if (setDepth(Depth)){
        setGuards();
    } else{
        throw new invalid_argument(
                "SkipList Constructor: "
                "SkipList must have one or more levels.");
    }
}

// T/F: The value of this SNode is also stored up one level.
bool SkipList::alsoHigher() const { return false; }

// Add a new value to the SkipList. No duplicates. True if successful.
bool SkipList::add(int Data) {
  return true;
}

// Add the NewNode into the position before NextNode (Horizontally).
void SkipList::addBefore(SNode *NewNode, SNode *NextNode) {
    if (NextNode->Prev != nullptr){
        SNode* Tmp = NextNode->Prev;
        NewNode->Prev = Tmp;
        Tmp->Next = NewNode;
    }
    NextNode->Prev = NewNode;
    NewNode->Next = NextNode;
}

// Duplicate this node in higher level
SkipList::SNode* SkipList::duplicateAbove(SNode* OrigNode){
    OrigNode->UpLevel = new SNode(OrigNode->Data);
    SNode* NewDuplicate = OrigNode->UpLevel;
    NewDuplicate->DownLevel = OrigNode;

//    SNode* NextNode = OrigNode->Next->UpLevel;
//    addBefore(NewDuplicate, NextNode);
    return NewDuplicate;
}

// Safely sets the depth of the SkipList. True if successful.
bool SkipList::setDepth(int Depth){
    if(Depth > 0){
        this->Depth = Depth;
        return true;
    }
    return false;
}

// Creates array of Guard pointers and fills them with MIN and MAX SNodes.
void SkipList::setGuards(){
    FrontGuards = new SNode*[Depth];
    RearGuards  = new SNode*[Depth];
    FrontGuards[0] = new SNode(INT_MIN);
    RearGuards [0] = new SNode(INT_MAX);
    for (int I = 0; I < Depth - 1; I++){
        addBefore(FrontGuards[I], RearGuards[I]);
        FrontGuards[I + 1] = duplicateAbove(FrontGuards[I]);
        RearGuards [I + 1] = duplicateAbove(RearGuards [I]);
    }   addBefore(FrontGuards[Depth - 1], RearGuards[Depth - 1]);
}

// given a string array with matching depth, converts each level
// to a string and stores it in the associated string array index.
void SkipList::toString(string* Levels) const{
    SNode* Current = FrontGuards[0];
    while(Current != nullptr){
        Levels[0] += Current;
    }

}

// Delete memory on Heap
SkipList::~SkipList() {
  // need to delete individual nodes
}

// Remove a value from the SkipList. True if successful.
bool SkipList::remove(int Data) { return false; }

// T/F: The SkipList contains given Data value.
bool SkipList::contains(int Data) {
  return false;
}
