//
// Created by Yusuf Pisan on 4/18/18.
//

#ifndef ASS3_CREATURE_H
#define ASS3_CREATURE_H

#include "maze.h"
#include <ostream>
#include <stack>


class Creature {
public:
    // Creature represented by row, col.
  friend ostream &operator<<(ostream &Out, const Creature &Creature);

private:
  int Row;
  int Col;
  stack<string> Path;

  // Mark current position as visited, but not path to exit.
  // Take one step back
  // If unsuccessful, pushes error to path.
  void backTrack(Maze* Maze);

  // Find the next possible step.
  // If successful, update path with new step.
  // If no steps are possible, backtrack one step.
  void findPath(Maze* Maze);

  // Answers: the creature is inside the maze, T/F?
  bool inMaze(Maze* Maze);

  // Empties path stack!
  // Returns string representation of path steps by directions: NSEW.
  string pathString();

public:

  // Constructor: init creature at given coordinates
  Creature(int Row, int Col);

  // Answers: You are at the exit, T/F?
  bool atExit(const Maze* Maze) const;

  // Try to step north (up),
  // If successful, Return "N", mark current position as path, update Row.
  // Return "X" if unsuccessful.
  string goNorth(Maze* Maze);

  // Try to step West (left),
  // If successful, Return "W", mark current position as path, update Col.
  // Returns "X" if unsuccessful.
  string goWest(Maze* Maze);

  // Try to step south (down),
  // If successful, Return "S", mark current position as path, update Row.
  // Returns "X" if unsuccessful.
  string goSouth(Maze* Maze);

  // Try to step East (right),
  // If successful, Return "E", mark current position as path, update Col.
  // Returns "X" if unsuccessful.
  string goEast(Maze* Maze);

  // Returns a string representing the series of directions
  // to the exit in form of NSEW (north, south, east, west).
  // If an Error occurs, it returns a string explaining the error.
  string solve(Maze& Maze);
};

#endif //ASS3_CREATURE_H
