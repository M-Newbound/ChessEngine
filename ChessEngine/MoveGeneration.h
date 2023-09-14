/**
 * @file MoveGeneration.h
 * @brief Header file for MoveGeneration class and related ChessMove struct.
 *
 * This file contains the declarations for the `ChessMove` struct, which represents
 * a chess move from one square to another, and the `MoveGeneration` class, which
 * provides methods for generating legal chess moves, checking for checks, and finding
 * danger squares.
 *
 * @author Martin N
 * @date 09/2023
 */

#pragma once
#include <cstdint>
#include <vector>

#include "ChessBoard.h"

/**
 * @struct ChessMove
 * Represents a chess move from one square to another.
 */
struct ChessMove {
public:
    /**
     * Constructor for creating a ChessMove object.
     * @param from The source square of the move.
     * @param to The destination square of the move.
     */
    ChessMove(std::uint8_t from, std::uint8_t to) : fromSquare(from), toSquare(to) {};

    /**
     * Copy constructor for creating a ChessMove object from another.
     * @param other The ChessMove object to copy from.
     */
    ChessMove(const ChessMove& other) : fromSquare(other.fromSquare), toSquare(other.toSquare) {}

    std::uint8_t fromSquare; ///< Source square of the move.
    std::uint8_t toSquare;   ///< Destination square of the move.
};

/**
 * @class MoveGeneration
 * Provides methods for generating legal chess moves, checking for checks, and finding danger squares.
 */
class MoveGeneration {
public:
    /**
     * Generates all legal moves for a specific color on the chessboard.
     * @param board Pointer to the ChessBoard object representing the current board state.
     * @param forWhite A boolean indicating whether to generate moves for white pieces (true) or black pieces (false).
     * @return A vector containing ChessMove objects representing legal moves.
     */
    static std::vector<ChessMove> generateColorsLegalMoves(const ChessBoard* board, bool forWhite);

    /**
     * Generates all legal moves for a piece located on a specific square on the chessboard.
     * @param board Pointer to the ChessBoard object representing the current board state.
     * @param square The square (0-63) on which the piece is located.
     * @param forWhite A boolean indicating whether to generate moves for white pieces (true) or black pieces (false).
     * @return A vector containing ChessMove objects representing legal moves for the piece on the specified square.
     */
    static std::vector<ChessMove> generateSquaresLegalMoves(const ChessBoard* board, std::uint8_t square, bool forWhite);

    /**
     * Checks if the specified color is in check on the current chessboard.
     * @param board Pointer to the ChessBoard object representing the current board state.
     * @param forWhite A boolean indicating whether to check for white king's check (true) or black king's check (false).
     * @return True if the specified color is in check, false otherwise.
     */
    static bool isCheck(const ChessBoard* board, bool forWhite);

    /**
     * Retrieves a bitboard representing squares that are under threat by the specified color.
     * @param board Pointer to the ChessBoard object representing the current board state.
     * @param asWhite A boolean indicating whether to find danger squares for white pieces (true) or black pieces (false).
     * @return A bitboard where set bits represent squares under threat by the specified color.
     */
    static std::uint64_t getDangerSquares(const ChessBoard* board, bool asWhite);

private:
    // Functions to generate pseudo moves for specific pieces
    static std::uint64_t pawnPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite);
    static std::uint64_t knightPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite);
    static std::uint64_t bishopPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite);
    static std::uint64_t rookPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite);
    static std::uint64_t queenPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite);
    static std::uint64_t kingPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite);
};
