//
// Created by Yusuf Pisan on 4/18/18.
//

#include <fstream>
#include <iostream>
#include "maze.h"

using namespace std;

// Maze in current state with 'x', '*', '+', ' ' as possible characters.
ostream &operator<<(ostream &Out, const Maze &Maze) {
  for (int Row = 0; Row < Maze.Height; ++Row) {
    for (int Col = 0; Col < Maze.Width; ++Col) {
      Out << Maze.Field[Row][Col];
    }
    Out << endl;
  }
  Out << endl;
  return Out;
}

// Constructor init Maze with Maze filename
Maze::Maze(const string &FileName) {
  ifstream InFile;
  InFile.open(FileName);
  if (!InFile) {
    cout << "Unable to open file";
    exit(1); // terminate with error
  }
  InFile >> Width >> Height;
  InFile >> ExitRow >> ExitColumn;
  string Str;
  getline(InFile, Str);
  for (int Row = 0; Row < Height; ++Row) {
    for (int Col = 0; Col < Width; ++Col) {
      InFile.get(Field[Row][Col]);
//       cout << Row << ", " << Col << ": " << Field[Row][Col] << endl;
    }
    getline(InFile, Str);
  }
  InFile.close();
}

// Returns the row of the maze exit.
int Maze::getExitRow() const {
  return ExitRow;
}

// Returns the Col of the maze exit.
int Maze::getExitColumn() const {
  return ExitColumn;
}

// Answers: The given coordinates are clear, T/F?
bool Maze::isClear(int Row, int Col) const {
  return Field[Row][Col] == ' ';
}

// Marks the given location as "*", part of the path to the exit.
void Maze::markAsPath(int Row, int Col) {
  Field[Row][Col] = '*';
}

// Marks given location as "+" visited, but not a path to the exit.
void Maze::markAsVisited(int Row, int Col) {
  Field[Row][Col] = '+';
}

// returns height of maze
int Maze::getHeight() const{
    return Height;
}

// returns width of maze
int Maze::getWidth() const{
    return Width;
}

// Answers: the given coordinate is a wall "x", T/F?
bool Maze::isWall(int Row, int Col) const{
    return Field[Row][Col] == 'x';
}
