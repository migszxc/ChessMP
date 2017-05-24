# ChessMP

The goal is to create a single-player chess game. The player should be able to choose whether which side he/she will be playing. The program will act as the opponent. The game will not record nor use time limit, but potential draw cases should be observed.

# Accomplished
* Created a Position class
	* stores position in integer values
	* keeps in track positions in the form of chess algebraic notation (e.g. e4 h1 a2 etc.)
	* has methods that:
		* allow it to convert string-form to object-form and vice-versa
		* calculate the distance to another position
* Created a ChessPiece class
	* stores information such as:
		* piece type (King, Pawn, Rook, etc)
		* piece color
		* has been captured/or not
		* position in the form of a Position object
	* has methods that:
		* return these information
		* promote the piece
* Basic Game Logic
	* all proper movesets of each piece
	* does not allow a player to make a move that leaves their king in check
	* turn-switching
	* does not allow leaps unless a knight is in play
	* endgame state (stalemate or checkmate)
	* backtracking AI
* Prints the board
# Todo
* Major missing features
	* castling
	* en passant
* Minor missing features
	* A more a e s t h e t i c board
	* saving and loading game states

