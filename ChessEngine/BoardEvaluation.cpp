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

	if (MoveGeneration::generateColorsLegalMoves(board, color).size() == 0) return std::numeric_limits<int32_t>::min();
	if (MoveGeneration::generateColorsLegalMoves(board, !color).size() == 0) return std::numeric_limits<int32_t>::max();


	return numPawns * 100 + numRook * 500 + numKinghts * 300 + numBishops * 300 + numQueens * 800;
}


std::int32_t BoardEvaluation::getEvaluation(const ChessBoard* board)
{

	return eval(board, true);
}

ChessMove BoardEvaluation::getBestNextMove(const ChessBoard* board, std::uint8_t depth, bool isWhite)
{
	std::pair<int, ChessMove> bestMove = negaMax(board, depth, isWhite);
	return bestMove.second;
}

std::pair<int, ChessMove> BoardEvaluation::negaMax(const ChessBoard* board, int depth, bool currPlayer)
{
	if (depth == 0) {
		return std::pair<int, ChessMove>(eval(board, currPlayer), ChessMove(0, 0));
	}

	if (isCheckMate(board, currPlayer)) {
		return std::pair<int, ChessMove>(BoardEvaluation::bestScore, ChessMove(0, 0));
	}

	ChessMove bestMove(0, 0);
	int bestScore = -BoardEvaluation::bestScore - 1;	// -1 just ensures you can move into a checkmated pos

	for (ChessMove move : MoveGeneration::generateColorsLegalMoves(board, currPlayer)) {
		ChessBoard newBoard = *board;
		newBoard.makeMove(move.fromSquare, move.toSquare);
		std::pair<int, ChessMove> results = negaMax(&newBoard, depth - 1, !currPlayer);

		results.first = -1 * results.first;

		if (results.first > bestScore) {
			bestScore = results.first;
			bestMove = move;
		}
	}

	return std::pair<int, ChessMove>(bestScore, bestMove);

}




















bool BoardEvaluation::isCheckMate(const ChessBoard* board, bool forWhite)
{
	return MoveGeneration::generateColorsLegalMoves(board, forWhite).size() == 0;
}
