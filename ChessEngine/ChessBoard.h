#pragma once
#include <string>
#include <cstdint>


struct ChessBoard
{
	/* The white piece positions */
	std::uint64_t whitePawns;
	std::uint64_t whiteRooks;
	std::uint64_t whiteKnights;
	std::uint64_t whiteBishops;
	std::uint64_t whiteQueens;
	std::uint64_t whiteKing;

	/* The black piece positions */
	std::uint64_t blackPawns;
	std::uint64_t blackRooks;
	std::uint64_t blackKnights;
	std::uint64_t blackBishops;
	std::uint64_t blackQueens;
	std::uint64_t blackKing;

	/* Commonly derived positions */
	std::uint64_t getAllWhitePieces();
	std::uint64_t getAllBlackPieces();
	std::uint64_t getAllPieces();


	void loadFEN(std::string fenStr);
	std::string getFEN();
};

