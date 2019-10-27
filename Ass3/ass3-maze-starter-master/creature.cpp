//
// Created by Yusuf Pisan on 4/18/18.
//

#include <iostream>
#include <bits/stdc++.h>
#include "creature.h"

// Creature represented by row, col.
std::ostream &operator<<(std::ostream &Out, const Creature &Creature) {
    Out << Creature.Row << ", " << Creature.Col; //TODO
  return Out;
}

// Constructor: init creature at given coordinates
Creature::Creature(int Row, int Col) : Row(Row), Col(Col) {}

// Answers: You are at the exit, T/F?
bool Creature::atExit(const Maze &Maze) const {
  return (Maze.getExitColumn() == Col) && (Maze.getExitRow() == Row);
}

// Returns a string representing the series of directions
// to the exit in form of NSEW (north, south, east, west).
// If an Error occurs, it returns a string explaining the error.
string Creature::solve(Maze &Maze) {
    if (!inMaze(Maze))  {
        return "Solve Error: Creature outside of Maze.";
    }
    if (Maze.isWall(Row, Col)){
        return "Solve Error: creature is in a wall.";
    }
    if (atExit(Maze)){
        Maze.markAsPath(Row, Col);
        return pathString();
    }
    else{
        findPath(Maze);
        if (!Path.empty() && Path.top().length() > 1){
            string error = Path.top();
            Path.pop();
            return error;
        }
        return solve(Maze);
    }
}

// Find the next possible step.
// If successful, update path with new step.
// If no steps are possible, backtrack one step.
void Creature::findPath(Maze& Maze) {
    Path.push(goNorth(Maze));
    if (Path.top() == "X"){
        Path.pop();
        Path.push(goWest(Maze));
        if (Path.top() == "X") {
            Path.pop();
            Path.push(goSouth(Maze));
            if (Path.top() == "X") {
                Path.pop();
                Path.push(goEast(Maze));
                if (Path.top() == "X") {
                    backTrack(Maze);

                }
            }
        }
    }
}

// Answers: the creature is inside the maze, T/F?
bool Creature::inMaze(Maze& Maze) {
    return (Row >= 0 && Row < Maze.getHeight()) && (Col >= 0 && Col < Maze.getWidth());
}

// Try to step north (up),
// If successful, Return "N", mark current position as path, update Row.
// Return "X" if unsuccessful.
string Creature::goNorth(Maze &Maze) {
    if (atExit(Maze)){
        return "";
    }
    else if (Maze.isClear(Row - 1, Col)){
        Maze.markAsPath(Row, Col);
        Row--;
        return "N";
    }
    else{
        return "X";
    }
}

// Try to step West (left),
// If successful, Return "W", mark current position as path, update Col.
// Returns "X" if unsuccessful.
string Creature::goWest(Maze &Maze) {
    if (atExit(Maze)){
        return "";
    }
    else if (Maze.isClear(Row, Col - 1)){
        Maze.markAsPath(Row, Col);
        Col--;
        return "W";
    }
    else{
        return "X";
    }
}

// Try to step south (down),
// If successful, Return "S", mark current position as path, update Row.
// Returns "X" if unsuccessful.
string Creature::goSouth(Maze &Maze) {
    if (atExit(Maze)){
        return "";
    }
    else if (Maze.isClear(Row + 1, Col)){
        Maze.markAsPath(Row, Col);
        Row++;
        return "S";
    }
    else{
        return "X";
    }
}

// Try to step East (right),
// If successful, Return "E", mark current position as path, update Col.
// Returns "X" if unsuccessful.
string Creature::goEast(Maze &Maze) {
    if (atExit(Maze)){
        Maze.markAsPath(Row, Col);
        return "";
    }
    else if (Maze.isClear(Row, Col + 1)){
        Maze.markAsPath(Row, Col);
        Col++;
        return "E";
    }
    else{
        return "X";
    }
}

// Mark current position as visited, but not path to exit.
// Take one step back
// If unsuccessful, pushes error to path.
void Creature::backTrack(Maze & Maze) {
        if (Path.empty()){
            Path.push("Backtrack Error: Stack empty, no available path.");
            return;
        }
        else{
            Path.pop();
            if (Path.empty()){
                Path.push("Backtrack Error: No exit found.");
                return;
            }
            if (Path.top() == "N"){
                Maze.markAsVisited(Row, Col);
                Row++;
            }
            else if (Path.top() == "W"){
                Maze.markAsVisited(Row, Col);
                Col++;
            }
            else if (Path.top() == "S"){
                Maze.markAsVisited(Row, Col);
                Row--;
            }
            else if (Path.top() == "E") {
                Maze.markAsVisited(Row, Col);
                Col--;
            }
            else {
                Path.push("Backtrack Error: stack contains invalid string.");
                return;
            }
            Path.pop();
        }
    }

// Empties path stack!
// Returns string representation of path steps by directions: NSEW.
string Creature::pathString() {
    string steps;
    while(!Path.empty()){
        steps += Path.top();
        Path.pop();
    }
    reverse(steps.begin(), steps.end());
    return steps;
}
