#include "Bishop.hpp"

/**
 * @brief Default Constructor.
 * @post Sets piece_size_ to 3 and type to "BISHOP"
 */
Bishop::Bishop() : ChessPiece() { setSize(3); setType("BISHOP"); }

/**
 * @brief Parameterized constructor.
 * @param color: The color of the Bishop.
 * @param row: 0-indexed row position of the Bishop.
 * @param col: 0-indexed column position of the Bishop.
 * @param movingUp: Flag indicating whether the Bishop is moving up.
 */
Bishop::Bishop(const std::string& color, const int& row, const int& col, const bool& movingUp)
    : ChessPiece(color, row, col, movingUp, 3, "BISHOP") {}

bool Bishop::canMove(const int& target_row, const int& target_col, const std::vector<std::vector<ChessPiece*>>& board) const {
    // Not on the board
    if (getRow() == -1 || getColumn() == -1) { return false; }

    // Out of bounds target
    if (target_row < 0 || target_row >= BOARD_LENGTH || target_col < 0 || target_col >= BOARD_LENGTH) { return false; }

    ChessPiece* target_piece = board[target_row][target_col];
    if (target_piece && target_piece->getColor() == getColor()) { return false; }

    int dx = target_row - getRow();
    int dy = target_col - getColumn();

    // Not a diagonal line or they lie on the same cell.
    bool not_diagonal = std::abs(dx) != std::abs(dy);
    bool no_movement = (dx == 0) && (dy == 0);
    if (not_diagonal || no_movement) { return false; }

    // Get sign of offsets: -1 if target is to the left or down, 1 if to the right or up.
    int row_offset = dx / std::abs(dx);
    int col_offset = dy / std::abs(dy);

    // Iterate from the target space to the original space and check if there is any obstructing ChessPiece

    while ((dx -= row_offset) != 0 && (dy -= col_offset) != 0) {
        if (board[getRow() + dx][getColumn() + dy]) {
            return false;
        }
    }

    return true;
}
