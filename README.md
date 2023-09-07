# ChessEngine
A chess engine is a computer program that calculates and suggests the best moves in a game of chess, leveraging complex algorithms and databases to assess positions and make strategic decisions, enabling players to compete against it.

## How to Use

## Overview
To create a functional chess engine, several key features need to be considered:

- Board Representation: Find a way to represent the current state of the chessboard in an effeicent manner.
- Move Generation: Develop a method to generate all **legal** moves for each piece on the board based on the rules of chess.
- Position Evaluation: Create an evaluation function that can assess the relative strength of each side's position.
- Search Algorithms: Implement a search over these legal moves to find the move which gives us the strongest position.

Lets explore these key ideas in a bit bore depth, and understand how we can create a chess engine of our own.

### Board Representation

When it comes to chess engines we will see time and time again the question of memory vesus speed, and with modern day hardware, the answer will nearly always be speed. 
I say this as it leads on to the big question, **how do we represent the chess board?**.

We know a chess board (8*8 squares) contains 6 unique pieces per side. Running some simple math (6 + 6 + NONE piece) we know that each square may have 13 states, so, 
what we could do is define a enum and simiply store our board in an array of these enums, with size 64. This certaintly looks like a nice way of going about things, however
is it **fast**? And when we get to speak of Move Generation we will find the answer to be a big **NO NO**. This is where we introduce Bitboards.

If we take a type of piece, lets say whitePawns, and now think of our 64*64 chess board. Each of these squares can be in one of two states, it can be hasWhitePawn or noWhitePawn. So, instead of storing these states as entries to an array, why not create use a datatype which represents 64 bits, uint64_t. Now our entire chessboard's state of whitePawns has been represented as a single 64 bit integer. On modern processors this allows for extremely fast manipulation.

So to answer the overarching question, we can represent our entire chess board as 12 bitboards, one per peice. 

### Move Generation

When it comes to move generation in a chess engine, efficiency is paramount. Generating moves at runtime can be a performance bottleneck, so we opt for clever techniques to streamline the process and achieve the speed necessary for a competitive chess program.

- **The Pitfall of Generating Moves at Runtime**
- Generating moves dynamically during gameplay can be inefficient. Calculating all possible moves for each piece on the board in real-time is a resource-intensive task. Instead, we aim for a more optimized approach to keep the game running smoothly.

- **Using Lookup Tables for King and Knight Moves**
-For certain pieces like the king and knight, we can precompute their possible moves and store them in lookup tables. This eliminates the need for complex calculations during gameplay. When a piece of these types needs to move, we simply consult the precomputed table, resulting in rapid and efficient move generation.

- **Leveraging Magic Bitboards for Sliding Pieces**
-Magic bitboards are a fascinating technique that accelerates move generation for sliding pieces, including rooks, bishops, and queens. They allow us to define lookup tables based on the blocking patterns of other pieces around a sliding piece.

-- **The Magic Behind Magic Bitboards**
-- Magic Numbers: Magic numbers serve as perfect hashing functions for each square and piece type. These numbers are carefully chosen so that when combined with the current occupancy of the board, they produce a unique index into a precomputed table.
--Efficient Move Generation: By using these magic numbers, we can determine all possible moves of a sliding piece with minimal computational effort. The magic bitboard approach greatly speeds up move generation for these complex pieces.

- **Bit Manipulation for Pawn Moves**
- Pawns, with their unique two-step initial move and capture mechanics, can efficiently generate moves using bit manipulation. By shifting and masking the pawn's position on a bitboard, we can quickly identify all valid pawn moves, making pawn move generation both speedy and elegant.
