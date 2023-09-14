/**
 * @file commands.cpp
 *
 * Implementation of commands related to a chess engine using the Universal Chess Interface (UCI) protocol.
 * And also engine specific commands.
 *
 * @author Martin N
 * @date 09/2023
 */


#include "Commands.h"
#include "MoveGeneration.h"
#include "BoardEvaluation.h"
#include <iostream>
#include <vector>


/**
* Displays the current state of the chessboard in the console.
*
* @param board Pointer to the ChessBoard object representing the current game state.
*/
void commands::engine_display(const ChessBoard* board)
{
    const char pieceSymbols[] = {
    '-', // ChessBoard::PieceType::EMPTY
    'P', // ChessBoard::PieceType::WHITE_PAWN
    'R', // ChessBoard::PieceType::WHITE_ROOK
    'N', // ChessBoard::PieceType::WHITE_KNIGHT
    'B', // ChessBoard::PieceType::WHITE_BISHOP
    'Q', // ChessBoard::PieceType::WHITE_QUEEN
    'K', // ChessBoard::PieceType::WHITE_KING
    'p', // ChessBoard::PieceType::BLACK_PAWN
    'r', // ChessBoard::PieceType::BLACK_ROOK
    'n', // ChessBoard::PieceType::BLACK_KNIGHT
    'b', // ChessBoard::PieceType::BLACK_BISHOP
    'q', // ChessBoard::PieceType::BLACK_QUEEN
    'k'  // ChessBoard::PieceType::BLACK_KING
    };

    std::cout << std::endl;
    for (std::int8_t i = 63; i >= 0; i--)
    {
        if (i % 8 == 7) std::cout << " " << (i / 8) + 1 << " | ";

        ChessBoard::PieceType piece = board->getPieceTypeAtSquare(i / 8, i % 8);
        char currSquare = pieceSymbols[static_cast<int>(piece)+1];

        std::cout << currSquare << ' ';
        if (i % 8 == 0) std::cout << std::endl;
    }

    std::cout << "   '----------------" << std::endl << "     a b c d e f g h\n" << std::endl;
    std::cout << (board->currPlayer ? "      Whites's Move" : "      Black's Move") << std::endl;
}

/**
* Placeholder function for processing the "uci" command.
*/
void commands::uci_uci()
{
}


/**
* Placeholder function for processing the "debug" command.
*
* @param mode The debug mode (either "on" or "off").
*/
void commands::uci_debug(std::string mode)
{
}

/**
* Sends the "readyok" response to indicate that the engine is ready to receive commands.
*/
void commands::uci_isready()
{
    std::cout << "readyok" << std::endl;
}

/**
 * Placeholder function for processing the "ucinewgame" command.
 */
void commands::uci_newGame()
{
}

/**
 * Converts a square coordinate in algebraic notation to a numeric representation.
 *
 * @param square The square coordinate in algebraic notation (e.g., "e4").
 * @return The numeric representation of the square (0 to 63).
 */
int squareToNumeric(const std::string& square) {
    
    int file = square[0] - 'a';
    int rank = square[1] - '1';

    return rank * 8 + (7 - file);
}

/**
 * Converts a numeric square representation to algebraic notation.
 *
 * @param numeric The numeric representation of the square (0 to 63).
 * @return The square coordinate in algebraic notation (e.g., "e4").
 */
std::string numericToSquare(int numeric) {

    int rank = numeric / 8;
    int file = 7 - (numeric % 8); // Reverse calculation

    char fileChar = 'a' + file;
    char rankChar = '1' + rank;

    return std::string(1, fileChar) + std::string(1, rankChar);
}

/**
 * Processes the "position" command in UCI and updates the chessboard accordingly.
 *
 * @param board Pointer to the ChessBoard object representing the current game state.
 * @param details The details of the "position" command, including FEN and move history.
 */
void commands::uci_position(ChessBoard* board, std::string details)
{
    // Remove spaces using erase-remove idiom
    details.erase(std::remove_if(details.begin(), details.end(), ::isspace), details.end());

    std::smatch match;
    if (std::regex_match(details, match, uci_positionCmd)) {

        // Check which part of the regex was matched
        if (match[2].str() == "startpos") {

            std::string replacement = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

            std::regex pattern("startpos");
            details = std::regex_replace(details, pattern, replacement);
            return uci_position(board, details);

        }

        // It's the FEN variant
        std::string fen = match[3].str();
        std::string color = match[4].str();
        std::string castlingRights = match[5].str();
        std::string enPassant = match[7].str();
        std::string halfMoves = match[9].str();
        std::string fullMoves = match[10].str();

        bool whitesMove = color == "w";
        commands::loadFEN(board, fen);
        board->currPlayer = whitesMove;


        // Handle the moves
        std::string moves = match[11].str();
        std::regex moveRegex(R"([a-h][1-8][a-h][1-8])");
        std::sregex_iterator it(moves.begin(), moves.end(), moveRegex);
        std::sregex_iterator end;

        while (it != end) {
            std::string currMove = it->str();
            int fromSquare = squareToNumeric(currMove.substr(0, 2));
            int toSquare = squareToNumeric(currMove.substr(2, 4));

            // verify is legal move
            std::vector<ChessMove> fromSquareLegals = MoveGeneration::generateSquaresLegalMoves(board, fromSquare, whitesMove);
            
            bool isLegal = false;
            for (ChessMove move : fromSquareLegals) {
                if (move.toSquare == toSquare) {
                    isLegal = true;
                    break;
                }
            }

            if (!isLegal) {
                std::cout << "illegal move: " << currMove.substr(0, 2) << "->" << currMove.substr(2, 4) << std::endl;
                board->clearBoard();
                return;
            }

            board->makeMove(fromSquare, toSquare);

            whitesMove = !whitesMove;
            ++it;
        }
    }
}


/**
 * Processes the "go" command in UCI and selects the best move for the engine to play.
 *
 * @param board Pointer to the ChessBoard object representing the current game state.
 * @param details The details of the "go" command, including the time control information.
 */
void commands::uci_go(ChessBoard* board, std::string details)
{
    std::smatch match;
    std::regex_match(details, match, uci_goCmd);

    ChessMove bestMove = BoardEvaluation::getBestNextMove(board, stoi(match[2]), match[1] == "w");
    std::string fromSq = numericToSquare(bestMove.fromSquare);
    std::string toSq = numericToSquare(bestMove.toSquare);

    std::cout << "\nBest Move " << fromSq << toSq << std::endl;
}


/**
 * Loads a chessboard state from a Forsyth-Edwards Notation (FEN) string.
 *
 * @param board Pointer to the ChessBoard object to update.
 * @param fen The FEN string representing the desired chessboard state.
 * @return True if the FEN was successfully loaded; otherwise, false.
 */
bool commands::loadFEN(ChessBoard* board, const std::string& fen) {
    if (fen.empty()) return false; // Empty FEN string

    int rank = 7; // Start from rank 8 (index 7 in an array)
    int file = 7; // Start from file A (index 7 in an array)

    board->clearBoard();

    for (char fenChar : fen) {
        if (fenChar == '/') {
            // Move to the next rank
            rank--;
            file = 7;
            continue;
        }
        if (rank < 0 || file < 0) return false; // Invalid FEN string format
        
       
        else if (isdigit(fenChar)) {
            // Empty squares
            int emptySquares = fenChar - '0';
            file -= emptySquares;
        }
        else {
            // Non-empty squares (pieces)
            ChessBoard::PieceType piece;
            switch (fenChar) {
                case 'P': piece = ChessBoard::PieceType::WHITE_PAWN; break;
                case 'R': piece = ChessBoard::PieceType::WHITE_ROOK; break;
                case 'N': piece = ChessBoard::PieceType::WHITE_KNIGHT; break;
                case 'B': piece = ChessBoard::PieceType::WHITE_BISHOP; break;
                case 'Q': piece = ChessBoard::PieceType::WHITE_QUEEN; break;
                case 'K': piece = ChessBoard::PieceType::WHITE_KING; break;
                case 'p': piece = ChessBoard::PieceType::BLACK_PAWN; break;
                case 'r': piece = ChessBoard::PieceType::BLACK_ROOK; break;
                case 'n': piece = ChessBoard::PieceType::BLACK_KNIGHT; break;
                case 'b': piece = ChessBoard::PieceType::BLACK_BISHOP; break;
                case 'q': piece = ChessBoard::PieceType::BLACK_QUEEN; break;
                case 'k': piece = ChessBoard::PieceType::BLACK_KING; break;
                default: return false; // Invalid character in FEN string
            }
            board->setPiece(piece, rank, file);
            file--;
        }
    }

    return true;
}

/**
 * Processes the "moves" command and prints legal moves from a specified square.
 *
 * @param board Pointer to the ChessBoard object representing the current game state.
 * @param details The details of the "moves" command, including the source square and color.
 */
void commands::engine_moves(ChessBoard* board, std::string details)
{
    std::smatch match;
    if (std::regex_match(details, match, engine_movesCmd)) {

        int square = squareToNumeric(match[1]);
        bool color = match[2] == "w";
        
        std::vector<ChessMove> moves = MoveGeneration::generateSquaresLegalMoves(board, square, color);

        for (ChessMove move : moves) {
            std::cout << numericToSquare(move.toSquare) << " ";
        }

        std::cout << std::endl;
    }
}

/**
 * Processes the "check" command and checks if a specified color is in check.
 *
 * @param board Pointer to the ChessBoard object representing the current game state.
 * @param details The details of the "check" command, including the color to check.
 */
void commands::engine_isCheck(ChessBoard* board, std::string details)
{
    std::smatch match;
    if (std::regex_match(details, match, engine_isCheckCmd)) {
        bool color = match[1] == "w";

        std::string result = MoveGeneration::isCheck(board, color) ? "yes" : "no";
        std::cout << result << std::endl;
    }
}

/**
 * Processes the "mate" command and checks if a specified color is in checkmate.
 *
 * @param board Pointer to the ChessBoard object representing the current game state.
 * @param details The details of the "mate" command, including the color to check.
 */
void commands::engine_isMate(ChessBoard* board, std::string details)
{
    std::smatch match;
    if (std::regex_match(details, match, engine_isMateCmd)) {
        bool color = match[1] == "w";

        std::string result = BoardEvaluation::isCheckMate(board, color) ? "yes" : "no";
        std::cout << result << std::endl;
    }
}

/**
 * Processes the "piece" command and prints the type of piece on a specified square.
 *
 * @param board Pointer to the ChessBoard object representing the current game state.
 * @param details The details of the "piece" command, including the square.
 */
void commands::engine_piece(ChessBoard* board, std::string details)
{
    std::smatch match;
    if (std::regex_match(details, match, engine_pieceCmd)) {
        std::string squareStr = match[1];
        int square = squareToNumeric(squareStr);

        std::cout << ChessBoard::pieceTypeToFen(board->getPieceTypeAtSquare(square/8, square%8)) << std::endl;
    
    }
}

/**
 * Processes the "move" command and makes a move on the chessboard if it's legal.
 *
 * @param board Pointer to the ChessBoard object representing the current game state.
 * @param details The details of the "move" command, including the source and destination squares.
 */
void commands::engine_move(ChessBoard* board, std::string details)
{
    std::smatch match;
    if (std::regex_match(details, match, engine_moveCmd)) {

        int squareFrom = squareToNumeric(match[1]);
        int squareTo = squareToNumeric(match[2]);
        
        bool display = match[3] == "y";
        bool color = board->currPlayer;

        std::vector<ChessMove> moves = MoveGeneration::generateSquaresLegalMoves(board, squareFrom, color);

        for (ChessMove move : moves) {
            if (move.toSquare == squareTo) {
                board->makeMove(squareFrom, squareTo);
                if (display) engine_display(board);
                return;
            }
        }

        std::cout << "Illegal Move for " << (color ? "white" : "black") << std::endl;
    }
}
