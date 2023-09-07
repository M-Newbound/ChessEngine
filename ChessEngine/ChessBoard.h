#pragma once
#include <cstdint>
#include <vector>
#include <string>

struct ChessBoard
{
	enum class PieceType {
		EMPTY = 0,
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

	/* Commonly derived positions */
	std::uint64_t getAllWhitePieces() const;
	std::uint64_t getAllBlackPieces() const;
	std::uint64_t getAllPieces() const;
	
	ChessBoard* copy() const;
	
	void clearBoard();
	void makeMove(std::uint8_t from, std::uint8_t to);
	void setPiece(ChessBoard::PieceType piece, int rank, int file);
	ChessBoard::PieceType getPieceTypeAtSquare(int rank, int file) const;

	static std::string pieceTypeToFen(PieceType piece) {
		switch (piece) {
		case PieceType::EMPTY: return ".";
		case PieceType::WHITE_PAWN: return "P";
		case PieceType::WHITE_ROOK: return "R";
		case PieceType::WHITE_KNIGHT: return "N";
		case PieceType::WHITE_BISHOP: return "B";
		case PieceType::WHITE_QUEEN: return "Q";
		case PieceType::WHITE_KING: return "K";
		case PieceType::BLACK_PAWN: return "p";
		case PieceType::BLACK_ROOK: return "r";
		case PieceType::BLACK_KNIGHT: return "n";
		case PieceType::BLACK_BISHOP: return "b";
		case PieceType::BLACK_QUEEN: return "q";
		case PieceType::BLACK_KING: return "k";
		default: return "?"; // Handle unexpected input
		}
	}

};


