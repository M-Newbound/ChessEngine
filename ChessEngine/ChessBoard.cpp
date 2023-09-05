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

void ChessBoard::setPiece(PieceType piece, int rank, int file)
{
    // Calculate the bit for the given rank and file (assuming rank 0 is the lowest rank)
    std::uint64_t bit = static_cast<std::uint64_t>(1) << (rank * 8 + file);

    // Depending on the piece type, set the appropriate bit on the board
    switch (piece) {
    case WHITE_PAWN:
        whitePawns |= bit;
        break;
    case WHITE_ROOK:
        whiteRooks |= bit;
        break;
    case WHITE_KNIGHT:
        whiteKnights |= bit;
        break;
    case WHITE_BISHOP:
        whiteBishops |= bit;
        break;
    case WHITE_QUEEN:
        whiteQueens |= bit;
        break;
    case WHITE_KING:
        whiteKing |= bit;
        break;
    case BLACK_PAWN:
        blackPawns |= bit;
        break;
    case BLACK_ROOK:
        blackRooks |= bit;
        break;
    case BLACK_KNIGHT:
        blackKnights |= bit;
        break;
    case BLACK_BISHOP:
        blackBishops |= bit;
        break;
    case BLACK_QUEEN:
        blackQueens |= bit;
        break;
    case BLACK_KING:
        blackKing |= bit;
        break;
    default:
        // Invalid piece type or empty square
        break;
    }
}
