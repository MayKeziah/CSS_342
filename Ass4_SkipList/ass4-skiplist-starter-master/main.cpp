//
// Created by Yusuf Pisan on 4/26/18.
//

#include "skiplist.h"
#include <iostream>
#include <sstream>

using namespace std;

int TotalPassed = 0;
int TotalTests = 0;

template <typename T> string isOK(const T &got, const T &expected) {
  ++TotalTests;
  if (got == expected) {
    ++TotalPassed;
    return "OK: ";
  }
  cout << "    Got   " << got << "\n expected " << expected << endl;
  return "ERR: ";
}
void testRemove(SkipList& List, int Data){
    if (List.contains(Data)){
        cout << isOK(List.remove(Data), true);
        cout << "Able to remove existing value.\n\t";
        cout << isOK(List.contains(Data), false);
        cout << "Value successfully removed ";
    } else{
        cout << isOK(List.remove(Data), false);
        cout << "Can't remove a value that is not contained ";
    }
    cout << Data << endl;
}
void testAdd(SkipList& List){
    srand(1);
    int Values[10];
    for (int I = 0; I < 10; I++) {
        Values[I] = rand() % 100;
    }
    for (int Test = 9; Test >= 0; Test--){
        List.add(Values[Test]);
        cout << isOK(List.contains(Values[Test]), true);
        cout << "List contains added value " << Values[Test] << endl;
    }
    for (int Data = 9; Data >= 0; Data--){
        testRemove(List, Values[Data]);
    }
}
void testConstructor(int Depth){
    SkipList Empty(Depth);
    stringstream SList;
    stringstream SExpected;
    SList << Empty;
    for (int Level = Depth - 1; Level >= 0; Level--){
        SExpected << "Level: " << Level << " -- -2147483648, 2147483647, \n";
    }
    cout << isOK(SList.str(), SExpected.str());
    cout << "Empty List contains correct number of Guards." << endl;

    // Test add for list of depth 1
    testAdd(Empty);

}
void test02() {
  SkipList Skip(3);
  stringstream Ss;
  Ss << Skip;
  cout << isOK(Ss.str(), "Level: 2 -- -2147483648, 2147483647, \n"s +
                             "Level: 1 -- -2147483648, 2147483647, \n"s +
                             "Level: 0 -- -2147483648, 2147483647, \n"s)
       << "Empty SkipList of Depth=3" << endl;

  srand(100);
  Skip.add(10);
  Skip.add(30);
  Skip.add(5);
  Skip.add(25);
  Ss.str("");
  Ss << Skip;
  // Test for my Laptop
//  cout << isOK(Ss.str(),
//               "Level: 2 -- -2147483648, 10, 30, 2147483647, \n"s +
//                   "Level: 1 -- -2147483648, 5, 10, 30, 2147483647, \n"s +
//                   "Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"s)
//       << "SkipList of Depth=3 with 10, 30, 5, 25" << endl;

    // Test for linux computer csslab11.uwb.edu
    cout << isOK(Ss.str(),
                 "Level: 2 -- -2147483648, 30, 2147483647, \n"s +
                 "Level: 1 -- -2147483648, 30, 2147483647, \n"s +
                 "Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"s)
         << "SkipList of Depth=3 with 10, 30, 5, 25" << endl;
  cout << isOK(Skip.contains(10), true) << "Contains 10" << endl;
  cout << isOK(Skip.contains(30), true) << "Contains 30" << endl;
  cout << isOK(Skip.contains(71), false) << "Does not contain 71" << endl;
}

void test01() {
  SkipList Skip;
  stringstream Ss;
  Ss << Skip;
  cout << isOK(Ss.str(), "Level: 0 -- -2147483648, 2147483647, \n"s)
       << "Empty SkipList" << endl;
  Skip.add(10);
  Skip.add(30);
  Skip.add(5);
  Skip.add(25);
  Ss.str("");
  Ss << Skip;
  cout << isOK(Ss.str(),
               "Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"s)
       << "Added 10, 30, 5, 25," << endl;
}

int main() {
  cout << "Because of the random nature of SkipList, "
       << "the skip list levels may not match" << endl;
  // Set the random seed for easy debugging
  // NOLINTNEXTLINE
  srand(424242);
  test01();
  test02();
  for (int Depth = 1; Depth < 6; Depth++){
      testConstructor(Depth);
  }
  cout << "Passed: " << TotalPassed << "/" << TotalTests << endl;
  return 0;
}