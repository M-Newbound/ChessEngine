#include "BoardEvaluation.h"
#include "MoveGeneration.h"
#include <cstdint>

std::uint8_t hammingDistance(std::uint64_t n) {
	std::uint8_t count = 0;
	while (n > 0) {
		if (n & 1) {
			count++;
		}
		n >>= 1; // Right shift to check the next bit
	}
	return count;
}

std::int32_t eval(const ChessBoard* board, bool color) {
	const std::uint64_t pawns = color ? board->whitePawns : board->blackPawns;
	const std::uint64_t rooks = color ? board->whiteRooks : board->blackRooks;
	const std::uint64_t knights = color ? board->whiteKnights : board->blackKnights;
	const std::uint64_t bishops = color ? board->whiteBishops : board->blackBishops;
	const std::uint64_t queens = color ? board->whiteQueens : board->blackQueens;

	const std::uint8_t numPawns = hammingDistance(pawns);
	const std::uint8_t numRook = hammingDistance(rooks);
	const std::uint8_t numKinghts = hammingDistance(knights);
	const std::uint8_t numBishops = hammingDistance(bishops);
	const std::uint8_t numQueens = hammingDistance(queens);

	if (MoveGeneration::generateLegalMoves(board, color).size() == 0) return std::numeric_limits<int32_t>::min();
	if (MoveGeneration::generateLegalMoves(board, !color).size() == 0) return std::numeric_limits<int32_t>::max();


	return numPawns * 100 + numRook * 500 + numKinghts * 300 + numBishops * 300 + numQueens * 800;
}


std::int32_t BoardEvaluation::getEvaluation(const ChessBoard* board)
{

	return eval(board, true) - eval(board, false);
}

ChessMove BoardEvaluation::getBestNextMove(const ChessBoard* board, std::uint8_t depth, bool isWhite)
{
	if (depth == 0 || BoardEvaluation::isCheckMate(board, true) || BoardEvaluation::isCheckMate(board, false)) {
		return ChessMove(0, 0, getEvaluation(board));
	}

	std::int32_t bestEval = isWhite ? std::numeric_limits<int32_t>::min() : std::numeric_limits<int32_t>::max();
	std::vector<ChessMove> moves = MoveGeneration::generateLegalMoves(board, isWhite);
	std::uint8_t bestFrom = 0;
	std::uint8_t bestTo = 0;

	for (ChessMove& move : moves) {
		ChessBoard* newBoard = board->copy();
		newBoard->makeMove(move.fromSquare, move.toSquare);
		int32_t eval = BoardEvaluation::minimax(newBoard, depth - 1, !isWhite);
		delete newBoard;

		if ((isWhite && eval > bestEval) || (!isWhite && eval < bestEval)) {
			bestEval = eval;
			bestFrom = move.fromSquare;
			bestTo = move.toSquare;
		}
	}

	return ChessMove(bestFrom, bestTo);
}



int32_t BoardEvaluation::minimax(const ChessBoard* board, uint8_t depth, bool isMaximizing)
{
	if (depth == 0 || BoardEvaluation::isCheckMate(board, true) || BoardEvaluation::isCheckMate(board, false)) {
		return getEvaluation(board);
	}

	std::int32_t bestEval = isMaximizing ? std::numeric_limits<int32_t>::min() : std::numeric_limits<int32_t>::max();
	std::vector<ChessMove> moves = MoveGeneration::generateLegalMoves(board, isMaximizing);

	for (const ChessMove& move : moves) {
		ChessBoard* newBoard = board->copy(); 
		newBoard->makeMove(move.fromSquare, move.toSquare);
		int32_t eval = minimax(newBoard, depth - 1, !isMaximizing);
		delete newBoard;

		if (isMaximizing) {
			bestEval = std::max(bestEval, eval);
		}
		else {
			bestEval = std::min(bestEval, eval);
		}
	}

	return bestEval;
}


bool BoardEvaluation::isCheckMate(const ChessBoard* board, bool forWhite)
{
	return MoveGeneration::generateLegalMoves(board, forWhite).size() == 0;
}
