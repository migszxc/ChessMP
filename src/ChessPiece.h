#include <iostream>
#include <string>
#include "Position.h"
using namespace std;

class ChessPiece {
public:
  ChessPiece();
  ChessPiece(char, bool, Position);
  char getType();
  char getImage();
  bool getColor();
  bool isDead;
  bool promote(char);
  Position position;
private:
  bool doubleMove;
  char type;
  bool color;
};
