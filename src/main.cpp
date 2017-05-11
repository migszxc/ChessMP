#include <iostream>
#include "ChessPiece.h"
#include <windows.h>
#include <math.h>
using namespace std;
#ifndef WHITE
#define WHITE false
#endif
#ifndef BLACK
#define BLACK true
#endif

// returns true if king is in check
bool isKingInCheck(ChessPiece pieces[32], bool color);
// returns true if the piece in question can be captured
bool canBeCaptured(Position pos, ChessPiece pieces[32]);
// signum function
int signum(double any);
// returns true if there are any pieces in between pos 1 and pos 2 (exclusive)
bool inBetween(Position pos1, Position pos2, ChessPiece pieces[32]);
// clears the board to prepare for next frame update
void clearBoard(char board[][8]);
// updates the board with regards to pieces and their states and colors
void updateBoard(char board[][8], ChessPiece pieces[32]);
// prints the board
void printBoard(char board[][8]);
// initializes the initial positions of the pieces
void initializePieces(ChessPiece pieces[32]);
// moves the piece in origin to newPos if valid
bool movePiece(Position origin, Position newPos, ChessPiece pieces[32], bool turn, string *err);
// returns the piece at a certain position
ChessPiece* getPieceAt(Position pos, ChessPiece pieces[32]);

int main() {
  ChessPiece pieces[32];
  char board[8][8];
  string temp, temp2;
  clearBoard(board);
  initializePieces(pieces);
  bool turn = WHITE;
  string err;

  for (;;) {
    clearBoard(board);
    updateBoard(board, pieces);
    printBoard(board);
    cout << "Pick a piece to move: ";
    cin >> temp;
    cout << "Pick a place to move it: ";
    cin >> temp2;
    if (movePiece(Position().toPosition(temp),Position().toPosition(temp2),pieces,turn,&err)) {
      cout << "true" << endl;
      turn = !turn;
    } else {
      cout << "false: "<< err << endl;
    }
    err = "illegal move";
    cout << endl;
  }
}

// returns true if the king is in check
bool isKingInCheck(ChessPiece pieces[32], bool color) {
  ChessPiece *king = NULL;
  for (int i = 0; i < 32; i++) {
    if (pieces[i].getType() == 'K' && pieces[i].getColor() == color) {
      king = &pieces[i];
    }
  }
  return canBeCaptured(king->position, pieces);
}

// checks if the piece in a position can be captured by anything else
bool canBeCaptured(Position pos, ChessPiece pieces[32]){
  ChessPiece* toEat = getPieceAt(pos, pieces);
  if (toEat == NULL) return false;
  bool valid = false;

  for (int i = 0; i < 32; i ++) {
    char type = pieces[i].getType();
    bool color = pieces[i].getColor();
    double Dy = pieces[i].position.y - (*toEat).position.y;
    double Dx = pieces[i].position.x - (*toEat).position.x;
    double slope = Dy / Dx;
    if (Dx == 0) slope = INFINITY;
    Position origin = pieces[i].position;
    Position newPos = (*toEat).position;
    double distance = origin.distanceTo(newPos);
    if (pieces[i].isDead) return false;
    if (color != (*toEat).getColor()) {
      switch(type) {
        case 'Q':
        if ((slope == -1 || slope == 0 || slope == 1 || slope == INFINITY)
        && !inBetween(origin, newPos, pieces)) return true;
        break;
        case 'K':
        if ((slope == -1 || slope == 0 || slope == 1 || slope == INFINITY) && distance <= sqrt(2)) return true;
        break;
        case 'R':
        if ((slope == 0 || slope == INFINITY) && !inBetween(origin, newPos, pieces)) return true;
        break;
        case 'N':
        if ((slope == 2.0 || slope == 0.5 || slope == -2.0 || slope == -0.5) && distance <= sqrt(5)) return true;
        break;
        case 'B':
        if ((slope == 1 || slope == -1) && !inBetween(origin, newPos, pieces)) return true;
        break;
        case 'P':
        if (color == WHITE) {
          if (Dy == 1 && Dx == 0 && !toEat) {
            return true;
          } else if (Dy == 2 && Dx == 0 && origin.y == 1) {
            return true;
          } else if (toEat && abs(Dx) == 1 && Dy == 1) {
            return true;
          }
        } else if (color == BLACK) {
          if (Dy == -1 && Dx == 0 && !toEat) {
            return true;
          } else if (Dy == -2 && Dx == 0 && origin.y == 6) {
            return true;
          } else if (toEat && abs(Dx) == 1 && Dy == -1) {
            return true;
          }
        }
        break;
      }
      ///kdjf;lkaf
    }
  }
  return false;
}

int signum(double any) {
  if (any < 0) return -1;
  if (any == 0) return 0;
  if (any > 0) return 1;
}

bool inBetween(Position pos1, Position pos2, ChessPiece pieces[32]) {
  double Dx = pos1.x-pos2.x;
  double Dy = pos1.y-pos2.y;
  double pos2Slope = Dy / Dx;
  double distancePos2 = pos1.distanceTo(pos2);
  if (Dx == 0) pos2Slope = INFINITY;
  for (int i = 0; i < 32; i ++) {
      if (!pieces[i].isDead){
        if (!pieces[i].position.equals(pos2) && !pieces[i].position.equals(pos1)) {
        double Dpx = pos1.x-pieces[i].position.x;
        double Dpy = pos1.y-pieces[i].position.y;
        double pieceSlope = Dpy / Dpx;
        double distancePiece = pos1.distanceTo(pieces[i].position);
        if (Dpx == 0) pieceSlope = INFINITY;
        if (pieceSlope == pos2Slope && distancePos2 > distancePiece && (signum(Dpx) == signum(Dx) &&
        signum(Dpy) == signum(Dy))) {
          /*cout << pieces[i].position.toString() << " is in between "
          << pos1.toString() << " and " << pos2.toString() << endl
          << "Dx = " << Dx << endl
          << "Dy = " << Dy << endl
          << "slope to pos2 is " << pos2Slope << endl
          << "Dpx = " << Dpx << endl
          << "Dpy = " << Dpy << endl
          << "slope to piece is " << pieceSlope << endl
          << "distancePos2 = " << distancePos2 << endl
          << "distancePiece = " << distancePiece << endl;*/
          return true;
        }
      }
    }
  }
  return false;
}

// returns a pointer pointing to the piece at a certain position
ChessPiece* getPieceAt(Position pos, ChessPiece pieces[32]) {
  for (int i = 0; i < 32; i ++) {
    if (pieces[i].position.equals(pos)) {
      if (pieces[i].isDead == false) {
        return &pieces[i];
      }
    }
  }
  return NULL;
}

// initialize the pieces in their default positions
void initializePieces(ChessPiece pieces[32]){
  for (int i = 0; i < 8; i++) {
    pieces[i] = ChessPiece('P', WHITE, Position(i, 1));
  }
  pieces[8] = ChessPiece('R', WHITE, Position(0,0));
  pieces[9] = ChessPiece('N', WHITE, Position(1,0));
  pieces[10] = ChessPiece('B', WHITE, Position(2,0));
  pieces[11] = ChessPiece('K', WHITE, Position(3,0));
  pieces[12] = ChessPiece('Q', WHITE, Position(4,0));
  pieces[13] = ChessPiece('B', WHITE, Position(5,0));
  pieces[14] = ChessPiece('N', WHITE, Position(6,0));
  pieces[15] = ChessPiece('R', WHITE, Position(7,0));
  for (int i = 0; i < 8; i++) {
    pieces[i+16] = ChessPiece('P', BLACK, Position(i, 6));
  }
  pieces[24] = ChessPiece('R', BLACK, Position(0,7));
  pieces[25] = ChessPiece('N', BLACK, Position(1,7));
  pieces[26] = ChessPiece('B', BLACK, Position(2,7));
  pieces[27] = ChessPiece('K', BLACK, Position(3,7));
  pieces[28] = ChessPiece('Q', BLACK, Position(4,7));
  pieces[29] = ChessPiece('B', BLACK, Position(5,7));
  pieces[30] = ChessPiece('N', BLACK, Position(6,7));
  pieces[31] = ChessPiece('R', BLACK, Position(7,7));
}

// returns true if the move is valid
// moves the piece at origin to newPos
bool movePiece(Position origin, Position newPos, ChessPiece pieces[32], bool turn, string *err) {
  // if the newposition is out of range of the board then it is an invalid move
  if (newPos.x < 0 || newPos.x > 7 || newPos.y < 0 || newPos.y > 7) {
    *err = "out of bounds exception";
    return false;
  }
  // find the piece in the origin position
  ChessPiece* piece = getPieceAt(origin, pieces);
  // find the piece in the new position (if it exists)
  ChessPiece* toEat = getPieceAt(newPos, pieces);
  // if there is no piece to move, invalid move
  if (piece == NULL) {
    *err = "no piece to move";
    return false;
  }
  char type = (*piece).getType();
  bool color = (*piece).getColor();
  double Dx = (newPos.x - (*piece).position.x);
  double Dy = (newPos.y - (*piece).position.y);
  //cout << "Dx = " << Dx << endl;
  //cout << "Dy = " << Dy << endl;
  double distance = origin.distanceTo(newPos);
  //cout << "distance = " << distance << endl;
  double slope;
  if (Dx != 0) {
    // change in y over change in x
    slope = Dy / Dx;
  } else {
    // undefined slope
    slope = INFINITY;
  }
  //cout << "Dy/Dx = " << slope << endl;
  bool valid = false;
  // evaluates move validity depending on type
  switch(type) {
    case 'Q':
    // queens are allowed the 8 directions with no distance limit
    if ((slope == -1 || slope == 0 || slope == 1 || slope == INFINITY)
    && !inBetween(origin, newPos, pieces)) valid = true;
    break;
    case 'K':
    // kings are allowed the 8 directions with a distance limit of sqrt(2) (for diagonal mvt)
    if ((slope == -1 || slope == 0 || slope == 1 || slope == INFINITY) && distance <= sqrt(2)) valid = true;
    break;
    case 'R':
    // rooks are allowed only vertical and horizontal movement with no distance limit
    if ((slope == 0 || slope == INFINITY) && !inBetween(origin, newPos, pieces)) valid = true;
    break;
    case 'N':
    // knights move with a slope of +/- 2 or +/- 0.5 with a distance limit of sqrt(5)
    if ((slope == 2.0 || slope == 0.5 || slope == -2.0 || slope == -0.5) && distance <= sqrt(5)) valid = true;
    break;
    case 'B':
    // bishops are only allowed diagonal movement with no distance limit
    if ((slope == 1 || slope == -1) && !inBetween(origin, newPos, pieces)) valid = true;
    break;
    case 'P':
    /*
    there are only 3 possible cases in which a pawn can move
    case 1: moving forward one space with nothing in front
    case 2: moving forward two spaces with nothing in front and only from
    original rank
    case 3: moving diagonal 1 space ONLY if there is something to be captured
    */
    if (color == WHITE) {
      if (Dy == 1 && Dx == 0 && !toEat) {
        valid = true;
      } else if (Dy == 2 && Dx == 0 && origin.y == 1) {
        valid = true;
      } else if (toEat && abs(Dx) == 1 && Dy == 1) {
        valid = true;
      }
    } else if (color == BLACK) {
      if (Dy == -1 && Dx == 0 && !toEat) {
        valid = true;
      } else if (Dy == -2 && Dx == 0 && origin.y == 6) {
        valid = true;
      } else if (toEat && abs(Dx) == 1 && Dy == -1) {
        valid = true;
      }
    }
    break;
  }
  // invalidate the move if it results in capturing its own teammate
  if (toEat) {
    if ((*toEat).getColor() == (*piece).getColor()) {
      *err = "cannot capture piece of the same color";
      valid = false;
    }
  }
  // invalidate the move if the piece color being moved is not the turn
  if (turn != (*piece).getColor()) {
    *err = "piece is not player's turn";
    valid = false;
  }
  // update the piece's position and KILL THE OTHER PIECE (if it exists lol)
  if (valid) {
    if (toEat) (*toEat).isDead = true;
    (*piece).position = newPos;
  }
  if (isKingInCheck(pieces, turn)) {
    if (toEat) toEat->isDead = false;
    piece->position = origin;
    valid = false;
    *err = "King is in check";
  }
  return valid;
}

// clears the board
void clearBoard(char board[][8]) {
  //cout << "clearing board" << endl;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      board[i][j] = ' ';
    }
  }
  //cout << "board cleared" << endl;
}

// updates the board according to piece position and state
void updateBoard(char board[][8], ChessPiece pieces[32]) {
  //cout << "updating board" <<endl;
  for (int i = 0; i < 32; i++) {
    if (!pieces[i].isDead)
    board[pieces[i].position.x][pieces[i].position.y] = pieces[i].getImage();
  }
  //cout << "board updated" << endl;
}

// prints the board
void printBoard(char board[][8]) {
  cout << " ";
  for (int x = 0; x < 8; x++ ){
    // prints abcdefgh at the top
    cout << " " << (char)(x+97);
  }
  cout << endl;
  for (int y = 7; y >= 0; y--) {
    // prints the row number at the left side
    cout  << y+1;
    for (int x = 0; x < 8; x++) {
      cout << "|";
      // prints the piece black
      if (board[x][y] >= 97 && board[x][y] <= 122) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
        cout << (char)(board[x][y]-32);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
      } else {
        // prints the piece white
        cout << board[x][y];
      }
    }
    // prints the row number on the right side
    cout << "|"<< y+1 << endl;
  }
  cout << " ";
  // prints abcdefgh at the bottom
  for (int x = 0; x < 8; x++ ){
    cout << " " << (char)(x+97);
  }
  cout << endl;
}
