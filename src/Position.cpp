#include <iostream>
#include <string>
#include "Position.h"
using namespace std;

/*
a class made to store and process coordinates for chess
*/

// empty constructor assumes position is at 0,0
Position::Position() {
  x = 0;
  y = 0;
}

// constructor with givens of abscissa and ordinate
Position::Position(int iX, int iY) {
  x = iX;
  y = iY;
}

// returns a string version of the position in terms of
// chess algebraic notation (e.g. e5, g3, a3)
string Position::toString() {
  string wew;
  wew += (char)(x + 97);
  wew += (char)(y + 49);
  return wew;
}

// returns a position given a string of format similar to one given above
Position Position::toPosition(string input) {
  int x = ((int)input[0]) - 97;
  int y = ((int)input[1]) - 49;
  return Position(x, y);
}

// compares if an inputted position is equal to this one
bool Position::equals(Position input) {
  if (input.x == x && input.y == y) return true;
  else return false;
}

// returns the distance from this to another given position
double Position::distanceTo(Position pos) {
  return sqrt(pow((x-pos.x),2) + pow((y-pos.y),2));
}
