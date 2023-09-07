#pragma once
#include <string>
#include <regex>
#include <unordered_map>
#include "ChessBoard.h"

namespace commands {
    // commo

    // engine specific commands
    const std::regex engine_displayCmd(R"(.*display\s*)");
    const std::regex engine_movesCmd(R"(moves ([a-h][1-8]) ([wb]))");
    const std::regex engine_isCheckCmd(R"(check ([wb]))");
    const std::regex engine_isMateCmd(R"(mate ([wb]))");



    // UCI specific commands
    const std::regex uci_uciCmd(R"(.*uci\s*)");
    const std::regex uci_debugCmd(R"(.*debug\s*(on|off)\s*)");
    const std::regex uci_isreadyCmd(R"(.*isready\s*)");
    const std::regex uci_newgameCmd(R"(.*ucinewgame\s*)");
    const std::regex uci_positionCmd(R"((.*position\s*)(startpos|((?:[rnbqkpRNBQKP1-8]+/){7}[rnbqkpRNBQKP1-8]+)\s*([bw])\s*((-|[KQkq]){1,4})\s*(-|[a-h][1-8])\s*((\d)+\s*(\d)+))\s*(?:moves\s*(([a-h]\s*[1-8]\s*[a-h]\s*[1-8]\s*)+))?$)");
    const std::regex uci_goCmd(R"(go)");


    void uci_uci();
    void uci_debug(std::string mode);
    void uci_isready();
    void uci_newGame();
    void uci_position(ChessBoard* board, std::string details);
    void uci_go(ChessBoard* board, std::string details);
    
    // non uci functions
    void engine_display(const ChessBoard* board);
    void engine_moves(ChessBoard* board, std::string details);
    void engine_isCheck(ChessBoard* board, std::string details);
    void engine_isMate(ChessBoard* board, std::string details);


    bool loadFEN(ChessBoard* board, const std::string& fen);
}


