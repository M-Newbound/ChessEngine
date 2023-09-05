#include "BoardEvaluation.h"
#include "MoveGeneration.h"
#include <cstdint>

uint8_t hammingDistance(uint64_t n) {
	uint8_t count = 0;
	while (n > 0) {
		if (n & 1) {
			count++;
		}
		n >>= 1; // Right shift to check the next bit
	}
	return count;
}

int32_t BoardEvaluation::getEvaluation(const ChessBoard* board, bool forWhite, bool andOther)
{
	const std::uint64_t pawns = forWhite ? board->whitePawns : board->blackPawns;
	const std::uint64_t rooks = forWhite ? board->whiteRooks : board->blackRooks;
	const std::uint64_t knights = forWhite ? board->whiteKnights : board->blackKnights;
	const std::uint64_t bishops = forWhite ? board->whiteBishops : board->blackBishops;
	const std::uint64_t queens = forWhite ? board->whiteQueens : board->blackQueens;
	
	const std::uint8_t numPawns = hammingDistance(pawns);
	const std::uint8_t numRook = hammingDistance(rooks);
	const std::uint8_t numKinghts = hammingDistance(knights);
	const std::uint8_t numBishops = hammingDistance(bishops);
	const std::uint8_t numQueens = hammingDistance(queens);

	int32_t other = andOther ? getEvaluation(board, !forWhite, false) : 0;

	if (MoveGeneration::generateLegalMoves(board, forWhite).size() == 0) return -2147483648;
	if (MoveGeneration::generateLegalMoves(board, !forWhite).size() == 0) return 2147483647;


	
	return numPawns * 100 + numRook * 500 + numKinghts * 300 + numBishops * 300 + numQueens * 800 - other;

}
