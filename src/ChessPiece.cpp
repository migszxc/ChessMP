#include <iostream>
#include "ChessPiece.h"
using namespace std;
#ifndef WHITE
#define WHITE false
#endif
#ifndef BLACK
#define BLACK true
#endif

/*
a class made to store and process information relating to chess pieces
such as position, type, and color
*/

ChessPiece::ChessPiece() {
  type = 'F';
  color = WHITE;
  isDead = false;
}

ChessPiece::ChessPiece(char kind, bool colour, Position pos) {
  type = kind;
  color = colour;
  position = pos;
  isDead = false;
}

char ChessPiece::getType() {
  return type;
}

char ChessPiece::getImage() {
  if (color == WHITE) {
    return type;
  } else {
    return (char)(type+32);
  }
}

bool ChessPiece::getColor() {
  return color;
}
