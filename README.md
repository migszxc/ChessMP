# ChessMP

The goal is to create a single-player chess game. The player should be able to choose whether which side he/she will be playing. The program will act as the opponent. The game will not record nor use time limit, but potential draw cases should be observed.

## Accomplished:
	* Created a Position class
		stores position in integer values
		keeps in track positions in the form of chess algebraic notation (e.g. e4 h1 a2 etc.)
		has methods that:
			allow it to convert string-form to object-form and vice-versa
			calculate the distance to another position
	* Created a ChessPiece class
		stores information such as:
			piece type (King, Pawn, Rook, etc)
			piece color
			has been captured/or not
			position in the form of a Position object
		has methods that:
			return these information
			promote the piece( not yet implemented )
	* Prints the board
## Todo:
