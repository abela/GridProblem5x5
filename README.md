# GridProblem5x5

Here is the problem:
- 5x5 grid
— Up to 6 pieces in the grid
— Each piece occupies one place in the grid
— One of them is special
- All the pieces can be moved horizontally or vertically (not diagonally)
— The pieces will move in that direction until they hit another piece
— The pieces cannot move unless they will hit another piece. Any other move is invalid.
- The problem is solved when the special piece rests in the middle position of the grid

What should the program do?
Write a command line program that generates a random board that has a solution with a certain number of moves and no solutions with fewer moves.
The program should receive 2 arguments:
the number of moving pieces 
the minimum number of moves that the solution should have
It should output the initial board and the solution separated in a new line.

The initial board should consist of a space-separated list of (comma separated) pairs of x and y coordinates (0 based) where there is a piece:
The first element in the list is the position of the special piece.

The move sequence should consist of a space-separated list of (0 based) indexes in the initial board and move directions:
D(down) means a negative move in y.
L(left) means a negative move in x.
U(up) means a positive move in y.
R(right) means a positive move in x.

Example of a possible output when you request a board with 5 pieces (including the special one) and a solution of 4 moves (where there are no solutions with fewer than 4 moves):
> ./myApp 5 4
> 4,1 0,0 0,4 1,3 3,2
> 2D 0L 0U 0R

