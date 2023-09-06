#include "Commands.h"
#include <iostream>

void commands::displayBoard(const ChessBoard* board)
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

    std::cout << "   '----------------" << std::endl << "     a b c e d f g h" << std::endl << std::endl;
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
        // Handle invalid input
        return -1; // Or some other error code
    }

    int file = square[0] - 'a'; // Assuming 'a' to 'h' for files
    int rank = square[1] - '1'; // Assuming '1' to '8' for ranks

    

    return rank * 8 + (7 - file);
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
            std::cout << currMove << std::endl;

            int fromSquare = squareToNumeric(currMove.substr(0, 2));
            int toSquare = squareToNumeric(currMove.substr(2, 4));

            // verify is psudo move

            // verify is legal move

            board->makeMove(fromSquare, toSquare);

            whitesMove = !whitesMove;
            ++it;
        }
    }
}

bool commands::loadFEN(ChessBoard* board, const std::string& fen) {
    if (fen.empty()) return false; // Empty FEN string

    int rank = 7; // Start from rank 8 (index 7 in an array)
    int file = 7; // Start from file A (index 7 in an array)

    board->whitePawns = 0;
    board->whiteRooks = 0;
    board->whiteKnights = 0;
    board->whiteBishops = 0;
    board->whiteQueens = 0;
    board->whiteKing = 0;
    board->blackPawns = 0;
    board->blackRooks = 0;
    board->blackKnights = 0;
    board->blackBishops = 0;
    board->blackQueens = 0;
    board->blackKing = 0;

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
                case 'P': piece = ChessBoard::WHITE_PAWN; break;
                case 'R': piece = ChessBoard::WHITE_ROOK; break;
                case 'N': piece = ChessBoard::WHITE_KNIGHT; break;
                case 'B': piece = ChessBoard::WHITE_BISHOP; break;
                case 'Q': piece = ChessBoard::WHITE_QUEEN; break;
                case 'K': piece = ChessBoard::WHITE_KING; break;
                case 'p': piece = ChessBoard::BLACK_PAWN; break;
                case 'r': piece = ChessBoard::BLACK_ROOK; break;
                case 'n': piece = ChessBoard::BLACK_KNIGHT; break;
                case 'b': piece = ChessBoard::BLACK_BISHOP; break;
                case 'q': piece = ChessBoard::BLACK_QUEEN; break;
                case 'k': piece = ChessBoard::BLACK_KING; break;
                default: return false; // Invalid character in FEN string
            }
            board->setPiece(piece, rank, file);
            file--;
        }
    }

    return true;
}
