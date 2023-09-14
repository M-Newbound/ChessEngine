/**
 * @file BoardEvaluation.cpp
 *
 * Implementation of chessboard evaluation and move generation functions.
 * This file contains functions for evaluating the position of chess pieces on the board,
 * finding the best moves, and determining checkmate conditions.
 *
 * @author Martin N
 * @date 09/2023
 */


#include "BoardEvaluation.h"
#include "MoveGeneration.h"
#include <cstdint>

constexpr int PAWN_VALUE = 100;
constexpr int ROOK_VALUE = 500;
constexpr int KNIGHT_VALUE = 300;
constexpr int BISHOP_VALUE = 300;
constexpr int QUEEN_VALUE = 800;

/**
 * Calculate the Hamming distance (number of set bits) in a 64-bit integer.
 *
 * @param n The input 64-bit integer.
 * @return The number of set bits in the input integer.
 */
std::uint8_t hammingDistance(std::uint64_t n) {
	std::uint8_t count = 0;
	while (n > 0) {
		if (n & 1) {
			count++;
		}
		n >>= 1;
	}
	return count;
}


/**
 * Evaluate the chessboard position for a given player. Currently this evaluation
 * function simpily applies a piece value summation. This will be improved in the
 * future when I have more time.
 * 
 * @param board A pointer to the ChessBoard object representing the current board state.
 * @param color A boolean indicating the player's color (true for white, false for black).
 * @return The evaluation score for the player's position on the board.
 */
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

	// Check for a stalemate or checkmate
	if (MoveGeneration::generateColorsLegalMoves(board, color).size() == 0) return std::numeric_limits<int32_t>::min();
	if (MoveGeneration::generateColorsLegalMoves(board, !color).size() == 0) return std::numeric_limits<int32_t>::max();

	// Calculate and return the position evaluation score based on piece values.
	return numPawns * PAWN_VALUE + numRook * ROOK_VALUE + numKinghts * KNIGHT_VALUE + numBishops * BISHOP_VALUE + numQueens * QUEEN_VALUE;
}


/**
 * Get the evaluation score difference between two players for a given chessboard.
 *
 * @param board A pointer to the ChessBoard object representing the current board state.
 * @return The evaluation score difference between the two players.
 */
std::int32_t BoardEvaluation::getEvaluation(const ChessBoard* board)
{
	return eval(board, true) - eval(board, false);
}


/**
 * Find the best next move for a player on the given chessboard.
 *
 * @param board A pointer to the ChessBoard object representing the current board state.
 * @param depth The search depth for the move evaluation.
 * @param isWhite A boolean indicating the player's color (true for white, false for black).
 * @return The best next move for the player.
 */
ChessMove BoardEvaluation::getBestNextMove(const ChessBoard* board, std::uint8_t depth, bool isWhite)
{
	constexpr int alpha = std::numeric_limits<int>::min();
	constexpr int beta = std::numeric_limits<int>::max();

	std::pair<int, ChessMove> bestMove = negaMax(board, depth, alpha, beta, isWhite);
	return bestMove.second;
}


/**
 * NegaMax algorithm implementation for finding the best move and its score.
 *
 * @param board A pointer to the ChessBoard object representing the current board state.
 * @param depth The search depth for the move evaluation.
 * @param alpha The alpha value for alpha-beta pruning.
 * @param beta The beta value for alpha-beta pruning.
 * @param currPlayer A boolean indicating the current player's color (true for white, false for black).
 * @return A pair containing the best move's score and the best move itself.
 */
std::pair<int, ChessMove> BoardEvaluation::negaMax(const ChessBoard* board, int depth, int alpha, int beta, bool currPlayer) {
	if (depth == 0) {
		return std::pair<int, ChessMove>(eval(board, currPlayer), ChessMove(0, 0));
	}

	if (isCheckMate(board, currPlayer)) {
		return std::pair<int, ChessMove>(BoardEvaluation::bestScore, ChessMove(0, 0));
	}

	ChessMove bestMove(0, 0);
	int bestScore = -BoardEvaluation::bestScore - 1;

	for (ChessMove move : MoveGeneration::generateColorsLegalMoves(board, currPlayer)) {
		ChessBoard newBoard = *board;
		newBoard.makeMove(move.fromSquare, move.toSquare);
		std::pair<int, ChessMove> results = negaMax(&newBoard, depth - 1, -beta, -alpha, !currPlayer);

		results.first = -results.first;

		if (results.first > bestScore) {
			bestScore = results.first;
			bestMove = move;
		}

		alpha = std::max(alpha, bestScore);

		if (alpha >= beta) {
			// Prune remaining branches
			break;
		}
	}

	return std::pair<int, ChessMove>(bestScore, bestMove);
}


/**
 * Check if the current player is in checkmate.
 *
 * @param board A pointer to the ChessBoard object representing the current board state.
 * @param forWhite A boolean indicating the player's color (true for white, false for black).
 * @return True if the player is in checkmate, false otherwise.
 */
bool BoardEvaluation::isCheckMate(const ChessBoard* board, bool forWhite)
{
	return MoveGeneration::generateColorsLegalMoves(board, forWhite).size() == 0;
}
