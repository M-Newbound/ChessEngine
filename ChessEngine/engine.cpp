#include <iostream>
#include <string>
#include <cctype>
#include <regex>
#include <vector>
#include "ChessBoard.h"
#include "MoveGeneration.h"
#include "BoardEvaluation.h"
#include "Commands.h"

#include <chrono>

#include <bitset>




int main() {
    // Initialize a ChessBoard
    ChessBoard gameBoard;


    bool setup = false;

    // handle command identification on this thread, handle command processing on a seperate thread.
    while (true)
    {

        std::string command;
        std::getline(std::cin, command);
        
        if (std::regex_match(command, commands::displayboardCmdRegex)) {
            commands::displayBoard(&gameBoard);
        }

        if (std::regex_match(command, commands::uci_positionCmd)) {
            commands::uci_position(&gameBoard, command);
        }

        
    }







    // Example FEN string for starting position:
      std::string fenStart = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
      std::string fenExample = "rnbqkbnr / 1pp1pppp / 8 / p2p4 / 2B1P3 / 5N2 / PPPP1PPP / RNBQK2R";
      std::string fenBlackCheckmate = "3rkbnr/1p1bp3/1q1p3p/p5pQ/3n4/PPR5/5PPP/6K1";
      std::string fenBlackNearCheckmate = "3rkbnr/1p1bp3/1q1p3p/p5p1/3n4/PPR2Q2/5PPP/6K1";




        //std::vector<ChessMove> moves = MoveGeneration::generateLegalMoves(&myBoard, false);

        //for (ChessMove move : moves) {
         //   std::cout << "from " << unsigned(move.fromSquare) << " to " << unsigned(move.toSquare) << std::endl;
        //}




    return 0;
}