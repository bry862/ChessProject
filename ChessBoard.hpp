/**
 * @class ChessBoard
 * @brief Represents an 8x8 board of Chess Pieces used to play chess
 */

#pragma once

#include <limits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#include "pieces_module.hpp"

namespace BoardColorizer {
    /*
    Specify the colors we have color codes for.
    */
    const std::unordered_set<std::string> ALLOWED_COLORS({"BLACK", "RED", "GREEN", "YELLOW", "BLUE", "MAGENTA", "CYAN", "WHITE"});

    /**
     * Colors the given text using the specified color code.
     *
     * This function uses ANSI escape sequences to color the input text.
     *
     * @param text The text to be colored.
     * @param color The desired color name.
     * @return The colored text string, or the original text if the color is not found.
     */
    std::string colorText(const std::string& text, const std::string& color);
};
class ChessBoard {
    private:
        // Define board size (8x8)
        static const int BOARD_LENGTH = 8;
        
        bool playerOneTurn;
        
        std::string p1_color;
        std::string p2_color;

        // Track the board state & all pieces that were ever in play
        std::vector<std::vector<ChessPiece*>> board;
        std::list<ChessPiece*> pieces;

    public:
        /**
         * Default / Parameterized constructor. 
         * @pre assignedColorP1 & assignedColorP2 represent colors present in the ALLOWED_COLORS list
         * 
         * @param assignedColorP1 A string denoting the color to use for Player One
         * @param assignedColorP2 A string denoting the color to use for Player Two
         * 
         * @post The board is setup with the following restrictions:
         * 1) board is initialized to a 8x8 2D vector of ChessPiece pointers
         *      - ChessPiece derived classes are dynamically allocated and constructed as follows:
         *          - Pieces on the BOTTOM half of the board are set to be "moving up" | of color "BLACK"
         *          - Pieces on the UPPER half of the board are set to be NOT "moving up"| of color "WHITE"
         *          - Their row & col members reflect their position on the board
         *          - All other parameters are default initialized.
         *   
         *      - Pawns (P), Rooks(R), Bishops(B), Kings(K), Queens(Q), and Knights(N) are placed in the following format (ie. the standard setup for chess):
         *          
         *          7 | R N B K Q B N R
         *          6 | P P P P P P P P
         *          5 | * * * * * * * *
         *          4 | * * * * * * * *
         *          3 | * * * * * * * *
         *          2 | * * * * * * * *
         *          1 | P P P P P P P P
         *          0 | R N B K Q B N R
         *              +---------------
         *              0 1 2 3 4 5 6 7
         *      
         *          (With * denoting empty cells)
         * 
         * 2) playerOneTurn is set to true.
         * 3) p1_color is set to "BLACK", and p2_color is set to "WHITE" if not provided, or they are equal
         */
        ChessBoard(const std::string& assignedColorP1 = "BLACK", const std::string& assignedColorP2 = "WHITE");

        /**
         * Constructs a ChessBoard object.
         *
         * This constructor initializes the chessboard with the provided 2D vector of 
         * ChessPiece* pointers. It also tracks all non-null pieces on the board.
         *
         * @param instance The state of the chessboard to copy, represented as a 
         *                 2D vector of ChessPiece* pointers.
         * @param p1Turn   A boolean indicating whether it's Player 1's turn to play.
         */
        ChessBoard(const std::vector<std::vector<ChessPiece*>>& board, const bool& p1Turn);

        /**
         * @brief Getter for board_ member
         */
        std::vector<std::vector<ChessPiece*>> getBoardState() const;

        /**
        * @brief Moves the piece at (row,col) to (new_row, new_col), if possible
        * 
        * @return True if the move was successfullcol executed. 
        * 
        *      A move is possible if:
        *      1) (row,col) is a valid space on the board ( ie. within [0, BOARD_LENGTH) )
        *      2) There exists a piece at (row,col)
        *      3) The color of the piece equals the color of the current player whose turn it is
        *      4) The piece "can move" to the target location (new_row, new_col) 
        *           and (if applicable) the piece being captured is not of type "KING"
        * 
        *      Otherwise the move is invalid and nothing occurs / false is returned.
        * 
        * @post If the move is possible, it is executed
        *      - board is updated to reflect the move
        *      - The moved piece's row and col members are updated to reflect the move
        *      If a pawn is moved from its start position, its double_jumpable_ flag is set to false.. 
        */
        bool move(const int& x, const int& y, const int& new_x, const int& new_y);

        /**
         * @brief Gets the ChessPiece (if any) at (row, col) on the board
         * 
         * @param row The row of the cell
         * @param col The column of the cell
         * @return ChessPiece* A pointer to the ChessPiece* at the cell specified by (row, col) on the board
         */
        ChessPiece* getCell(const int& row, const int& col) const;

        /**
         * @brief Destructor. 
         * @post Deallocates all ChessPiece pointers that were ever used on the board.
         */
        ~ChessBoard();
        
        /**
         * @brief Utility display function that prints out colored text
         *        based on the players' colors
         * @pre P1_COLOR & P2_COLOR are exist 
         *      within the BoardColorizer ALLOWED_COLORS vector
         * 
         * @post Display row / column headers & symbols for pieces on the board
         *       where each piece is colored based on the color representing the 
         *       player they belong to
         */
        void display() const;
};