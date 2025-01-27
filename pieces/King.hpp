#pragma once

#include <iostream>
#include <vector>
#include "ChessPiece.hpp"


/**
 * @brief King class inheriting from ChessPiece.
 */
class King : public ChessPiece {
public:
    /**
     * @brief Default Constructor for King. 
     * @post Sets piece_size_ to 4 and type to "KING"
     */
    King();

    /**
     * @brief Parameterized constructor.
     * @param color: The color of the King.
     * @param row: 0-indexed row position of the King.
     * @param col: 0-indexed column position of the King.
     * @param movingUp: Flag indicating whether the King is moving up on the board.
     */
    King(const std::string& color, const int& row = -1, const int& col = -1, const bool& movingUp = false);

    bool canMove(const int& target_row, const int& target_col, const std::vector<std::vector<ChessPiece*>>& board) const override;
};