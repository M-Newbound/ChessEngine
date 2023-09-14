/**
 * @file commands.cpp
 *
 * Implementation of commands related to a chess engine using the Universal Chess Interface (UCI) protocol.
 * This file contains regular expressions for parsing UCI and engine-specific commands, as well as functions
 * to handle and process these commands.
 *
 * @author Martin N
 * @date 09/2023
 */

#include <string>
#include <regex>
#include <unordered_map>
#include "ChessBoard.h"

namespace commands {

    // Regular expressions for engine and UCI commands

    // Engine specific commands
    const std::regex engine_displayCmd(R"(.*display\s*)");
    const std::regex engine_movesCmd(R"(.*moves\s*([a-h][1-8])\s*([wb])\s*)");
    const std::regex engine_isCheckCmd(R"(.*check\s*([wb])\s*)");
    const std::regex engine_isMateCmd(R"(.*mate\s*([wb])\s*)");
    const std::regex engine_pieceCmd(R"(.*piece\s*([a-h][1-8])\s*)");
    const std::regex engine_moveCmd(R"(.*move\s*([a-h][1-8])\s*([a-h][1-8])\s*([y]|[n])?)");
    //const std::regex engine_play(R"(.*play ([cp]) ([cp])\s*)");

    // UCI specific commands
    const std::regex uci_uciCmd(R"(.*uci\s*)");
    const std::regex uci_debugCmd(R"(.*debug\s*(on|off)\s*)");
    const std::regex uci_isreadyCmd(R"(.*isready\s*)");
    const std::regex uci_newgameCmd(R"(.*ucinewgame\s*)");
    const std::regex uci_positionCmd(R"((.*position\s*)(startpos|((?:[rnbqkpRNBQKP1-8]+/){7}[rnbqkpRNBQKP1-8]+)\s*([bw])\s*((-|[KQkq]){1,4})\s*(-|[a-h][1-8])\s*((\d)+\s*(\d)+))\s*(?:moves\s*(([a-h]\s*[1-8]\s*[a-h]\s*[1-8]\s*)+))?$)");
    const std::regex uci_goCmd(R"(go ([w]|[b]) ([1-9]))");

    // Function prototypes for handling UCI commands
    void uci_uci();
    void uci_debug(std::string mode);
    void uci_isready();
    void uci_newGame();
    void uci_position(ChessBoard* board, std::string details);
    void uci_go(ChessBoard* board, std::string details);

    // Function prototypes for handling engine-specific commands
    void engine_display(const ChessBoard* board);
    void engine_moves(ChessBoard* board, std::string details);
    void engine_isCheck(ChessBoard* board, std::string details);
    void engine_isMate(ChessBoard* board, std::string details);
    void engine_piece(ChessBoard* board, std::string details);
    void engine_move(ChessBoard* board, std::string details);

    // Function for loading FEN (Forsyth-Edwards Notation) into a ChessBoard
    bool loadFEN(ChessBoard* board, const std::string& fen);
}
