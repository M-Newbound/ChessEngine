#pragma once
#include <string>
#include <regex>
#include "ChessBoard.h"

namespace commands {

    

    // engine specific commands
    const std::regex displayboardCmdRegex(R"(.*displayboard\s*\n)");

    void displayBoard(const ChessBoard* board);

    // UCI specific commands
    const std::regex uciCmdRegex(R"(.*uci\s*\n)");
    const std::regex debugCmdRegex(R"(.*debug\s*(on|off)\s*\n)");
    const std::regex isreadyCmdRegex(R"(.*isready\s*\n)");
    const std::regex newgameCmdRegex(R"(.*ucinewgame\s*\n)");

    static void uci_uci();
    static void uci_debug(std::string mode);
    static void uci_isready();
    static void uci_newGame();
    static void uci_position(std::string details);
    
    // helper functions
    bool loadFEN(ChessBoard& board, const std::string& fen);
}


