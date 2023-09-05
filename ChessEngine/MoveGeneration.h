#pragma once
#include <cstdint>
#include <vector>

#include "ChessBoard.h"


struct ChessMove {
    ChessMove(std::uint8_t from, std::uint8_t to) : fromSquare(from), toSquare(to) {};
	const std::uint8_t fromSquare;
	const std::uint8_t toSquare;

};

class MoveGeneration
{

public:
	static std::vector<ChessMove*> generateLegalMoves(ChessBoard& board, bool forWhite);
    static bool isCheck(ChessBoard& board, bool forWhite);
    static std::uint64_t getDangerSquares(ChessBoard& board, bool forWhite);


private:

    // Functions to generate moves for specific pieces
    static std::uint64_t pawnPseudoMovesBitboard  (ChessBoard& board, const std::uint8_t square, bool forWhite);
    static std::uint64_t knightPseudoMovesBitboard(ChessBoard& board, const std::uint8_t square, bool forWhite);
    static std::uint64_t bishopPseudoMovesBitboard(ChessBoard& board, const std::uint8_t square, bool forWhite);
    static std::uint64_t rookPseudoMovesBitboard  (ChessBoard& board, const std::uint8_t square, bool forWhite);
    static std::uint64_t queenPseudoMovesBitboard (ChessBoard& board, const std::uint8_t square, bool forWhite);
    static std::uint64_t kingPseudoMovesBitboard  (ChessBoard& board, const std::uint8_t square, bool forWhite);

};

