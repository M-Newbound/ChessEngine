/**
 * @file ChessBoard.cpp
 *
 * Implementation of the ChessBoard struct for representing a chessboard and its state.
 * 
 * @author Martin N
 * @date 09/2023
 */

#include "ChessBoard.h"

 /**
  * Get the combined bitboard of all white pieces.
  *
  * @return The combined bitboard representing all white pieces.
  */
uint64_t ChessBoard::getAllWhitePieces() const
{
    return whitePawns |
        whiteRooks |
        whiteBishops |
        whiteKnights |
        whiteQueens |
        whiteKing;
}

/**
 * Get the combined bitboard of all black pieces.
 *
 * @return The combined bitboard representing all black pieces.
 */
uint64_t ChessBoard::getAllBlackPieces() const
{
    return blackPawns |
        blackRooks |
        blackBishops |
        blackKnights |
        blackQueens |
        blackKing;
}

/**
 * Get the combined bitboard of all pieces (both white and black).
 *
 * @return The combined bitboard representing all pieces.
 */
uint64_t ChessBoard::getAllPieces() const
{
    return getAllBlackPieces() | getAllWhitePieces();
}

/**
 * Create a deep copy of the current chessboard.
 *
 * @return A pointer to a new ChessBoard struct containing the copied state.
 */
ChessBoard* ChessBoard::copy() const
{
    ChessBoard* copyBoard = new ChessBoard;

    // Copy the state of white pieces
    copyBoard->whitePawns = whitePawns;
    copyBoard->whiteRooks = whiteRooks;
    copyBoard->whiteKnights = whiteKnights;
    copyBoard->whiteBishops = whiteBishops;
    copyBoard->whiteQueens = whiteQueens;
    copyBoard->whiteKing = whiteKing;

    // Copy the state of black pieces
    copyBoard->blackPawns = blackPawns;
    copyBoard->blackRooks = blackRooks;
    copyBoard->blackKnights = blackKnights;
    copyBoard->blackBishops = blackBishops;
    copyBoard->blackQueens = blackQueens;
    copyBoard->blackKing = blackKing;

    copyBoard->currPlayer = currPlayer;

    return copyBoard;
}

/**
 * Move a piece on a bitboard from one square to another.
 *
 * @param from The source square of the move.
 * @param to The destination square of the move.
 * @param bitboard The bitboard representing the piece positions.
 * @return True if the move was successful, false otherwise.
 */
bool movePiece(std::uint8_t from, std::uint8_t to, std::uint64_t& bitboard) {
    if (((bitboard >> from) & 1) != 1) return false;

    bitboard = bitboard & ~((std::uint64_t)1 << from);
    bitboard = bitboard | ((std::uint64_t)1 << to);
    return true;
}

/**
 * Clear the chessboard, setting all positions to EMPTY.
 */
void ChessBoard::clearBoard()
{
    whitePawns = 0;
    whiteRooks = 0;
    whiteKnights = 0;
    whiteBishops = 0;
    whiteQueens = 0;
    whiteKing = 0;
    blackPawns = 0;
    blackRooks = 0;
    blackKnights = 0;
    blackBishops = 0;
    blackQueens = 0;
    blackKing = 0;
}

/**
 * Make a move on the chessboard from one square to another.
 *
 * @param from The starting square (source) of the move.
 * @param to The target square (destination) of the move.
 */
void ChessBoard::makeMove(std::uint8_t from, std::uint8_t to)
{
    currPlayer = !currPlayer;

    whitePawns = whitePawns & ~((std::uint64_t)1 << to);
    whiteRooks = whiteRooks & ~((std::uint64_t)1 << to);
    whiteKnights = whiteKnights & ~((std::uint64_t)1 << to);
    whiteBishops = whiteBishops & ~((std::uint64_t)1 << to);
    whiteQueens = whiteQueens & ~((std::uint64_t)1 << to);

    blackPawns = blackPawns & ~((std::uint64_t)1 << to);
    blackRooks = blackRooks & ~((std::uint64_t)1 << to);
    blackKnights = blackKnights & ~((std::uint64_t)1 << to);
    blackBishops = blackBishops & ~((std::uint64_t)1 << to);
    blackQueens = blackQueens & ~((std::uint64_t)1 << to);

    if (movePiece(from, to, whitePawns)) return;
    if (movePiece(from, to, whiteRooks)) return;
    if (movePiece(from, to, whiteKnights)) return;
    if (movePiece(from, to, whiteBishops)) return;
    if (movePiece(from, to, whiteQueens)) return;
    if (movePiece(from, to, whiteKing)) return;

    if (movePiece(from, to, blackPawns)) return;
    if (movePiece(from, to, blackRooks)) return;
    if (movePiece(from, to, blackKnights)) return;
    if (movePiece(from, to, blackBishops)) return;
    if (movePiece(from, to, blackQueens)) return;
    if (movePiece(from, to, blackKing)) return;

}

/**
 * Set a specific piece on the chessboard at the given rank and file.
 *
 * @param piece The type of chess piece to set.
 * @param rank The rank (row) where the piece should be placed.
 * @param file The file (column) where the piece should be placed.
 */
void ChessBoard::setPiece(ChessBoard::PieceType piece, int rank, int file) {
    std::uint64_t bit = static_cast<std::uint64_t>(1) << (rank * 8 + file);

    if (piece == PieceType::WHITE_PAWN) whitePawns |= bit;
    else if (piece == PieceType::WHITE_ROOK) whiteRooks |= bit;
    else if (piece == PieceType::WHITE_KNIGHT) whiteKnights |= bit;
    else if (piece == PieceType::WHITE_BISHOP) whiteBishops |= bit;
    else if (piece == PieceType::WHITE_QUEEN) whiteQueens |= bit;
    else if (piece == PieceType::WHITE_KING) whiteKing |= bit;
    else if (piece == PieceType::BLACK_PAWN) blackPawns |= bit;
    else if (piece == PieceType::BLACK_ROOK) blackRooks |= bit;
    else if (piece == PieceType::BLACK_KNIGHT) blackKnights |= bit;
    else if (piece == PieceType::BLACK_BISHOP) blackBishops |= bit;
    else if (piece == PieceType::BLACK_QUEEN) blackQueens |= bit;
    else if (piece == PieceType::BLACK_KING) blackKing |= bit;
    else {
        // Invalid piece type or empty square
    }
}

/**
 * Get the type of chess piece at a specific square on the chessboard.
 *
 * @param rank The rank (row) of the square to query.
 * @param file The file (column) of the square to query.
 * @return The PieceType enumeration representing the type of the piece at the specified square.
 */
ChessBoard::PieceType ChessBoard::getPieceTypeAtSquare(int rank, int file) const {
    // Create a bitboard with a single 1 at the specified square
    std::uint64_t squareMask = 1ULL << (rank * 8 + file);

    // Check if the square is occupied by a white piece
    if (whitePawns & squareMask) return ChessBoard::PieceType::WHITE_PAWN;
    if (whiteRooks & squareMask) return ChessBoard::PieceType::WHITE_ROOK;
    if (whiteKnights & squareMask) return ChessBoard::PieceType::WHITE_KNIGHT;
    if (whiteBishops & squareMask) return ChessBoard::PieceType::WHITE_BISHOP;
    if (whiteQueens & squareMask) return ChessBoard::PieceType::WHITE_QUEEN;
    if (whiteKing & squareMask) return ChessBoard::PieceType::WHITE_KING;

    // Check if the square is occupied by a black piece
    if (blackPawns & squareMask) return ChessBoard::PieceType::BLACK_PAWN;
    if (blackRooks & squareMask) return ChessBoard::PieceType::BLACK_ROOK;
    if (blackKnights & squareMask) return ChessBoard::PieceType::BLACK_KNIGHT;
    if (blackBishops & squareMask) return ChessBoard::PieceType::BLACK_BISHOP;
    if (blackQueens & squareMask) return ChessBoard::PieceType::BLACK_QUEEN;
    if (blackKing & squareMask) return ChessBoard::PieceType::BLACK_KING;

    // If the square is empty, return EMPTY
    return ChessBoard::PieceType::EMPTY;
}

/**
 * Convert a PieceType to its Forsyth-Edwards Notation (FEN) representation.
 *
 * @param piece The PieceType to convert to FEN notation.
 * @return The FEN representation of the PieceType.
 */
std::string ChessBoard::pieceTypeToFen(PieceType piece) {
    switch (piece) {
    case PieceType::EMPTY: return ".";
    case PieceType::WHITE_PAWN: return "P";
    case PieceType::WHITE_ROOK: return "R";
    case PieceType::WHITE_KNIGHT: return "N";
    case PieceType::WHITE_BISHOP: return "B";
    case PieceType::WHITE_QUEEN: return "Q";
    case PieceType::WHITE_KING: return "K";
    case PieceType::BLACK_PAWN: return "p";
    case PieceType::BLACK_ROOK: return "r";
    case PieceType::BLACK_KNIGHT: return "n";
    case PieceType::BLACK_BISHOP: return "b";
    case PieceType::BLACK_QUEEN: return "q";
    case PieceType::BLACK_KING: return "k";
    default: return "?"; // Handle unexpected input
    }
}