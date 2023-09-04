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

void ChessBoard::loadFEN(std::string fenStr)
{
    uint64_t currPosition = (uint64_t)1 << 63;


}

std::string ChessBoard::getFEN()
{
    return std::string();
}
