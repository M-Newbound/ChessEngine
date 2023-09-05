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
	static std::vector<ChessMove> generateLegalMoves(const ChessBoard* board, bool forWhite);
    static bool isCheck(const ChessBoard* board, bool forWhite);
    static std::uint64_t getDangerSquares(const ChessBoard* board, bool forWhite);


private:

    // Functions to generate moves for specific pieces
    static std::uint64_t pawnPseudoMovesBitboard  (const ChessBoard* board, const std::uint8_t* square, bool forWhite);
    static std::uint64_t knightPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite);
    static std::uint64_t bishopPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite);
    static std::uint64_t rookPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite);
    static std::uint64_t queenPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite);
    static std::uint64_t kingPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite);

};

