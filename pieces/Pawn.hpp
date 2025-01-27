#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include "ChessPiece.hpp"

class Pawn : public ChessPiece {
    public:
        /**
         * @brief Default Constructor. All boolean values are default initialized to false.
         * @note Remember to construct the base-class as well
         */
        Pawn();

        /**
        * @brief Parameterized constructor.
        * @param : A const reference to the color of the Pawn (a string). Set the color "BLACK" if the provided string contains non-alphabetic characters. 
        *     If the string is purely alphabetic, it is converted and stored in uppercase.
        *     NOTE: We do not supply a default value for color, the first parameter. Notice that if we do, we override the default constructor.
        * @param : The 0-indexed row position of the Pawn (as a const reference to an integer). Default value -1 if not provided, or if the value provided is outside the board's dimensions, [0, BOARD_LENGTH)
        * @param : The 0-indexed column position of the Pawn (as a const reference to an integer). Default value -1 if not provided, or if the value provided is outside the board's dimensions, [0, BOARD_LENGTH)
        * @param : A flag indicating whether the Pawn is moving up on the board, or not (as a const reference to a boolean). Default value false if not provided.
        * @post : The private members are set to the values of the corresponding parameters. 
        *   If either of row or col are out-of-bounds and set to -1, the other is also set to -1 (regardless of being in-bounds or not).
        */
        Pawn(const std::string& color, const int& row = -1, const int& col = -1, const bool& movingUp = false);

        /**
         * @brief Gets the value of the flag for the Pawn can double jump
         * @return The boolean value stored in double_jumpable_
         */
        bool canDoubleJump() const;


        /**
         * @brief Determines if this pawn can be promoted to another piece
         *     A pawn can be promoted if its row has reached the farthest row it can move up (or down) to. This is determined by the board size and the Piece's movingUp_ member.
         *
         *     EXAMPLE: If a pawn is movingUp and the board has 8 rows, then it can promoted only if it is in the 7th row (0-indexed)
         * @return True if this pawn can be promoted. False otherwise.
         */
        bool canPromote() const;

        bool canMove(const int& target_row, const int& target_col, const std::vector<std::vector<ChessPiece*>>& board) const override;
};