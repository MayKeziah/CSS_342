#include "creature.h"
#include "maze.h"
#include <cassert>
#include <iostream>

// Visual test of maze.txt
void test() {
    cout << "--------------------- Original Maze ---------------------" << endl;
    Maze M("maze.txt");
    Creature C(4, 4);
    cout << "Path: " << C.solve(M) << endl;
    cout << M << endl;

    cout << "\nLocation two: " << endl;
    Maze M1("maze.txt");
    Creature C1(5, 15);
    cout << "Path: " << C1.solve(M1) << endl;
    cout << M1 << endl;
}

// Visual test of maze1.txt
void test1(){
    cout << "------------------------- Maze1 -------------------------" << endl;
    Maze M("maze1.txt");
    Creature C(4, 18);
    cout << "Path: " << C.solve(M) << endl;
    cout << M << endl;

    cout << "\nLocation two: " << endl;
    Maze M1("maze1.txt");
    Creature C1(3, 1);
    cout << "Path: " << C1.solve(M1) << endl;
    cout << M1 << endl;
}

// Visual test of maze2.txt
void test2(){
    cout << "------------------------- Maze2 -------------------------" << endl;
    Maze M("maze2.txt");
    Creature C(4, 18);
    cout << "Path: " << C.solve(M) << endl;
    cout << M << endl;

    cout << "\nLocation two: " << endl;
    Maze M1("maze2.txt");
    Creature C1(3, 1);
    cout << "Path: " << C1.solve(M1) << endl;
    cout << M1 << endl;
}

// Visual test of maze3.txt
void test3(){
    cout << "------------------------- Maze3 -------------------------" << endl;
    Maze M("maze3.txt");
    Creature C(4, 30);
    cout << "Path: " << C.solve(M) << endl;
    cout << M << endl;

    cout << "\nLocation two: " << endl;
    Maze M1("maze3.txt");
    Creature C1(4, 20);
    cout << "Path: " << C1.solve(M1) << endl;
    cout << M1 << endl;
}

// Tests that creature finds the path to the exit
// and correctly reports the directions to the exit.
void assertPath(){
    cout << "\nStarting AssertPath..." << endl;
    cout << "\t...testing that the creature follows expected path." << endl;
    Maze M("maze.txt");
    Creature C(4, 15);
    assert(C.solve(M) == "SEEENNNNN");
    cout << "...all Path assertions passed." << endl;
}

// Tests error Handling: out of bounds, in a wall, no exit found
void assertErrors(){
    cout << "Starting AssertErrors..." << endl;

    // Test for Creature out of bounds
    cout << "\t...testing for a creature out of bounds." << endl;
    Maze M("maze.txt");
    Creature C(-1, 0);
    assert(C.solve(M) == "Solve Error: Creature outside of Maze.");

    C = Creature(0, 30);
    assert(C.solve(M) == "Solve Error: Creature outside of Maze.");


    // Test for creature in a wall
    cout << "\t...testing for a creature inside a wall." << endl;
    C = Creature(0, 0);
    assert(C.solve(M) == "Solve Error: creature is in a wall.");


    // Test a trapped Creature
    cout << "\t...testing a creature with no exit." << endl;
    M = Maze("maze3.txt");
    C = Creature(1, 32);
    assert(C.solve(M) == "Backtrack Error: No exit found.");


    cout << "...all error assertions passed." << endl;
}

// Tests Creature and Maze using maze, maze1, maze2, and maze3.txt
int main() {
    test(); // success
    test1(); // as expected, consider optimizing
    test2(); // as expected
    test3(); // as expected
    assertErrors(); // Test: creature out of bounds, creature in wall, no exit
    assertPath(); // Test: Creature finds and correctly reports path to exit.

    cout << "\nDone!" << std::endl;
    return 0;
}