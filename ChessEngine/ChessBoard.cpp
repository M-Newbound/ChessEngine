#include "ChessBoard.h"

uint64_t ChessBoard::getAllWhitePieces() const
{
    return whitePawns   |
           whiteRooks   |
           whiteBishops | 
           whiteKnights |
           whiteQueens  | 
           whiteKing;
}

uint64_t ChessBoard::getAllBlackPieces() const
{
    return blackPawns   |
           blackRooks   |
           blackBishops |
           blackKnights |
           blackQueens  |
           blackKing;
}

uint64_t ChessBoard::getAllPieces() const
{
    return getAllBlackPieces() | getAllWhitePieces();
}

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

    return copyBoard;
}

bool movePiece(std::uint8_t from, std::uint8_t to, std::uint64_t& bitboard) {
    if (((bitboard >> from) & 1) != 1) return false;

    bitboard = bitboard & ~((std::uint64_t)1 << from);
    bitboard = bitboard | ((std::uint64_t)1 << to);
    return true;
}

void ChessBoard::makeMove(std::uint8_t from, std::uint8_t to)
{
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

void ChessBoard::setPiece(ChessBoard::PieceType piece, int rank, int file) {
    std::uint64_t bit = static_cast<std::uint64_t>(1) << (rank * 8 + file);

    if (piece == WHITE_PAWN) whitePawns |= bit;
    else if (piece == WHITE_ROOK) whiteRooks |= bit;
    else if (piece == WHITE_KNIGHT) whiteKnights |= bit;
    else if (piece == WHITE_BISHOP) whiteBishops |= bit;
    else if (piece == WHITE_QUEEN) whiteQueens |= bit;
    else if (piece == WHITE_KING) whiteKing |= bit;
    else if (piece == BLACK_PAWN) blackPawns |= bit;
    else if (piece == BLACK_ROOK) blackRooks |= bit;
    else if (piece == BLACK_KNIGHT) blackKnights |= bit;
    else if (piece == BLACK_BISHOP) blackBishops |= bit;
    else if (piece == BLACK_QUEEN) blackQueens |= bit;
    else if (piece == BLACK_KING) blackKing |= bit;
    else {
        // Invalid piece type or empty square
    }
}


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
