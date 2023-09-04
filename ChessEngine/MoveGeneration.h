#pragma once
#include <cstdint>
#include <vector>

#include "ChessBoard.h"

struct ChessMove {
	std::uint8_t fromSquare;
	std::uint8_t toSquare;
};

class MoveGeneration
{

public:
	static std::vector<ChessMove> generateLegalMoves(const ChessBoard& board);


private:

    // Functions to generate moves for specific pieces
    static std::uint64_t pawnPseudoMovesBitboard  (ChessBoard& board, const std::uint8_t square, bool forWhite);
    static std::uint64_t knightPseudoMovesBitboard(ChessBoard& board, const std::uint8_t square, bool forWhite);
    static std::uint64_t bishopPseudoMovesBitboard(ChessBoard& board, const std::uint8_t square, bool forWhite);
    static std::uint64_t rookPseudoMovesBitboard  (ChessBoard& board, const std::uint8_t square, bool forWhite);
    static std::uint64_t queenPseudoMovesBitboard (ChessBoard& board, const std::uint8_t square, bool forWhite);
    static std::uint64_t kingPseudoMovesBitboard  (ChessBoard& board, const std::uint8_t square, bool forWhite);

};

