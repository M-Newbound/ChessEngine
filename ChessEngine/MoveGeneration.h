#pragma once
#include <cstdint>
#include <vector>

#include "ChessBoard.h"


struct ChessMove {
    ChessMove(std::uint8_t from, std::uint8_t to, std::int32_t eval = 0) : fromSquare(from), toSquare(to) { eval = eval; };
	const std::uint8_t fromSquare;
	const std::uint8_t toSquare;
    std::int32_t eval = 0;

};

class MoveGeneration
{

public:
	static std::vector<ChessMove> generateColorsLegalMoves(const ChessBoard* board, bool forWhite);
    static std::vector<ChessMove> generateSquaresLegalMoves(const ChessBoard* board, std::uint8_t square, bool forWhite);

    static bool isCheck(const ChessBoard* board, bool forWhite);
    static std::uint64_t getDangerSquares(const ChessBoard* board, bool asWhite);


private:

    // Functions to generate moves for specific pieces
    static std::uint64_t pawnPseudoMovesBitboard  (const ChessBoard* board, const std::uint8_t* square, bool forWhite);
    static std::uint64_t knightPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite);
    static std::uint64_t bishopPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite);
    static std::uint64_t rookPseudoMovesBitboard  (const ChessBoard* board, const std::uint8_t* square, bool forWhite);
    static std::uint64_t queenPseudoMovesBitboard (const ChessBoard* board, const std::uint8_t* square, bool forWhite);
    static std::uint64_t kingPseudoMovesBitboard  (const ChessBoard* board, const std::uint8_t* square, bool forWhite);

};

