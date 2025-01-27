#pragma once

#include <iostream>
#include "ChessPiece.hpp"

/**
 * @brief Bishop class inheriting from ChessPiece.
 */
class Bishop : public ChessPiece {
public:
    /**
     * @brief Default Constructor for Bishop. 
     * @post Sets piece_size_ to 3 and type to "BISHOP"
     */
    Bishop();

    /**
     * @brief Parameterized constructor.
     * @param color: The color of the Bishop.
     * @param row: 0-indexed row position of the Bishop.
     * @param col: 0-indexed column position of the Bishop.
     * @param movingUp: Flag indicating whether the Bishop is moving up on the board.
     */
    Bishop(const std::string& color, const int& row = -1, const int& col = -1, const bool& movingUp = false);

    bool canMove(const int& target_row, const int& target_col, const std::vector<std::vector<ChessPiece*>>& board) const override;
};