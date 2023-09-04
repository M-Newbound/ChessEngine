#include "ChessBoard.h"

uint64_t ChessBoard::getAllWhitePieces()
{
    return whitePawns   |
           whiteRooks   |
           whiteBishops | 
           whiteKnights |
           whiteQueens  | 
           whiteKing;
}

uint64_t ChessBoard::getAllBlackPieces()
{
    return blackPawns   |
           blackRooks   |
           blackBishops |
           blackKnights |
           blackQueens  |
           blackKing;
}

uint64_t ChessBoard::getAllPieces()
{
    return getAllBlackPieces() | getAllWhitePieces();
}


