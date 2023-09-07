#pragma once
#include "MoveGeneration.h"




class BoardEvaluation
{
public:
	static std::int32_t getEvaluation(const ChessBoard* board);

	static ChessMove getBestNextMove(const ChessBoard* board, std::uint8_t dempth, bool isWhite);
	
	static std::pair<int, ChessMove> negaMax(const ChessBoard* board, int depth, int alpha, int beta, bool currPlayer);

	static bool isCheckMate(const ChessBoard* board, bool forWhite);

private:
	static const int bestScore = 1000000;
};



