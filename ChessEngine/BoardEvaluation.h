#pragma once
#include "ChessBoard.h"

class BoardEvaluation
{
public:
	static int32_t getEvaluation(const ChessBoard* board, bool forWhite, bool andOther=true);

};



