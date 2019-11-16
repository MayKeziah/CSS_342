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
  return Out;
}

// Explicit constructor. Data is the value to store in the SNode
SkipList::SNode::SNode(int Data) {
    this->Data = Data;
}

// Explicit Constructor. Depth is the number of levels in list. Default = 1.
// Throws Invalid Argument Exception for Depths less than 1.
SkipList::SkipList(int Depth) {
    if (setDepth(Depth)){

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
}

// Duplicate this node in higher level
void SkipList::duplicate(SNode* OrigNode){
    OrigNode->UpLevel = new SNode(OrigNode->Data);
    OrigNode->UpLevel->DownLevel = OrigNode;
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
