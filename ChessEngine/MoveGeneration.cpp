#include "MoveGeneration.h"
#include "ChessData.h"
#include "MoveTables.h"

/**
 * Generates all legal moves for a specific color on the chessboard.
 * @param board Pointer to the ChessBoard object representing the current board state.
 * @param forWhite A boolean indicating whether to generate moves for white pieces (true) or black pieces (false).
 * @return A vector containing ChessMove objects representing legal moves.
 */
std::vector<ChessMove> MoveGeneration::generateColorsLegalMoves(const ChessBoard* board, bool forWhite) {
	std::vector<ChessMove> pseudoMoves;
	std::vector<ChessMove> legalMoves;

	// Get all pseudo moves for pawns, rooks, knights, bishops, queens, and kings.
	const std::uint64_t* pawns = forWhite ? &board->whitePawns : &board->blackPawns;
	const std::uint64_t* rooks = forWhite ? &board->whiteRooks : &board->blackRooks;
	const std::uint64_t* knights = forWhite ? &board->whiteKnights : &board->blackKnights;
	const std::uint64_t* bishops = forWhite ? &board->whiteBishops : &board->blackBishops;
	const std::uint64_t* queens = forWhite ? &board->whiteQueens : &board->blackQueens;
	const std::uint64_t* king = forWhite ? &board->whiteKing : &board->blackKing;

	std::uint64_t unprocessedPieces = board->getAllPieces();

	// Loop through each square on the board.
	for (std::uint8_t i = 0; i < 64; i++) {
		std::uint64_t currMoves = 0;

		if (((*pawns >> i) & 1) == 1) currMoves = pawnPseudoMovesBitboard(board, &i, forWhite);
		else if (((*rooks >> i) & 1) == 1) currMoves = rookPseudoMovesBitboard(board, &i, forWhite);
		else if (((*knights >> i) & 1) == 1) currMoves = knightPseudoMovesBitboard(board, &i, forWhite);
		else if (((*bishops >> i) & 1) == 1) currMoves = bishopPseudoMovesBitboard(board, &i, forWhite);
		else if (((*queens >> i) & 1) == 1) currMoves = queenPseudoMovesBitboard(board, &i, forWhite);
		else if (((*king >> i) & 1) == 1) currMoves = kingPseudoMovesBitboard(board, &i, forWhite);

		if (currMoves == 0) continue;

		// Loop through possible destination squares.
		for (std::uint8_t j = 0; j < 64; j++) {
			if (((currMoves >> j) & 1) != 1) continue;
			ChessMove move(i, j);
			ChessBoard newBoard = *board; // Create a copy of the board by value
			newBoard.makeMove(move.fromSquare, move.toSquare);

			// Check if the move results in the player's own king being in check.
			if (!isCheck(&newBoard, forWhite)) legalMoves.push_back(move);
		}
	}

	return legalMoves;
}


/**
 * Generates all legal moves for a piece located on a specific square on the chessboard.
 * @param board Pointer to the ChessBoard object representing the current board state.
 * @param square The square (0-63) on which the piece is located.
 * @param forWhite A boolean indicating whether to generate moves for white pieces (true) or black pieces (false).
 * @return A vector containing ChessMove objects representing legal moves for the piece on the specified square.
 */
std::vector<ChessMove> MoveGeneration::generateSquaresLegalMoves(const ChessBoard* board, std::uint8_t square, bool forWhite) {
	std::vector<ChessMove> pseudoMoves;
	std::vector<ChessMove> legalMoves;

	// Get all pseudo moves for pawns, rooks, knights, bishops, queens, and kings.
	const std::uint64_t* pawns = forWhite ? &board->whitePawns : &board->blackPawns;
	const std::uint64_t* rooks = forWhite ? &board->whiteRooks : &board->blackRooks;
	const std::uint64_t* knights = forWhite ? &board->whiteKnights : &board->blackKnights;
	const std::uint64_t* bishops = forWhite ? &board->whiteBishops : &board->blackBishops;
	const std::uint64_t* queens = forWhite ? &board->whiteQueens : &board->blackQueens;
	const std::uint64_t* king = forWhite ? &board->whiteKing : &board->blackKing;

	std::uint64_t currMoves = 0;

	if (((*pawns >> square) & 1) == 1) currMoves = pawnPseudoMovesBitboard(board, &square, forWhite);
	else if (((*rooks >> square) & 1) == 1) currMoves = rookPseudoMovesBitboard(board, &square, forWhite);
	else if (((*knights >> square) & 1) == 1) currMoves = knightPseudoMovesBitboard(board, &square, forWhite);
	else if (((*bishops >> square) & 1) == 1) currMoves = bishopPseudoMovesBitboard(board, &square, forWhite);
	else if (((*queens >> square) & 1) == 1) currMoves = queenPseudoMovesBitboard(board, &square, forWhite);
	else if (((*king >> square) & 1) == 1) currMoves = kingPseudoMovesBitboard(board, &square, forWhite);

	if (currMoves == 0) return legalMoves;

	// Loop through possible destination squares.
	for (std::uint8_t j = 0; j < 64; j++) {
		if (((currMoves >> j) & 1) != 1) continue;
		ChessMove move(square, j);
		ChessBoard newBoard = *board; // Create a copy of the board by value
		newBoard.makeMove(move.fromSquare, move.toSquare);

		// Check if the move results in the player's own king being in check.
		if (!isCheck(&newBoard, forWhite)) legalMoves.push_back(move);
	}

	return legalMoves;
}

/**
 * Checks if the specified color is in check on the current chessboard.
 * @param board Pointer to the ChessBoard object representing the current board state.
 * @param forWhite A boolean indicating whether to check for white king's check (true) or black king's check (false).
 * @return True if the specified color is in check, false otherwise.
 */
bool MoveGeneration::isCheck(const ChessBoard* board, bool forWhite)
{
	if (forWhite) {
		return (getDangerSquares(board, false) & board->whiteKing) != 0;
	}

	return (getDangerSquares(board, true) & board->blackKing) != 0;
}


/**
 * Retrieves a bitboard representing squares that are under threat by the specified color.
 * @param board Pointer to the ChessBoard object representing the current board state.
 * @param asWhite A boolean indicating whether to find danger squares for white pieces (true) or black pieces (false).
 * @return A bitboard where set bits represent squares under threat by the specified color.
 */
std::uint64_t MoveGeneration::getDangerSquares(const ChessBoard* board, bool asWhite)
{
	const std::uint64_t* pawns = asWhite ? &board->whitePawns : &board->blackPawns;
	const std::uint64_t* rooks = asWhite ? &board->whiteRooks : &board->blackRooks;
	const std::uint64_t* knights = asWhite ? &board->whiteKnights : &board->blackKnights;
	const std::uint64_t* bishops = asWhite ? &board->whiteBishops : &board->blackBishops;
	const std::uint64_t* queens = asWhite ? &board->whiteQueens : &board->blackQueens;
	const std::uint64_t* king = asWhite ? &board->whiteKing : &board->blackKing;

	std::uint64_t dangerSquares = 0;



	for (std::uint8_t i = 0; i < 64; i++)
	{
		if (((*pawns >> i) & 1) == 1) dangerSquares |= pawnPseudoMovesBitboard(board, &i, asWhite);
		if (((*rooks >> i) & 1) == 1) dangerSquares |= rookPseudoMovesBitboard(board, &i, asWhite);
		if (((*knights >> i) & 1) == 1) dangerSquares |= knightPseudoMovesBitboard(board, &i, asWhite);
		if (((*bishops >> i) & 1) == 1) dangerSquares |= bishopPseudoMovesBitboard(board, &i, asWhite);
		if (((*queens >> i) & 1) == 1) dangerSquares |= queenPseudoMovesBitboard(board, &i, asWhite);
		if (((*king >> i) & 1) == 1) dangerSquares |= kingPseudoMovesBitboard(board, &i, asWhite);
	}

	return dangerSquares;

}


/**
 * Generates pseudo moves for a knight located on a specific square on the chessboard.
 * @param board Pointer to the ChessBoard object representing the current board state.
 * @param square Pointer to the square (0-63) on which the knight is located.
 * @param forWhite A boolean indicating whether the knight is white (true) or black (false).
 * @return A bitboard representing pseudo moves for the knight.
 */
std::uint64_t MoveGeneration::knightPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite)
{
	// use the knight lookup table and mask out own peices
	const std::uint64_t ownPeices = forWhite ? board->getAllWhitePieces() : board->getAllBlackPieces();
	return (~ownPeices) & movetables::knightMoveTable[*square];
}


/**
 * Generates pseudo moves for a king located on a specific square on the chessboard.
 * @param board Pointer to the ChessBoard object representing the current board state.
 * @param square Pointer to the square (0-63) on which the king is located.
 * @param forWhite A boolean indicating whether the king is white (true) or black (false).
 * @return A bitboard representing pseudo moves for the king.
 */
std::uint64_t MoveGeneration::kingPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite)
{
	// use king lookup table and mask out own peices
	const std::uint64_t ownPeices = forWhite ? board->getAllWhitePieces() : board->getAllBlackPieces();
	return (~ownPeices) & movetables::kingMoveTable[*square];
}



/**
 * Generates pseudo moves for a pawn located on a specific square on the chessboard.
 * @param board Pointer to the ChessBoard object representing the current board state.
 * @param square Pointer to the square (0-63) on which the pawn is located.
 * @param forWhite A boolean indicating whether the pawn is white (true) or black (false).
 * @return A bitboard representing pseudo moves for the pawn.
 */
std::uint64_t MoveGeneration::pawnPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite)
{
	const std::uint64_t pawns = forWhite ? board->whitePawns : board->blackPawns;
	const std::uint64_t pawn = pawns & ((uint64_t)1 << *square);


	// these are rank masks, they will be used to determin if a pawn has a valid double (psudeo) move
	const std::uint64_t rank4Mask = data::masks::rankMask[data::masks::rank::RANK_4];
	const std::uint64_t rank5Mask = data::masks::rankMask[data::masks::rank::RANK_5];


	// these are file masks, they will be used to enforce the board boundry when calculating
	// if a pawn can currently capture left / right.
	const std::uint64_t file1Mask = data::masks::rankMask[data::masks::file::FILE_1];
	const std::uint64_t file8Mask = data::masks::rankMask[data::masks::file::FILE_8];

	// Calculate shifted bitboards by directions based on color
	const std::uint64_t forward = forWhite ? pawn << 8 : pawn >> 8;

	const std::uint64_t captureLeft = forWhite ? (pawn & ~file1Mask) << 9 : (pawn & ~file1Mask) >> 7;
	const std::uint64_t captureRight = forWhite ? (pawn & ~file8Mask) << 7 : (pawn & ~file8Mask) >> 9;

	// mask there shifted bitboards to determin if move is psudo legal.
	std::uint64_t singleMove = forward & ~board->getAllPieces();
	const std::uint64_t doubleforward = forWhite ? singleMove << 8 : singleMove >> 8;

	std::uint64_t doubleMove = doubleforward & ~board->getAllPieces() & (forWhite ? rank4Mask : rank5Mask);

	std::uint64_t lhsCapture = captureLeft & (forWhite ? board->getAllBlackPieces() : board->getAllWhitePieces());
	std::uint64_t rhsCapture = captureRight & (forWhite ? board->getAllBlackPieces() : board->getAllWhitePieces());

	return lhsCapture | rhsCapture | singleMove | doubleMove;

}


/**
 * Generates pseudo moves for a bishop located on a specific square on the chessboard.
 * @param board Pointer to the ChessBoard object representing the current board state.
 * @param square Pointer to the square (0-63) on which the bishop is located.
 * @param forWhite A boolean indicating whether the bishop is white (true) or black (false).
 * @return A bitboard representing pseudo moves for the bishop.
 */
std::uint64_t MoveGeneration::bishopPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite)
{
	// get the current blocker bitboard in a blocker bitboard, any peice which can halt the sliding
	// piece is marked as a 1. Everything else is marked as 0.
	const std::uint64_t blockerBoard = data::masks::bishopBlockerMask[*square] & board->getAllPieces();

	// using magic bitboards the magic index is calculated by the formula i = blocker * magic_number >> shifter
	// we can find all this information in our chess data class, so we can simiply numbr crunch the formula.
	const std::uint64_t magicIndex = (blockerBoard * data::magicbitboards::bishoptMagicNumbers[*square]) >> data::magicbitboards::bishopMagicKeyShift[*square];

	// this is where the magic of magic biboards shine, we can simiply index into an already computed lookup table to
	// find what the possible moves are.
	const std::uint64_t magicMoves = movetables::bishopMoveTable[magicIndex + data::magicbitboards::bishopFlatternedIndices[*square]];

	// in a magic bitboard we can capture our own peices, to sort this out we can just mask out our own pieces.
	return magicMoves & (forWhite ? ~board->getAllWhitePieces() : ~board->getAllBlackPieces());
}


/**
 * Generates pseudo moves for a rook located on a specific square on the chessboard.
 * @param board Pointer to the ChessBoard object representing the current board state.
 * @param square Pointer to the square (0-63) on which the rook is located.
 * @param forWhite A boolean indicating whether the rook is white (true) or black (false).
 * @return A bitboard representing pseudo moves for the rook.
 */
std::uint64_t MoveGeneration::rookPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite)
{
	// follows same logic as the bishop generation
	const std::uint64_t blockerBoard = data::masks::rookBlockerMask[*square] & board->getAllPieces();
	const std::uint64_t magicIndex = (blockerBoard * data::magicbitboards::rooktMagicNumbers[*square]) >> data::magicbitboards::rooktMagicKeyShift[*square];
	const std::uint64_t magicMoves = movetables::rookMoveTable[magicIndex + data::magicbitboards::rooktFlatternedIndices[*square]];

	return magicMoves & (forWhite ? ~board->getAllWhitePieces() : ~board->getAllBlackPieces());
}


/**
 * Generates pseudo moves for a queen located on a specific square on the chessboard.
 * A queen's pseudo moves are a combination of rook and bishop pseudo moves.
 * @param board Pointer to the ChessBoard object representing the current board state.
 * @param square Pointer to the square (0-63) on which the queen is located.
 * @param forWhite A boolean indicating whether the queen is white (true) or black (false).
 * @return A bitboard representing pseudo moves for the queen.
 */
std::uint64_t MoveGeneration::queenPseudoMovesBitboard(const ChessBoard* board, const std::uint8_t* square, bool forWhite)
{
	// a queen is just a piece which acts as both a rook, and bishop. So all that is needed is to get the sudo
	// moves for both rook and bishop and combine them.
	return rookPseudoMovesBitboard(board, square, forWhite) | bishopPseudoMovesBitboard(board, square, forWhite);
}


