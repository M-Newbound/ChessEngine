/**
 * @file BoardEvaluation.h
 *
 * Declaration of the BoardEvaluation class, which provides functions for evaluating
 * chessboard positions, finding the best next move, and determining checkmate conditions.
 *
 * This class encapsulates evaluation and move generation logic for a chess engine.
 *
 * @author Martin N
 * @date 09/2023
 */

#pragma once
#include "MoveGeneration.h"

 /**
  * @class BoardEvaluation
  *
  * The BoardEvaluation class encapsulates functions for evaluating chessboard positions,
  * finding the best next move, and determining checkmate conditions for a chess engine.
  */
class BoardEvaluation
{
public:
    /**
     * Get the evaluation score difference between two players for a given chessboard.
     *
     * @param board A pointer to the ChessBoard object representing the current board state.
     * @return The evaluation score difference between the two players.
     */
    static std::int32_t getEvaluation(const ChessBoard* board);

    /**
     * Find the best next move for a player on the given chessboard.
     *
     * @param board A pointer to the ChessBoard object representing the current board state.
     * @param depth The search depth for the move evaluation.
     * @param isWhite A boolean indicating the player's color (true for white, false for black).
     * @return The best next move for the player.
     */
    static ChessMove getBestNextMove(const ChessBoard* board, std::uint8_t depth, bool isWhite);

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
    static std::pair<int, ChessMove> negaMax(const ChessBoard* board, int depth, int alpha, int beta, bool currPlayer);

    /**
     * Check if the current player is in checkmate.
     *
     * @param board A pointer to the ChessBoard object representing the current board state.
     * @param forWhite A boolean indicating the player's color (true for white, false for black).
     * @return True if the player is in checkmate, false otherwise.
     */
    static bool isCheckMate(const ChessBoard* board, bool forWhite);

private:
    // Constant representing the best possible score
    static const int bestScore = 1000000;
};
