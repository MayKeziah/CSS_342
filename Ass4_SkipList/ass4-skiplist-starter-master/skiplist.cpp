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
    auto* Levels = new string[SkipL.Depth];
//    SkipL.strings(Levels);
    SkipL.stringsByLvl(Levels);
    for (int I = SkipL.Depth - 1; I > -1 ; I--) {
        Out << Levels[I] << endl;
    }
    delete[] Levels;
    return Out;
}

// Explicit constructor. Data is the value to store in the SNode
SkipList::SNode::SNode(int Data): Data{Data},
Prev{nullptr}, Next{nullptr}, UpLevel{nullptr}, DownLevel {nullptr}{}

//// is this duplicated above?
//bool SkipList::SNode::isAbove() const{
//    return UpLevel != nullptr;
//}
//
//// is this duplicated below?
//bool SkipList::SNode::isBelow() const{
//    return DownLevel != nullptr;
//}

// Convert SNode to string for visual degugging output
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

// T/F: The value of this SNode is to be duplicated up one level.
bool SkipList::alsoHigher() const { return (rand() % 2) == 1; }

// Add a new value to the SkipList. No duplicates. True if successful.
bool SkipList::add(int Data) {
    int CurrLevel = Depth - 1;
    SNode* Current = FrontGuards[CurrLevel];
    SNode* CoinTossNexts[Depth];
    for (int I = Depth - 1; I > 0; I--){
        CoinTossNexts[I] = findNext(Current, Data);
        if (CoinTossNexts[I]->Data == Data){
            return false;
        }
        Current = CoinTossNexts[I]->DownLevel;
    }
    CoinTossNexts[0] = findNext(Current, Data);
    if (CoinTossNexts[0]->Data == Data){
        return false;
    }
    else{
        SNode* ToAdd = new SNode(Data);
        addBefore(ToAdd, CoinTossNexts[0]);
        for (int I = 1; I < Depth; I++){
            if (alsoHigher()){
                ToAdd = duplicateAbove(ToAdd);
                addBefore(ToAdd, CoinTossNexts[I]);;
            } else {
                return true;
            }
        }
        return true;

    }

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

// removes all added SNodes, leaving only the front and rear guards.
void SkipList::clear(){
    
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

// finds the next SNode if the data were added to this level
// If this level contains Data, it returns that node.
SkipList::SNode* SkipList::findNext(SNode* Start, int Data){
    if (Start == nullptr){
        return Start;
    }
    SNode* Current = Start;
    while (Data < Current->Data){
        Current = Current->Prev;
    }
    while (Data > Current->Data){
        Current = Current->Next;
    }
    return Current;
}

// removes the given node and all nodes below.
void SkipList::removeColumn(SNode* Top){
    SNode* Current = Top;
    SNode* Tmp = Current->DownLevel;
    while(Current != nullptr){
        Current->Prev->Next = Current->Next;
        Current->Next->Prev = Current->Prev;
        delete Current;
        Current = Tmp;
        if (Tmp != nullptr){
            Tmp = Tmp->DownLevel;
        }
    }

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
void SkipList::strings(string* Levels) const{
    for (int I = 0; I < Depth; I++){
        Levels[I] += "Level: " + to_string(I) + " -- ";
        SNode* Current = FrontGuards[I];
        while(Current != nullptr){
            Levels[I] += to_string(Current->Data) + ", ";
            Current = Current->Next;
        }
    }

}

// given a string array with matching depth, converts each level
// to a string and stores it in the associated string array index.
void SkipList::stringsByLvl(string* Levels) const{
    for (int I = 0; I < Depth; I++){
        SNode* Current = FrontGuards[I];
        Levels[I].insert(0, "L" + to_string(I) + ":\t");
        while(Current != RearGuards[I]){
            Levels[I] += Current->toString() + "<->";
            Current = Current->Next;
        } Levels[I] += Current->toString();
    }

}

// Delete memory on Heap
SkipList::~SkipList() {
  // need to delete individual nodes
}

// Remove a value from the SkipList. True if successful.
bool SkipList::remove(int Data) {
    SNode* Current= findNext(FrontGuards[Depth - 1], Data);
    for (int I = Depth - 1; I >= 0; I++){
        if(Current->Data == Data){
            removeColumn(Current);
            return true;
        }
        else{
            Current = findNext(Current->DownLevel, Data);
        }
    }
    return false;
}

// T/F: The SkipList contains given Data value.
bool SkipList::contains(int Data) {
    SNode* Current = findNext(FrontGuards[Depth - 1], Data);
    for (int I = Depth - 1; I > 0; I--){
        if (Current->Data == Data){
//            cout << endl << Data << " true at " << I << endl;
            return true;
        }
        Current = findNext(Current->DownLevel, Data);
    }
  return Current->Data == Data;
}
