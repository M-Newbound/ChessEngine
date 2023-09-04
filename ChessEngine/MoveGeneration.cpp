#include "MoveGeneration.h"
#include "LookupTable.h"


std::uint64_t MoveGeneration::knightPseudoMovesBitboard(ChessBoard& board, const std::uint8_t square, bool forWhite)
{
	std::uint64_t knights = forWhite ? board.whiteKnights : board.blackKnights;
	std::uint64_t knight = knights & ((uint64_t)1 << square);

	std::uint64_t ownPeices = forWhite ? board.getAllWhitePieces() : board.getAllBlackPieces();
	return (~ownPeices) & ChessTables::knightMoveTable[square];
}

std::uint64_t MoveGeneration::kingPseudoMovesBitboard(ChessBoard& board, const std::uint8_t square, bool forWhite)
{
	std::uint64_t king = forWhite ? board.whiteKing : board.blackKing;
	std::uint64_t ownPeices = forWhite ? board.getAllWhitePieces() : board.getAllBlackPieces();
	return (~ownPeices) & ChessTables::kingMoveTable[square];
}




std::uint64_t MoveGeneration::pawnPseudoMovesBitboard(ChessBoard& board, const std::uint8_t square, bool forWhite)
{
	std::uint64_t pawns = forWhite ? board.whitePawns : board.blackPawns;
	std::uint64_t pawn  = pawns & ((uint64_t)1 << square);

	return 0;
}




std::uint64_t MoveGeneration::bishopPseudoMovesBitboard(ChessBoard& board, const std::uint8_t square, bool forWhite)
{
	std::uint64_t bishops = forWhite ? board.whiteBishops : board.blackBishops;
	std::uint64_t bishop  = bishops & ((uint64_t)1 << square);
	return 0;
}

std::uint64_t MoveGeneration::rookPseudoMovesBitboard(ChessBoard& board, const std::uint8_t square, bool forWhite)
{
	std::uint64_t rooks = forWhite ? board.whiteRooks : board.blackRooks;
	std::uint64_t rook  = rooks & ((uint64_t)1 << square);
	return 0;
}

std::uint64_t MoveGeneration::queenPseudoMovesBitboard(ChessBoard& board, const std::uint8_t square, bool forWhite)
{
	std::uint64_t queens = forWhite ? board.whiteQueens : board.blackQueens;
	std::uint64_t queen  = queens & ((uint64_t)1 << square);
	return 0;
}


