#pragma once

#include <iostream>
#include <vector>
#include "ChessPiece.hpp"


/**
 * @brief Queen class inheriting from ChessPiece.
 */
class Queen : public ChessPiece {
public:
    /**
     * @brief Default Constructor for Queen. 
     * @post Sets piece_size_ to 4 and type to "QUEEN"
     */
    Queen();

    /**
     * @brief Parameterized constructor.
     * @param color: The color of the Queen.
     * @param row: 0-indexed row position of the Queen.
     * @param col: 0-indexed column position of the Queen.
     * @param movingUp: Flag indicating whether the Queen is moving up on the board.
     */
    Queen(const std::string& color, const int& row = -1, const int& col = -1, const bool& movingUp = false);

    bool canMove(const int& target_row, const int& target_col, const std::vector<std::vector<ChessPiece*>>& board) const override;
};