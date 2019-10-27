//
// Created by Yusuf Pisan on 4/18/18.
//

#ifndef ASS3_MAZE_H
#define ASS3_MAZE_H

#include <ostream>

using namespace std;

enum CELL { CLEAR, WALL, PATH, VISITED };

class Maze {
  // Maze in current state with 'x', '*', '+', ' ' as possible characters.
  friend ostream &operator<<(ostream &Out, const Maze &Maze);
private:
  const static int MAX_SIZE = 100;
  char Field[MAX_SIZE][MAX_SIZE];
  int Width, Height;
  int ExitRow, ExitColumn;
public:
  // Constructor init Maze with Maze filename
  explicit Maze(const string &FileName);

  // Answers: The given coordinates are clear, T/F?
  bool isClear(int Row, int Col) const;

  // Marks the given location as "*", part of the path to the exit.
  void markAsPath(int Row, int Col);

  // Marks given location as "+" visited, but not a path to the exit.
  void markAsVisited(int Row, int Col);

  // Returns the row of the maze exit.
  int getExitRow() const;

  // Returns the Col of the maze exit.
  int getExitColumn() const;

  // returns height of maze
  int getHeight() const;

  // returns width of maze
  int getWidth() const;

  // Answers: the given coordinate is a wall "x", T/F?
  bool isWall(int Row, int Col) const;

};

#endif //ASS3_MAZE_H
