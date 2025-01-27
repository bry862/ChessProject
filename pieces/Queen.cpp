#include "Queen.hpp"

/**
 * @brief Default Constructor.
 * @post Sets piece_size_ to 9 and type to "QUEEN"
 */
Queen::Queen() : ChessPiece() { setSize(4); setType("QUEEN"); }

/**
 * @brief Parameterized constructor.
 * @param color: The color of the Queen.
 * @param row: 0-indexed row position of the Queen.
 * @param col: 0-indexed column position of the Queen.
 * @param movingUp: Flag indicating whether the Queen is moving up.
 */
Queen::Queen(const std::string& color, const int& row, const int& col, const bool& movingUp)
    : ChessPiece(color, row, col, movingUp, 4, "QUEEN") {}

bool Queen::canMove(const int& target_row, const int& target_col, const std::vector<std::vector<ChessPiece*>>& board) const {
    // Not on the board
    if (getRow() == -1 || getColumn() == -1) { return false; }

    // Out of bounds target
    if (target_row < 0 || target_row >= BOARD_LENGTH || target_col < 0 || target_col >= BOARD_LENGTH) { return false; }

    ChessPiece* target_piece = board[target_row][target_col];
    if (target_piece && target_piece->getColor() == getColor()) { return false; }

    int dx = target_row - getRow();
    int dy = target_col - getColumn();

    // Must move either straight or diagonal
    bool no_movement = (dx == 0) && (dy == 0);
    bool not_straight = dx != 0 && dy != 0;
    bool not_diagonal = std::abs(dx) != std::abs(dy);
    
    if (no_movement || (not_straight && not_diagonal)) { return false; }

    // EDIT BELOW.
    // Get sign of offsets: -1 if target is to the left or down, 0 if on the same vert/horizontal line, 1 if to the right or up.
    int row_offset = (dx) ? dx / std::abs(dx) : 0;
    int col_offset = (dy) ? dy / std::abs(dy) : 0;

    // Iterate from the target space to the original space and check if there is any obstructing Chess Piece
    while ((dx -= row_offset) != 0 && (dy -= col_offset) != 0) {
        if (board[getRow() + dx][getColumn() + dy]) {
            return false;
        }
    }

    return true;
}
