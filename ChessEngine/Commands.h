#pragma once
#include <string>
#include <regex>
#include <unordered_map>
#include "ChessBoard.h"

namespace commands {
    // commo

    // engine specific commands
    const std::regex displayboardCmdRegex(R"(.*display\s*)");

    void displayBoard(const ChessBoard* board);

    // UCI specific commands
    const std::regex uci_uciCmd(R"(.*uci\s*)");
    const std::regex uci_debugCmd(R"(.*debug\s*(on|off)\s*)");
    const std::regex uci_isreadyCmd(R"(.*isready\s*)");
    const std::regex uci_newgameCmd(R"(.*ucinewgame\s*)");
    const std::regex uci_positionCmd(R"((.*position\s*)(startpos|((?:[rnbqkpRNBQKP1-8]+/){7}[rnbqkpRNBQKP1-8]+)\s*([bw])\s*((-|[KQkq]){1,4})\s*(-|[a-h][1-8])\s*((\d)+\s*(\d)+))\s*(?:moves\s*(([a-h]\s*[1-8]\s*[a-h]\s*[1-8]\s*)+))?$)");
    
    void uci_uci();
    void uci_debug(std::string mode);
    void uci_isready();
    void uci_newGame();
    void uci_position(ChessBoard* board, std::string details);
    
    // helper functions
    bool loadFEN(ChessBoard* board, const std::string& fen);

}


