#include "King.hpp"

/**
 * @brief Default Constructor.
 * @post Sets piece_size_ to 4 and type to "KING"
 */
King::King() : ChessPiece() { setSize(4); setType("KING"); }

/**
 * @brief Parameterized constructor.
 * @param color: The color of the King.
 * @param row: 0-indexed row position of the King.
 * @param col: 0-indexed column position of the King.
 * @param movingUp: Flag indicating whether the King is moving up.
 */
King::King(const std::string& color, const int& row, const int& col, const bool& movingUp)
    : ChessPiece(color, row, col, movingUp, 4, "KING") {}

bool King::canMove(const int& target_row, const int& target_col, const std::vector<std::vector<ChessPiece*>>& board) const {
    // Check for bounds and on_board
    if (getRow() == -1 || getColumn() == -1) { return false; } 
    if (target_row < 0 || target_row >= BOARD_LENGTH || target_col < 0 || target_col >= BOARD_LENGTH) { return false; } 

    ChessPiece* target_piece = board[target_row][target_col];
    if (target_piece && target_piece->getColor() == getColor()) { return false; }

    return (target_row != getRow() || target_col != getColumn() ) &&  
        (std::abs(target_row - getRow()) <= 1 && std::abs(target_col - getColumn()) <= 1);
}