#include "Knight.hpp"

/**
 * @brief Default Constructor.
 * @post Sets piece_size_ to 3 and type to "KNIGHT"
 */
Knight::Knight() : ChessPiece() { setSize(3); setType("KNIGHT"); }

/**
 * @brief Parameterized constructor.
 * @param color: The color of the Knight.
 * @param row: 0-indexed row position of the Knight.
 * @param col: 0-indexed column position of the Knight.
 * @param movingUp: Flag indicating whether the Knight is moving up.
 */
Knight::Knight(const std::string& color, const int& row, const int& col, const bool& movingUp)
    : ChessPiece(color, row, col, movingUp, 3, "KNIGHT") {}

bool Knight::canMove(const int& target_row, const int& target_col, const std::vector<std::vector<ChessPiece*>>& board) const {
    // Not on the board
    if (getRow() == -1 || getColumn() == -1) { return false; }

    // Out of bounds target
    if (target_row < 0 || target_row >= BOARD_LENGTH || target_col < 0 || target_col >= BOARD_LENGTH) { return false; }

    ChessPiece* target_piece = board[target_row][target_col];
    if (target_piece && target_piece->getColor() == getColor()) { return false; }

    int abs_dx = std::abs(getRow() - target_row);
    int abs_dy = std::abs(getColumn() - target_col);

    // Check for an L-shape move pattern
    return (abs_dx == 1 && abs_dy == 2) || (abs_dx == 2 && abs_dy == 1);
}