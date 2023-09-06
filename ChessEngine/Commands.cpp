#include "Commands.h"
#include <iostream>

void commands::displayBoard(const ChessBoard* board)
{
    for (std::int8_t i = 63; i >= 0; i--)
    {
        if (i % 8 == 7) std::cout << " " << (i / 8) + 1 << " | ";

        char currSquare = '-';
        ChessBoard::PieceType piece = board->getPieceTypeAtSquare(i / 8, i % 8);

        if (piece == ChessBoard::PieceType::WHITE_PAWN) currSquare = 'P';
        else if (piece == ChessBoard::PieceType::WHITE_ROOK) currSquare = 'R';
        else if (piece == ChessBoard::PieceType::WHITE_KNIGHT) currSquare = 'N';
        else if (piece == ChessBoard::PieceType::WHITE_BISHOP) currSquare = 'B';
        else if (piece == ChessBoard::PieceType::WHITE_QUEEN) currSquare = 'Q';
        else if (piece == ChessBoard::PieceType::WHITE_KING) currSquare = 'K';
        else if (piece == ChessBoard::PieceType::BLACK_PAWN) currSquare = 'p';
        else if (piece == ChessBoard::PieceType::BLACK_ROOK) currSquare = 'r';
        else if (piece == ChessBoard::PieceType::BLACK_KNIGHT) currSquare = 'n';
        else if (piece == ChessBoard::PieceType::BLACK_BISHOP) currSquare = 'b';
        else if (piece == ChessBoard::PieceType::BLACK_QUEEN) currSquare = 'q';
        else if (piece == ChessBoard::PieceType::BLACK_KING) currSquare = 'k';

        std::cout << currSquare << ' ';
        if (i % 8 == 0) std::cout << std::endl;
    }

    std::cout << "   '----------------" << std::endl << "     a b c e d f g h" << std::endl;
}

void commands::uci_uci()
{
}

void commands::uci_debug(std::string mode)
{
}

void commands::uci_isready()
{
}

void commands::uci_newGame()
{
}

void commands::uci_position(std::string details)
{
}

bool commands::loadFEN(ChessBoard& board, const std::string& fen)
{
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
