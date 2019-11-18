# Skiplist

Goals: Working with dynamic arrays, pointers, doubly linked lists

For this assignment, you will write a Skip List data structure to store integers. 

When searching a Skip List, items can be found in O(log n) time. 
No duplicates are allowed.A SkipList can have multiple levels. 
SkipList of depth 1 is similar to a doubly linked list. All elements are inserted into a single doubly linked list.

When a SkipList has multiple levels, all elements are inserted at level = 0. 50% of those inserted at level = 0, 
are also inserted at level = 1. 50% of those inserted at level = 1 are also inserted at level = 2, and so on.

## Compile and Run

```
./simplecompile.sh
```


### Style Explanation
These options are defined in `.clang-tidy` file.

Perform all check except the following:

-fuchsia-* do not need specific checks for "fuchsia" a modular, capability-based operating system
- cppcoreguidelines-pro-bounds-array-to-pointer-decay: do not give warnings on assert
- google-build-using-namespace: for simplicity allow `using namespace std;`
- google-readability-braces-around-statements: allow compact code without `{`
- readability-braces-around-statements: allow compact code without `{`
This option is not available in CSS Linux lab under LLVM 3.8.1, but is needed on my PC when using 9.0.0
- hicpp-no-array-decay need to use assert
- modernize-use-trailing-return-type: not ready yet for `auto func() -> int` format
- hicpp-braces-around-statements: allow compact code without `{` (this option
- cppcoreguidelines-pro-bounds-pointer-arithmetic,
- llvm-header-guard: not using full directory name
- google-global-names-in-headers: for simplicity allow `using namespace std;`
- cppcoreguidelines-special-member-functions: not defining move operator
- hicpp-special-member-functions: not defining move operator
- cppcoreguidelines-owning-memory: not using gsl
## Clang-Tidy Warnings Generated
To begin with, the one warning remaining from Professor Pisan's test, and
 two the warnings from skiplist.cpp.
 
 Next we will explore the warnings generated from my tests in main.
#### 1. rand( ) is not actually random
The first warning is letting me know that if I hard-code the seed of the
 random number generator, I will get a predictable sequence of values. I am
  aware of this fact. Though in the real world, I may want the sequence of
   values given by rand() to actually be random, in this instance I need
    the values to be predictable to test the functionality of my code.
```shell script
/home/NETID/kezm/ass4-skiplist-starter-master/main.cpp:35:3: 
warning: random number generator seeded with a constant value will generate a 
predictable sequence of values [cert-msc32-c]
  srand(100);
  ^
```
The second warning is letting me know that my coin-toss is not that random
. It suggests I use a different random number generator. I know that these
 numbers are not completely random, but I need them to be somewhat
  predictable to test. Also, the specifications on canvas instructed me to
   write the coin-toss code the way I did.
```shell script
/home/NETID/kezm/ass4-skiplist-starter-master/skiplist.cpp:57:45: 
warning: rand() has limited randomness; 
use C++11 random library instead [cert-msc30-c]
bool SkipList::alsoHigher() const { return (rand() % 2) == 1; }
                                            ^
```

#### 2. Assigned value is _rubbish!_
The third warning let me know that there is a chance that by the time I
 give `NextNode` value, `CoinTossNexts[I]` may not have been initialized. I
  believe this is due to a static analysis which does not realize that some
   sequences of conditions can never happen. As I understand it, my code
    will never get to this line without having assigned `CoinTossNexts[I]`
     to be a real SNode stored in this SkipList.
   
   My reasoning is as follows: 
 * `CoinTossNexts[]` stores all the next greatest `SNode`'s in each level
  as `add(Data)` searches each level (top-down) to find the correct position 
   for the `Data` `ToAdd`.
   - Each elt of CoinTossNexts is initialized to nullptr at the start of add.
   - As long as no duplicates of `Data`'s value are found, CoinTossNexts's
    elts are always initialized to the next largest SNode compared to `Data`.
   - If a duplicate is found, the function returns false.
 * If no duplicates were found, CoinTossNexts is full of pointers to real
  SNodes in this SkipList.
 * If when we "toss the coin", we decide to duplicate the SNode above, 
   - NextNode points to SNode stored in CoinTossNexts.
   - `I` will only ever be 1 - (Depth - 1))
```shell script
/home/NETID/kezm/ass4-skiplist-starter-master/skiplist.cpp:91:26: 
warning: Assigned value is garbage or undefined [clang-analyzer-core.uninitialized.Assign]
                NextNode = CoinTossNexts[I];
                         ^
```
#### 3. Warnings in my tests
The following warnings were generated for my tests. They consist of issues
 with using array subscript instead of .at(), rand() not being that random
 , and Non-constant reference parameters. Although I can see why these are
  not great coding practice, I **do** know that the tests I wrote work as
   intended how they are written. Therefore, I will leave it.

```shell script
/home/NETID/kezm/ass4-skiplist-starter-master/main.cpp:23:27: warning: non-const reference parameter 'List', make it const or use a pointer [google-runtime-references]
void testRemove(SkipList& List, int Data){
                          ^
/home/NETID/kezm/ass4-skiplist-starter-master/main.cpp:35:24: warning: non-const reference parameter 'List', make it const or use a pointer [google-runtime-references]
void testAdd(SkipList& List){
                       ^
/home/NETID/kezm/ass4-skiplist-starter-master/main.cpp:36:5: warning: random number generator seeded with a constant value will generate a predictable sequence of values [cert-msc32-c]
    srand(1);
    ^
/home/NETID/kezm/ass4-skiplist-starter-master/main.cpp:38:5: warning: use range-based for loop instead [modernize-loop-convert]
    for (int I = 0; I < 10; I++) {
    ^   ~~~~~~~~~~~~~~~~~~~~~~~~
        (int & Value : Values)
/home/NETID/kezm/ass4-skiplist-starter-master/main.cpp:39:9: warning: do not use array subscript when the index is not an integer constant expression; use gsl::at() instead [cppcoreguidelines-pro-bounds-constant-array-index]
        Values[I] = rand() % 100;
        ^
/home/NETID/kezm/ass4-skiplist-starter-master/main.cpp:39:21: warning: rand() has limited randomness; use C++11 random library instead [cert-msc30-c]
        Values[I] = rand() % 100;
                    ^
/home/NETID/kezm/ass4-skiplist-starter-master/main.cpp:42:18: warning: do not use array subscript when the index is not an integer constant expression; use gsl::at() instead [cppcoreguidelines-pro-bounds-constant-array-index]
        List.add(Values[Test]);
                 ^
/home/NETID/kezm/ass4-skiplist-starter-master/main.cpp:43:36: warning: do not use array subscript when the index is not an integer constant expression; use gsl::at() instead [cppcoreguidelines-pro-bounds-constant-array-index]
        cout << isOK(List.contains(Values[Test]), true);
                                   ^
/home/NETID/kezm/ass4-skiplist-starter-master/main.cpp:44:49: warning: do not use array subscript when the index is not an integer constant expression; use gsl::at() instead [cppcoreguidelines-pro-bounds-constant-array-index]
        cout << "List contains added value " << Values[Test] << endl;
                                                ^
/home/NETID/kezm/ass4-skiplist-starter-master/main.cpp:47:26: warning: do not use array subscript when the index is not an integer constant expression; use gsl::at() instead [cppcoreguidelines-pro-bounds-constant-array-index]
        testRemove(List, Values[Data]);
                         ^

```


## Misc

This file is part of a repository located at
https://github.com/pisan342/ass3-maze-starter

