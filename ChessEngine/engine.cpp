#include <iostream>
#include <string>
#include <regex>
#include "ChessBoard.h"
#include "Commands.h"




int main() {
    // Initialize a ChessBoard
    ChessBoard gameBoard;


    bool setup = false;

    // handle command identification on this thread, handle command processing on a seperate thread.
    while (true)
    {

        std::string command;
        std::getline(std::cin, command);
        
        if (std::regex_match(command, commands::engine_displayCmd)) {
            commands::engine_display(&gameBoard);
        }

        else if (std::regex_match(command, commands::uci_positionCmd)) {
            commands::uci_position(&gameBoard, command);
        }

        else if (std::regex_match(command, commands::uci_uciCmd)) {
            commands::uci_uci();
        }

        else if (std::regex_match(command, commands::uci_goCmd)) {
            commands::uci_go(&gameBoard, command);
        }

        else if (std::regex_match(command, commands::engine_movesCmd)) {
            commands::engine_moves(&gameBoard, command);
        }

        else if (std::regex_match(command, commands::engine_isCheckCmd)) {
            commands::engine_isCheck(&gameBoard, command);
        }

        else if (std::regex_match(command, commands::engine_isMateCmd)) {
            commands::engine_isMate(&gameBoard, command);
        }

        else if (std::regex_match(command, commands::engine_pieceCmd)) {
            commands::engine_piece(&gameBoard, command);
        }

        else if (std::regex_match(command, commands::engine_moveCmd)) {
            commands::engine_move(&gameBoard, command);
        }

    }

    return 0;
}