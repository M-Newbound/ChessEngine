# ChessEngine
A chess engine is a computer program that calculates and suggests the best moves in a game of chess, leveraging complex algorithms and databases to assess positions and make strategic decisions, enabling players to compete against it.

# How to Use

This chess engine accepts various commands through standard input and will repond via standard output. Below are the instructions on how to use this chess engine:

## Running the Chess Engine

Compile the Code:  
Before running the chess engine, ensure you have a C++ compiler installed on your system. This engine does not have any external dependencies, so no worries about installing third party libraries. Compile the code using a C++ compiler, such as g++. Navigate to the directory containing the code files in your terminal.

The first command will compile the code, the second line will run the engine.  
``` bash
g++ -o chess_engine main.cpp
./chess_engine
```

## Commands
The chess engine accepts various commands for interacting with the chessboard and evaluating the game. Here are the available commands:

### Display the Chessboard
``` bash
display
```
displays the current state of the chessboard by showing the chessboard with the pieces' positions.

## Engine-Specific Commands

### Moves Command
``` bash
moves [square] [color]
```
Lists all legal moves for a piece on the specified square and with the specified color.  
- square = square to analyse written by rank+file: eg: "e4"
- color = what color player to consider the move for, either "b" or "w" for black or white

### Move Command
``` bash
move [fromSquare] [toSquare] [display]
```
- fromSquare = square to move from : eg: "e4"
- toSquare = square to move to : eg: "f4"
- display = optional, "y" to display the board after the move.
  
Allows a player to make a move on the board. Provide the starting and ending square coordinates, and optionally, set display to "y" to show the updated board after the move.

### Check command
``` bash
check [color]
```
Checks if the specified color ("w" or "b") is in check.

mate [color]: Checks if the specified color is in checkmate.

piece [square]: Identifies the piece on the specified square.



## Universal Chess Interface (UCI) Commands

The engine supports some UCI (Universal Chess Interface) commands I am still hooking these into the engine so some commands are marked as, "in progress". However these commands are non vital to use the engine to it's fullest potentual.

### Position Command
``` bash
position [FEN|startpos] [moves]: 
```
moves are option, they are just sequentually processed after the startpos/fen. Eg, position startpos e2e4 will do the following:  Set the board to the starting position.  Make the move e2->e4 if valid


### Go Command
```` bash
go [color] [depth]
````
Initiates a search for the best move for the specified color and depth. Note: higher depths will produce better results, but take longer in the future I will fully convert this command to how it is defined in the UCI guidelines so that the engine choses the depth value.

### In Progress

uci: Initializes the UCI protocol.  

debug [on|off]: Enables or disables debugging mode.  

isready: Checks if the engine is ready to receive commands.  


##Playing a Game
Start the engine and setup the board with position.

Optionally issue go commands to let the engine calculate and suggest moves for white or black players.

Use the move command to make moves.

To display the current state of the chessboard at any point, use the display command.

Check for legal moves for a piece using the moves command.

Determine if a player is in check using the check command.

Check if a player is in checkmate using the mate command.


Example Usage
```bash
position startpos
display
go w 4
moves e2 w
move e2e4 y
move e7e5
check b
mate w
piece d1
move e2 e4 y
go w 5
go b 5
```

## Commands Summary

Ensure that you follow the correct syntax for each command.  
The engine will respond to commands with appropriate information or moves.  
You can integrate this chess engine into your own applications or use it for analysis and gameplay.  

Enjoy using the chess engine!

# Engine Overview
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
is it **fast**? And when we get to speak of Move Generation we will find the answer to be  **NO**. This is where we introduce Bitboards.

If we take a type of piece, lets say whitePawns, and now think of our 64squares chess board. Each of these squares can be in one of two states, it can be hasWhitePawn or noWhitePawn. So, instead of storing these states as entries to an array, why not create use a datatype with 64 bits of memory, for our purpose we will use uint64_t. Now our entire chessboard's state of whitePawns has been represented as a single 64 bit integer. On modern processors this allows for extremely fast manipulation.

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



### The Negamax Algorithm
Negamax/minimax is a vital algorithm in computer chess. Negamax is a variation of the minimax algorithm and both serve as the core of move selection in many many chess engines.

Core Aspects of Negamax:  
- **Recursive Searching**: Negamax explores potential positions on the chessboard by constructing a game tree. It recursively considers both the player's moves and their opponent's responses to thoes moves.
- **Evaluation Function**: At the leaf nodes of the tree, an evaluation function assigns a numerical value to each position, reflecting its desirability for the current player. Factors like piece values, board control, and king safety are often considered.
- **Minimizing Losses**: Negamax minimizes losses for the player whose turn it is. It selects moves that maximize the evaluation when it's their turn and minimizes it when it's the opponent's turn.

### Alpha-Beta Pruning
In small domain application (eg naughts and crosses) minimax can solve every possible move and guarentee the best move is played. In chess however the domain is much much bigger. Lets say that it's the opening game (white has 20 possible moves). At a depth of 2 (whites move then blacks move) we already must consider 20^2 leafs. So to boost efficiency, I've implemented alpha-beta pruning alongside Negamax. This optimization reduces the number of positions to evaluate, making the search faster without sacrificing accuracy.

**How Alpha-Beta Pruning Works:**  
- **Alpha**: This represents the minimum score the maximizing player is assured of having and starts at negative infinity.
- **Beta**: This represents the maximum score the minimizing player is assured of having and starts at positive infinity.
- **Pruning**: When a position's evaluation falls outside the alpha-beta bounds, we prune (discard) that branch. This is because we know the opponent can force a position with a better score, so further exploration isn't necessary.

Combining the Negamax algorithm with alpha-beta pruning is a powerful approach to position evaluation. It systematically explores the game tree while efficiently removing unproductive branches. This results in faster gameplay and provides a foundation for making smart, strategic moves in the intricate world of chess.

# Limitations

This project was undertaken out of personal interest and is in no way meant as a serious altneritive to the many advanced chess engines today. If I get around to it, in the future I would like to explore AI related board evaluation methods using CNNs and similiar. I also need to do some more intensive optimisation in the move generation, at current, when I test for check I am generating all of the opponent's attack squares and then &nding it with the current players king bitboard. While this will suffice for the time being, I would like to swap it for a more preformant method.

Currently the engine does not support special moves such as promotion, castling, and en passant. Adding these will be trivial, but for now I am keeping the move genration simple whilst I work on the command interface & the search/evaluation.

Currently there is no support for start/end game book moves. This causes the engine to act a bit wierd in the start and end games  -- this is mainly due to the evaluation function being in progress -- as theorecticlly a good evaluation function can find book moves by iteself.

