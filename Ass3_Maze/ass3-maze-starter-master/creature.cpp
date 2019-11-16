//
// Created by Yusuf Pisan on 4/18/18.
//

//#include <iostream>
#include "creature.h"
#include <bits/stdc++.h>


// Creature represented by row, col.
std::ostream &operator<<(std::ostream &Out, const Creature &Creature) {
    Out << Creature.Row << ", " << Creature.Col;
  return Out;
}

// Constructor: init creature at given coordinates
Creature::Creature(int Row, int Col) : Row(Row), Col(Col) {}

// Answers: You are at the exit, T/F?
bool Creature::atExit(const Maze* Maze) const {
  return (Maze->getExitColumn() == Col) && (Maze->getExitRow() == Row);
}

// Returns a string representing the series of directions
// to the exit in form of NSEW (north, south, east, west).
// If an Error occurs, it returns a string explaining the error.
string Creature::solve(Maze& Maze) {
    string Result;

   if (!inMaze(&Maze))  {
//        return "Solve Error: Creature outside of Maze.";
        Result = "Solve Error: Creature outside of Maze.";
    }
   else if (Maze.isWall(Row, Col)){
//        return "Solve Error: creature is in a wall.";
        Result = "Solve Error: creature is in a wall.";
    }
   else if (atExit(&Maze)){
        Maze.markAsPath(Row, Col);
//        return pathString();
        Result = pathString();
    }
   else{
        findPath(&Maze);
        if (!Path.empty() && Path.top().length() > 1){
            string Error = Path.top();
            Path.pop();
//            return Error;
            Result = Error;
        }
        else {
            return solve(Maze);
        }
    }
    return Result;
}

// Find the next possible step.
// If successful, update path with new step.
// If no steps are possible, backtrack one step.
void Creature::findPath(Maze* Maze) {
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
bool Creature::inMaze(Maze* Maze) {
    return (Row >= 0 && Row < Maze->getHeight()) && (Col >= 0 && Col < Maze->getWidth());
}

// Try to step north (up),
// If successful, Return "N", mark current position as path, update Row.
// Return "X" if unsuccessful.
string Creature::goNorth(Maze* Maze) {
    string Step;
    if (atExit(Maze)){
//        return "";
        Step = "";
    }
    else if (Maze->isClear(Row - 1, Col)){
        Maze->markAsPath(Row, Col);
        Row--;
//        return "N";
        Step = "N";
    }
    else{
//        return "X";
        Step = "X";
    }
    return Step;
}

// Try to step West (left),
// If successful, Return "W", mark current position as path, update Col.
// Returns "X" if unsuccessful.
string Creature::goWest(Maze* Maze) {
    string Step;
    if (atExit(Maze)){
//        return "";
        Step = "";
    }
    else if (Maze->isClear(Row, Col - 1)){
        Maze->markAsPath(Row, Col);
        Col--;
//        return "W";
        Step = "W";
    }
    else{
//        return "X";
        Step = "X";
    }
    return Step;
}

// Try to step south (down),
// If successful, Return "S", mark current position as path, update Row.
// Returns "X" if unsuccessful.
string Creature::goSouth(Maze* Maze) {
    string Step;
    if (atExit(Maze)){
//        return "";
        Step = "";
    }
    else if (Maze->isClear(Row + 1, Col)){
        Maze->markAsPath(Row, Col);
        Row++;
//        return "S";
        Step = "S";
    }
    else{
//        return "X";
        Step = "X";
    }
    return Step;
}

// Try to step East (right),
// If successful, Return "E", mark current position as path, update Col.
// Returns "X" if unsuccessful.
string Creature::goEast(Maze* Maze) {
    string Step;
    if (atExit(Maze)){
        Maze->markAsPath(Row, Col);
//        return "";
        Step = "";
    }
    else if (Maze->isClear(Row, Col + 1)){
        Maze->markAsPath(Row, Col);
        Col++;
//        return "E";
        Step = "E";
    }
    else{
//        return "X";
        Step = "X";
    }
    return Step;
}

// Mark current position as visited, but not path to exit.
// Take one step back
// If unsuccessful, pushes error to path.
void Creature::backTrack(Maze* Maze) {
        if (Path.empty()){
            Path.push("Backtrack Error: Stack empty, no available path.");
//            Path.push("toPop");
//            return;
        }
        else{
            Path.pop();
            if (Path.empty()){
                Path.push("Backtrack Error: No exit found.");
                Path.push("toPop");
//                return;
            }
            else if (Path.top() == "N"){
                Maze->markAsVisited(Row, Col);
                Row++;
            }
            else if (Path.top() == "W"){
                Maze->markAsVisited(Row, Col);
                Col++;
            }
            else if (Path.top() == "S"){
                Maze->markAsVisited(Row, Col);
                Row--;
            }
            else if (Path.top() == "E") {
                Maze->markAsVisited(Row, Col);
                Col--;
            }
            else {
                Path.push("Backtrack Error: stack contains invalid string.");
//                return;
                Path.push("toPop");
            }
            Path.pop();
        }
    }

// Empties path stack!
// Returns string representation of path steps by directions: NSEW.
string Creature::pathString() {
    string Steps;
    while(!Path.empty()){
        Steps += Path.top();
        Path.pop();
    }
    reverse(Steps.begin(), Steps.end());
    return Steps;
}
