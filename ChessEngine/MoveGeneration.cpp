#include "MoveGeneration.h"
#include "ChessData.h"
#include "MoveTables.h"

std::vector<ChessMove*> MoveGeneration::generateLegalMoves(ChessBoard& board, bool forWhite)
{
	std::vector<ChessMove*> pseudoMoves;
	std::vector<ChessMove*> legalMoves;

	// get all pseudo moves for pawns
	std::uint64_t pawns = forWhite ? board.whitePawns : board.blackPawns;
	std::uint64_t rooks = forWhite ? board.whiteRooks : board.blackRooks;
	std::uint64_t knights = forWhite ? board.whiteKnights : board.blackKnights;
	std::uint64_t bishops = forWhite ? board.whiteBishops : board.blackBishops;
	std::uint64_t queens = forWhite ? board.whiteQueens : board.blackQueens;
	std::uint64_t king = forWhite ? board.whiteKing : board.blackKing;

	for (std::uint8_t i = 0; i < 64; i++)
	{
		std::uint64_t currMoves = 0; 

		if (((pawns >> i) & 1) == 1) currMoves = pawnPseudoMovesBitboard(board, i, forWhite);
		else if (((rooks >> i) & 1) == 1) currMoves = rookPseudoMovesBitboard(board, i, forWhite);
		else if (((knights >> i) & 1) == 1) currMoves = knightPseudoMovesBitboard(board, i, forWhite);
		else if (((bishops >> i) & 1) == 1) currMoves = bishopPseudoMovesBitboard(board, i, forWhite);
		else if (((queens >> i) & 1) == 1) currMoves = queenPseudoMovesBitboard(board, i, forWhite);
		else if (((king >> i) & 1) == 1) currMoves = kingPseudoMovesBitboard(board, i, forWhite);
	
		if (currMoves == 0) continue;

		for (std::uint8_t j = 0; j < 64; j++)
		{
			if (((currMoves >> j) & 1) != 1) continue;
			pseudoMoves.push_back(new ChessMove(i, j));
		}
	}

	// filter out illegal moves
	for (ChessMove* move : pseudoMoves)
	{
		ChessBoard* newBoard = board.copy();
		newBoard->makeMove(move->fromSquare, move->toSquare);

		if (!isCheck(*newBoard, forWhite)) legalMoves.push_back(move);
		else delete move;

		delete newBoard;
	}

	// legal moves can be returned even without heap allocation, this is due to how the
	// c++ compiler optimises and thus this is defined behaviour.
	return legalMoves;
}

bool MoveGeneration::isCheck(ChessBoard& board, bool forWhite)
{
	if (forWhite) {
		return (getDangerSquares(board, true) & board.whiteKing) != 0;
	}

	return (getDangerSquares(board, false) & board.blackKing) != 0;
}

std::uint64_t MoveGeneration::getDangerSquares(ChessBoard& board, bool forWhite)
{
	std::uint64_t pawns = forWhite ? board.whitePawns : board.blackPawns;
	std::uint64_t rooks = forWhite ? board.whiteRooks : board.blackRooks;
	std::uint64_t knights = forWhite ? board.whiteKnights : board.blackKnights;
	std::uint64_t bishops = forWhite ? board.whiteBishops : board.blackBishops;
	std::uint64_t queens = forWhite ? board.whiteQueens : board.blackQueens;
	std::uint64_t king = forWhite ? board.whiteKing : board.blackKing;

	std::uint64_t dangerSquares = 0;


	for (std::uint8_t i = 0; i < 64; i++)
	{
		if ((pawns >> i & 1) == 1) dangerSquares |= pawnPseudoMovesBitboard(board, i, forWhite);
		if ((rooks >> i & 1) == 1) dangerSquares |= rookPseudoMovesBitboard(board, i, forWhite);
		if ((knights >> i & 1) == 1) dangerSquares |= knightPseudoMovesBitboard(board, i, forWhite);
		if ((bishops >> i & 1) == 1) dangerSquares |= bishopPseudoMovesBitboard(board, i, forWhite);
		if ((queens >> i & 1) == 1) dangerSquares |= queenPseudoMovesBitboard(board, i, forWhite);
		if ((king >> i & 1) == 1) dangerSquares |= kingPseudoMovesBitboard(board, i, forWhite);
	}

	return dangerSquares;

}



std::uint64_t MoveGeneration::knightPseudoMovesBitboard(ChessBoard& board, const std::uint8_t square, bool forWhite)
{
	// use the knight lookup table and mask out own peices
	const std::uint64_t ownPeices = forWhite ? board.getAllWhitePieces() : board.getAllBlackPieces();
	return (~ownPeices) & movetables::knightMoveTable[square];
}

std::uint64_t MoveGeneration::kingPseudoMovesBitboard(ChessBoard& board, const std::uint8_t square, bool forWhite)
{
	// use king lookup table and mask out own peices
	const std::uint64_t ownPeices = forWhite ? board.getAllWhitePieces() : board.getAllBlackPieces();
	return (~ownPeices) & movetables::kingMoveTable[square];
}


std::uint64_t MoveGeneration::pawnPseudoMovesBitboard(ChessBoard& board, const std::uint8_t square, bool forWhite)
{
	const std::uint64_t pawns = forWhite ? board.whitePawns : board.blackPawns;
	const std::uint64_t pawn = pawns & ((uint64_t)1 << square);

	
	// these are rank masks, they will be used to determin if a pawn has a valid double (psudeo) move
	const std::uint64_t rank4Mask = data::masks::rankMask[data::masks::rank::RANK_4];
	const std::uint64_t rank5Mask = data::masks::rankMask[data::masks::rank::RANK_5];


	// these are file masks, they will be used to enforce the board boundry when calculating
	// if a pawn can currently capture left / right.
	const std::uint64_t file1Mask = data::masks::rankMask[data::masks::file::FILE_1];
	const std::uint64_t file8Mask = data::masks::rankMask[data::masks::file::FILE_8];

	// Calculate shifted bitboards by directions based on color
	const std::uint64_t forward       = forWhite ? pawn    << 8 : pawn    >> 8;
	const std::uint64_t doubleforward = forWhite ? forward << 8 : forward >> 8;
	
	const std::uint64_t captureLeft   = forWhite ? (pawn & ~file1Mask)  << 9 : (pawn & ~file1Mask) >> 7;
	const std::uint64_t captureRight  = forWhite ? (pawn & ~file8Mask)  << 7 : (pawn & ~file8Mask) >> 9;

	// mask there shifted bitboards to determin if move is psudo legal.
	std::uint64_t singleMove = forward & ~board.getAllPieces();
	std::uint64_t doubleMove = doubleforward & ~board.getAllPieces() & (forWhite ? rank4Mask : rank5Mask);

	std::uint64_t lhsCapture = captureLeft & (forWhite ? board.getAllBlackPieces() : board.getAllWhitePieces());
	std::uint64_t rhsCapture = captureRight & (forWhite ? board.getAllBlackPieces() : board.getAllWhitePieces());

	return lhsCapture | rhsCapture | singleMove | doubleMove;

}


std::uint64_t MoveGeneration::bishopPseudoMovesBitboard(ChessBoard& board, const std::uint8_t square, bool forWhite)
{
	// get the current blocker bitboard in a blocker bitboard, any peice which can halt the sliding
	// piece is marked as a 1. Everything else is marked as 0.
	const std::uint64_t blockerBoard = data::masks::bishopBlockerMask[square] & board.getAllPieces();
	
	// using magic bitboards the magic index is calculated by the formula i = blocker * magic_number >> shifter
	// we can find all this information in our chess data class, so we can simiply numbr crunch the formula.
	const std::uint64_t magicIndex = (blockerBoard * data::magicbitboards::bishoptMagicNumbers[square]) >> data::magicbitboards::bishopMagicKeyShift[square];
	
	// this is where the magic of magic biboards shine, we can simiply index into an already computed lookup table to
	// find what the possible moves are.
	const std::uint64_t magicMoves = movetables::bishopMoveTable[magicIndex + data::magicbitboards::bishopFlatternedIndices[square]];

	// in a magic bitboard we can capture our own peices, to sort this out we can just mask out our own pieces.
	return magicMoves & (forWhite ? ~board.getAllWhitePieces() : ~board.getAllBlackPieces());
}

std::uint64_t MoveGeneration::rookPseudoMovesBitboard(ChessBoard& board, const std::uint8_t square, bool forWhite)
{
	// follows same logic as the bishop generation
	const std::uint64_t blockerBoard = data::masks::rookBlockerMask[square] & board.getAllPieces();
	const std::uint64_t magicIndex = (blockerBoard * data::magicbitboards::rooktMagicNumbers[square]) >> data::magicbitboards::rooktMagicKeyShift[square];
	const std::uint64_t magicMoves = movetables::rookMoveTable[magicIndex + data::magicbitboards::rooktFlatternedIndices[square]];

	return magicMoves & (forWhite ? ~board.getAllWhitePieces() : ~board.getAllBlackPieces());
}

std::uint64_t MoveGeneration::queenPseudoMovesBitboard(ChessBoard& board, const std::uint8_t square, bool forWhite)
{
	// a queen is just a piece which acts as both a rook, and bishop. So all that is needed is to get the sudo
	// moves for both rook and bishop and combine them.
	return rookPseudoMovesBitboard(board, square, forWhite) | bishopPseudoMovesBitboard(board, square, forWhite);
}


