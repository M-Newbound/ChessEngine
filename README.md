# ChessEngine
A chess engine is a computer program that calculates and suggests the best moves in a game of chess, leveraging complex algorithms and databases to assess positions and make strategic decisions, enabling players to compete against it.

# How to Use

# Overview
To create a functional chess engine, several key features need to be considered:

- **Board Representation**: Find a way to represent the current state of the chessboard in an effeicent manner.
- **Move Generation**: Develop a method to generate all **legal** moves for each piece on the board based on the rules of chess.
- **Position Evaluation**: Create an evaluation function that can assess the relative strength of each side's position.
- **Search Algorithms**: Implement a search over these legal moves to find the move which gives us the strongest position.

Lets explore these key ideas in a bit bore depth, and understand how we can create a chess engine of our own.    

## Board Representation

When it comes to chess engines we will see time and time again the question of memory vesus speed, and with modern day hardware, the answer will nearly always be speed. 
I say this as it leads on to the big question, **how do we represent the chess board?**.

We know a chess board (8*8 squares) contains 6 unique pieces per side. Running some simple math (6 + 6 + NONE piece) we know that each square may have 13 states, so, 
what we could do is define a enum and simiply store our board in an array of these enums, with size 64. This certaintly looks like a nice way of going about things, however
is it **fast**? And when we get to speak of Move Generation we will find the answer to be a big **NO NO**. This is where we introduce Bitboards.

If we take a type of piece, lets say whitePawns, and now think of our 64*64 chess board. Each of these squares can be in one of two states, it can be hasWhitePawn or noWhitePawn. So, instead of storing these states as entries to an array, why not create use a datatype which represents 64 bits, uint64_t. Now our entire chessboard's state of whitePawns has been represented as a single 64 bit integer. On modern processors this allows for extremely fast manipulation.

So to answer the overarching question, we can represent our entire chess board as 12 bitboards, one per peice.     

## Move Generation

When it comes to move generation in a chess engine, efficiency is paramount. Generating moves at runtime can be a performance bottleneck, so we opt for clever techniques to streamline the process and achieve the speed necessary for a competitive chess program.

#### **The Pitfall of Generating Moves at Runtime**
- Generating moves dynamically during gameplay can be inefficient. Calculating all possible moves for each piece on the board in real-time is a resource-intensive task. Instead, we aim for a more optimized approach to keep the game running smoothly.

#### **Using Lookup Tables for King and Knight Moves**
- For certain pieces like the king and knight, we can precompute their possible moves and store them in lookup tables. This eliminates the need for complex calculations during gameplay. When a piece of these types needs to move, we simply consult the precomputed table, resulting in rapid and efficient move generation.

#### **Leveraging Magic Bitboards for Sliding Pieces**
- Magic bitboards are a fascinating technique that accelerates move generation for sliding pieces, including rooks, bishops, and queens. They allow us to define lookup tables based on the blocking patterns of other pieces around a sliding piece.
- I will discuss these in depth shortly, but for now, just trust me, they are magic.

#### **Bit Manipulation for Pawn Moves**
- Pawns, with their unique two-step initial move and capture mechanics, can efficiently generate moves using bit manipulation. By shifting and masking the pawn's position on a bitboard, we can quickly identify all valid pawn moves, making pawn move generation both speedy and elegant.    

## Magic Bitboards
Magic bitboards are a powerful technique used in chess engines to efficiently generate moves for sliding pieces, such as rooks, bishops, and queens. At their core, magic bitboards are a form of precomputed lookup table. However, their true genius lies in their ability to provide rapid move generation without requiring an enormous amount of memory.

**The Challenge of Storing All Possible Move Patterns**  
To appreciate the significance of magic numbers in magic bitboards, it's essential to understand the challenge we face. Sliding pieces can have a multitude of potential move patterns based on their position and the positions of blocking pieces. Storing every possible move pattern for each square and blocking configuration would demand an impractical amount of memory.

**Introducing Magic Numbers**  
Magic numbers are the key to solving this problem. They serve as the defining components of a perfect hashing function for each blocking pattern. These magic numbers are carefully chosen to ensure that, for any given square on the chessboard, every possible blocking pattern that can occur at that square has a unique hash or index. Magic numbers can be any 64bit int, and so the method I used to find them was just random trial an error.

maigic_index = f(blocking_pieces_bitboard, magic_number, shift_degree) = (blocking_pieces_bitboard * magic_number) >> shift_degree

**Simplifying Move Generation with Magic Numbers    
Now, let's break down how magic numbers streamline move generation:**    

- Blocker Mask: First, we obtain the blocker mask for a specific square. This mask indicates the positions of all blocking pieces relative to the sliding piece we want to move. It essentially marks the potential obstacles.

- Applying the Magic Formula: Here's where the magic happens. We apply the perfect hash formula using the chosen magic number and shift degree. This computation condenses the complex information of the blocking pattern into a single index.

- Accessing the Lookup Table: Finally, we use the result of our computation as an index to access a precomputed lookup table. This table provides us with all the possible move directions and target squares for the sliding piece, considering the specific blocking pattern.

In essence, magic numbers enable us to find all possible moves of a sliding piece with minimal computational effort. By cleverly mapping complex blocking patterns to unique indices, we optimize move generation and ensure that our chess engine operates at peak efficiency.

## Position Evalutation
in progress

## Search Algorithm



The Negamax Algorithm
Negamax/minimax is a vital algorithm in computer chess. Negamax is a variation of the minimax algorithm and both serve as the core of move selection in many many chess engines.

Core Aspects of Negamax:
Recursive Search: Negamax explores potential positions on the chessboard by constructing a game tree. It recursively considers both the player's moves and their opponent's responses to thoes moves.

Evaluation Function: At the leaf nodes of the tree, an evaluation function assigns a numerical value to each position, reflecting its desirability for the current player. Factors like piece values, board control, and king safety are often considered.

Minimizing Losses: Negamax minimizes losses for the player whose turn it is. It selects moves that maximize the evaluation when it's their turn and minimizes it when it's the opponent's turn.

Alpha-Beta Pruning
In small domain application (eg naughts and crosses) minimax can solve every possible move and guarentee the best move is played. In chess however the domain is much much bigger. Lets say that it's the opening game (white has 20 possible moves). At a depth of 2 (whites move then blacks move) we already must consider 20^2 leafs. So to boost efficiency, I've implemented alpha-beta pruning alongside Negamax. This optimization reduces the number of positions to evaluate, making the search faster without sacrificing accuracy.

How Alpha-Beta Pruning Works:
**Alpha**: This represents the minimum score the maximizing player is assured of having and starts at negative infinity.

**Beta**: This represents the maximum score the minimizing player is assured of having and starts at positive infinity.

**Pruning**: When a position's evaluation falls outside the alpha-beta bounds, we prune (discard) that branch. This is because we know the opponent can force a position with a better score, so further exploration isn't necessary.

Combining the Negamax algorithm with alpha-beta pruning is a powerful approach to position evaluation. It systematically explores the game tree while efficiently removing unproductive branches. This results in faster gameplay and provides a foundation for making smart, strategic moves in the intricate world of chess.

# Limitations
in progress
