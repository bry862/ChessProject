#pragma once

#include <iostream>
#include <vector>
#include "ChessPiece.hpp"


/**
 * @brief Knight class inheriting from ChessPiece.
 */
class Knight : public ChessPiece {
public:
    /**
     * @brief Default Constructor for Knight. 
     * @post Sets piece_size_ to 3 and type to "KNIGHT"
     */
    Knight();

    /**
     * @brief Parameterized constructor.
     * @param color: The color of the Knight.
     * @param row: 0-indexed row position of the Knight.
     * @param col: 0-indexed column position of the Knight.
     * @param movingUp: Flag indicating whether the Knight is moving up on the board.
     */
    Knight(const std::string& color, const int& row = -1, const int& col = -1, const bool& movingUp = false);

    bool canMove(const int& target_row, const int& target_col, const std::vector<std::vector<ChessPiece*>>& board) const override;
};