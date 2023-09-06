#pragma once
#include "MoveGeneration.h"




class BoardEvaluation
{
public:
	static std::int32_t getEvaluation(const ChessBoard* board);

	static ChessMove getBestNextMove(const ChessBoard* board, std::uint8_t dempth, bool isWhite);
	static std::int32_t minimax(const ChessBoard* board, uint8_t depth, bool isMaximizing);

	static bool isCheckMate(const ChessBoard* board, bool forWhite);

};



