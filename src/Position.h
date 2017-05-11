#include <iostream>
#include <string>
#include <math.h>
using namespace std;

class Position {
public:
  Position();
  Position(int, int);
  string toString();
  bool equals(Position);
  Position toPosition(string);
  double distanceTo(Position);
  int x;
  int y;
private:
};
