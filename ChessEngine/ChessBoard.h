/**
 * @file ChessBoard.cpp
 *
 * Implementation of the ChessBoard struct for representing a chessboard and its state.
 * This file contains the member function implementations for the ChessBoard struct.
 *
 * @author Martin N
 * @date 09/2023
 */

#pragma once
#include <cstdint>
#include <vector>
#include <string>

/**
 * @struct ChessBoard
 *
 * Represents a chessboard and its state, including the positions of chess pieces.
 */
struct ChessBoard
{
    /**
     * Enumeration representing different types of chess pieces.
     */
    enum class PieceType {
        EMPTY = -1,
        WHITE_PAWN,
        WHITE_ROOK,
        WHITE_KNIGHT,
        WHITE_BISHOP,
        WHITE_QUEEN,
        WHITE_KING,
        BLACK_PAWN,
        BLACK_ROOK,
        BLACK_KNIGHT,
        BLACK_BISHOP,
        BLACK_QUEEN,
        BLACK_KING
    };

    /* The white piece positions */
    std::uint64_t whitePawns = 0;
    std::uint64_t whiteRooks = 0;
    std::uint64_t whiteKnights = 0;
    std::uint64_t whiteBishops = 0;
    std::uint64_t whiteQueens = 0;
    std::uint64_t whiteKing = 0;

    /* The black piece positions */
    std::uint64_t blackPawns = 0;
    std::uint64_t blackRooks = 0;
    std::uint64_t blackKnights = 0;
    std::uint64_t blackBishops = 0;
    std::uint64_t blackQueens = 0;
    std::uint64_t blackKing = 0;

    /**
     * Get the combined bitboard of all white pieces.
     *
     * @return The combined bitboard representing all white pieces.
     */
    std::uint64_t getAllWhitePieces() const;

    /**
     * Get the combined bitboard of all black pieces.
     *
     * @return The combined bitboard representing all black pieces.
     */
    std::uint64_t getAllBlackPieces() const;

    /**
     * Get the combined bitboard of all pieces (both white and black).
     *
     * @return The combined bitboard representing all pieces.
     */
    std::uint64_t getAllPieces() const;

    /**
     * Create a deep copy of the current chessboard.
     *
     * @return A pointer to a new ChessBoard struct containing the copied state.
     */
    ChessBoard* copy() const;

    /**
     * A boolean indicating the current player (true for white, false for black).
     */
    bool currPlayer = true;

    /**
     * Clear the chessboard, setting all positions to EMPTY.
     */
    void clearBoard();

    /**
     * Make a move on the chessboard from one square to another.
     *
     * @param from The starting square (source) of the move.
     * @param to The target square (destination) of the move.
     */
    void makeMove(std::uint8_t from, std::uint8_t to);

    /**
     * Set a specific piece on the chessboard at the given rank and file.
     *
     * @param piece The type of chess piece to set.
     * @param rank The rank (row) where the piece should be placed.
     * @param file The file (column) where the piece should be placed.
     */
    void setPiece(ChessBoard::PieceType piece, int rank, int file);

    /**
     * Get the type of chess piece at a specific square on the chessboard.
     *
     * @param rank The rank (row) of the square to query.
     * @param file The file (column) of the square to query.
     * @return The PieceType enumeration representing the type of the piece at the specified square.
     */
    ChessBoard::PieceType getPieceTypeAtSquare(int rank, int file) const;

    /**
     * Convert a PieceType to its Forsyth-Edwards Notation (FEN) representation.
     *
     * @param piece The PieceType to convert to FEN notation.
     * @return The FEN representation of the PieceType.
     */
    static std::string pieceTypeToFen(PieceType piece);
};
