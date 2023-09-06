#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include "ChessBoard.h"
#include "MoveGeneration.h"
#include "BoardEvaluation.h"

#include <chrono>

#include <bitset>


bool loadFEN(ChessBoard& board, const std::string& fen) {
    // Initialize variables to track position within the FEN string
    int rank = 7; // Start from rank 8 (index 7 in an array)
    int file = 7; // Start from file A (index 0 in an array)

    for (char fenChar : fen) {
        
        if (fenChar == '/') {
            // Move to the next rank
            rank--;
            file = 7;
            continue;
        }


        if (fenChar == ' ') {
            // Ignore spaces in FEN strings
            continue;
        }

        if (rank < 0 || file < 0) {
            // Invalid FEN string format
            return false;
        }
        
        if (isdigit(fenChar)) {
            // Empty squares
            int emptySquares = fenChar - '0';
            for (int i = 0; i < emptySquares; i++) {
                // Clear the square (assuming you have a clearSquare function)
                // clearSquare(board, rank, file);
                file--;
            }
        }
        else {
            // Non-empty squares (pieces)
            ChessBoard::PieceType piece;
            switch (fenChar) {
            case 'P': // White Pawn
                piece = ChessBoard::WHITE_PAWN;
                break;
            case 'R': // White Rook
                piece = ChessBoard::WHITE_ROOK;
                break;
            case 'N': // White Knight
                piece = ChessBoard::WHITE_KNIGHT;
                break;
            case 'B': // White Bishop
                piece = ChessBoard::WHITE_BISHOP;
                break;
            case 'Q': // White Queen
                piece = ChessBoard::WHITE_QUEEN;
                break;
            case 'K': // White King
                piece = ChessBoard::WHITE_KING;
                break;
            case 'p': // Black Pawn
                piece = ChessBoard::BLACK_PAWN;
                break;
            case 'r': // Black Rook
                piece = ChessBoard::BLACK_ROOK;
                break;
            case 'n': // Black Knight
                piece = ChessBoard::BLACK_KNIGHT;
                break;
            case 'b': // Black Bishop
                piece = ChessBoard::BLACK_BISHOP;
                break;
            case 'q': // Black Queen
                piece = ChessBoard::BLACK_QUEEN;
                break;
            case 'k': // Black King
                piece = ChessBoard::BLACK_KING;
                break;
            default:
                // Invalid character in FEN string
                return false;
            }
            board.setPiece(piece, rank, file);
            file--;
        }
    }

    return true;
}


void displayBoard(const ChessBoard* board) {

}

int main() {
    // Initialize a ChessBoard
    ChessBoard myBoard;

    // Example FEN string for starting position:
      std::string fenStart = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
      std::string fenExample = "rnbqkbnr / 1pp1pppp / 8 / p2p4 / 2B1P3 / 5N2 / PPPP1PPP / RNBQK2R";
      std::string fenBlackCheckmate = "3rkbnr/1p1bp3/1q1p3p/p5pQ/3n4/PPR5/5PPP/6K1";
      std::string fenBlackNearCheckmate = "3rkbnr/1p1bp3/1q1p3p/p5p1/3n4/PPR2Q2/5PPP/6K1";


    // Load the FEN string into the ChessBoard
    if (loadFEN(myBoard, fenExample)) {
        

        //std::vector<ChessMove> moves = MoveGeneration::generateLegalMoves(&myBoard, false);

        //for (ChessMove move : moves) {
         //   std::cout << "from " << unsigned(move.fromSquare) << " to " << unsigned(move.toSquare) << std::endl;
        //}


        int32_t eval = BoardEvaluation::getEvaluation(&myBoard);
        ChessMove bestMove = BoardEvaluation::getBestNextMove(&myBoard, 2, true);
        std::cout << eval << std::endl;
        std::cout << unsigned(bestMove.fromSquare) << std::endl;
        std::cout << unsigned(bestMove.toSquare) << std::endl;
        
    }
    else {
        std::cout << "Invalid FEN string format." << std::endl;
    }



    return 0;
}