# ChessEngine
A chess engine is a computer program that calculates and suggests the best moves in a game of chess, leveraging complex algorithms and databases to assess positions and make strategic decisions, enabling players to compete against it.



# Overview
To create a functional chess engine, several key features need to be considered:

Board Representation: Find a way to represent the current state of the chessboard in an effeicent manner.
Move Generation: Develop a method to generate all **legal** moves for each piece on the board based on the rules of chess.
Position Evaluation: Create an evaluation function that can assess the relative strength of each side's position.
Search Algorithms: Implement a search over these legal moves to find the move which gives us the strongest position.

Lets explore these key ideas in a bit bore depth, and understand how we can create a chess engine of our own.

## Board Representation

When it comes to chess engines we will see time and time again the question of memory vesus speed, and with modern day hardware, the answer will nearly always be speed. 
I say this as it leads on to the big question, **how do we represent the chess board?**.

We know a chess board (8*8 squares) contains 6 unique pieces per side. Running some simple math (6 + 6 + NONE piece) we know that each square may have 13 states, so, 
what we could do is define a enum and simiply store our board in an array of these enums, with size 64. This certaintly looks like a nice way of going about things, however
is it **fast**? And when we get to speak of Move Generation we will find the answer to be a big **NO NO**. This is where we introduce Bitboards.


