#include "Commands.h"
#include "MoveGeneration.h"
#include "BoardEvaluation.h"
#include <iostream>
#include <vector>

void commands::engine_display(const ChessBoard* board)
{
    std::cout << std::endl;
    for (std::int8_t i = 63; i >= 0; i--)
    {
        if (i % 8 == 7) std::cout << " " << (i / 8) + 1 << " | ";

        char currSquare = '-';
        ChessBoard::PieceType piece = board->getPieceTypeAtSquare(i / 8, i % 8);

        if (piece == ChessBoard::PieceType::WHITE_PAWN) currSquare = 'P';
        else if (piece == ChessBoard::PieceType::WHITE_ROOK) currSquare = 'R';
        else if (piece == ChessBoard::PieceType::WHITE_KNIGHT) currSquare = 'N';
        else if (piece == ChessBoard::PieceType::WHITE_BISHOP) currSquare = 'B';
        else if (piece == ChessBoard::PieceType::WHITE_QUEEN) currSquare = 'Q';
        else if (piece == ChessBoard::PieceType::WHITE_KING) currSquare = 'K';
        else if (piece == ChessBoard::PieceType::BLACK_PAWN) currSquare = 'p';
        else if (piece == ChessBoard::PieceType::BLACK_ROOK) currSquare = 'r';
        else if (piece == ChessBoard::PieceType::BLACK_KNIGHT) currSquare = 'n';
        else if (piece == ChessBoard::PieceType::BLACK_BISHOP) currSquare = 'b';
        else if (piece == ChessBoard::PieceType::BLACK_QUEEN) currSquare = 'q';
        else if (piece == ChessBoard::PieceType::BLACK_KING) currSquare = 'k';

        std::cout << currSquare << ' ';
        if (i % 8 == 0) std::cout << std::endl;
    }

    std::cout << "   '----------------" << std::endl << "     a b c d e f g h" << std::endl << std::endl;
}

void commands::uci_uci()
{
}

void commands::uci_debug(std::string mode)
{
}

void commands::uci_isready()
{
}

void commands::uci_newGame()
{
}

int squareToNumeric(const std::string& square) {
    if (square.length() != 2) {
        return -1; // Or some other error code
    }

    int file = square[0] - 'a'; // Assuming 'a' to 'h' for files
    int rank = square[1] - '1'; // Assuming '1' to '8' for ranks

    return rank * 8 + (7 - file);
}

std::string numericToSquare(int numeric) {
    if (numeric < 0 || numeric >= 64) {
        return ""; // Or some other error handling
    }

    int rank = numeric / 8;
    int file = 7 - (numeric % 8); // Reverse calculation

    char fileChar = 'a' + file;
    char rankChar = '1' + rank;

    return std::string(1, fileChar) + std::string(1, rankChar);
}

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



void commands::uci_go(ChessBoard* board, std::string details)
{
    ChessMove bestMove = BoardEvaluation::getBestNextMove(board, 5, true);
    std::cout << "\nBest Move  " << unsigned(bestMove.fromSquare) << " " << unsigned(bestMove.toSquare) << std::endl;
}



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

void commands::engine_moves(ChessBoard* board, std::string details)
{
    //details.erase(std::remove_if(details.begin(), details.end(), ::isspace), details.end());

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

void commands::engine_isCheck(ChessBoard* board, std::string details)
{
    std::smatch match;
    if (std::regex_match(details, match, engine_isCheckCmd)) {
        bool color = match[1] == "w";

        std::string result = MoveGeneration::isCheck(board, color) ? "yes" : "no";
        std::cout << result << std::endl;
    }
}

void commands::engine_isMate(ChessBoard* board, std::string details)
{
    std::smatch match;
    if (std::regex_match(details, match, engine_isMateCmd)) {
        bool color = match[1] == "w";

        std::string result = BoardEvaluation::isCheckMate(board, color) ? "yes" : "no";
        std::cout << result << std::endl;
    }
}
