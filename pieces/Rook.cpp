#include "Rook.hpp"

/**
 * @brief Default Constructor. By default, Rooks have 3 available castle moves to make
 * @note Remember to default construct the base-class as well
 * @post Sets the piece_size_ member to 1. Sets the type to "PAWN"
 */
Rook::Rook() : ChessPiece(), castle_moves_left_{3} { setSize(2); setType("ROOK"); }

/**
* @brief Parameterized constructor. Rememeber to use the arguments to construct the underlying ChessPiece.
* @param : A const reference to the color of the Rook (a string). Set the color "BLACK" if the provided string contains non-alphabetic characters. 
*     If the string is purely alphabetic, it is converted and stored in uppercase
* @param : The 0-indexed row position of the Rook (as a const reference to an integer). Default value -1 if not provided, or if the value provided is outside the board's dimensions, [0, BOARD_LENGTH)
* @param : The 0-indexed column position of the Rook (as a const reference to an integer). Default value -1 if not provided, or if the value provided is outside the board's dimensions, [0, BOARD_LENGTH)
* @param : A flag indicating whether the Rook is moving up on the board, or not (as a const reference to a boolean). Default value false if not provided.
* @param : An integer representing how many castle moves it can make. Default to 3 if no value provided. If a negative value is provided, 0 is used instead.
* @post : The private members are set to the values of the corresponding parameters. 
*   If either of row or col are out-of-bounds and set to -1, the other is also set to -1 (regardless of being in-bounds or not).
*   The piece_size_ member is set to 1
*   The type member is set to "PAWN"
*/
Rook::Rook(const std::string& color, const int& row, const int& col, const bool& movingUp, const int& castle_moves_capacity) :
    ChessPiece(color, row, col, movingUp, 2, "ROOK"), castle_moves_left_{ std::max(0, castle_moves_capacity) } {}

/**
 * @brief Gets the value of the castle_moves_left_
 * @return The integer value stored in castle_moves_left_
 */
int Rook::getCastleMovesLeft() const {
    return castle_moves_left_;
}

/**
 * @brief Determines if this rook can castle with the parameter Chess Piece
 *     This rook can castle with another piece if:
 *        1. It has more than 0 castle moves available
 *        2. Both pieces share the same color
 *        3. Both pieces are considered on-the-board (no -1 rows or columns) and laterally adjacent (ie. they share the same row and their columns differ by at most 1)
 * @param ChessPiece A chess piece with which the rook may / may not be able to castle with
 * @return True if the rook can castle with the given piece. False otherwise.
 */
bool Rook::canCastle(const ChessPiece& target) const {
    // Ensure there are castle moves available & the pieces share color
    if (castle_moves_left_ == 0 || getColor() != target.getColor()) { return false; }

    // Ensure both pieces are on the board
    if (getRow() < 0 || getColumn() < 0 || target.getRow() < 0 || target.getColumn() < 0) { return false; }

    // Ensure they are in the same row or columns differ by at most 1 next to each other
    if (getRow() != target.getRow() || std::abs(getColumn() - target.getColumn()) > 1) { return false; }

    return true;
}

bool Rook::canMove(const int& target_row, const int& target_col, const std::vector<std::vector<ChessPiece*>>& board) const {
    // Not on the board 
    if (getRow() == -1 || getColumn() == -1) { return false; } 
    // Out of bounds target
    if (target_row < 0 || target_row >= BOARD_LENGTH || target_col < 0 || target_col >= BOARD_LENGTH) { return false; };
    

    // Account for castle in ChessBoard move()
    ChessPiece* target_piece = board[target_row][target_col];
    if (target_piece) {
        if (target_piece->getColor() == getColor()) { return false; }
        // if (canCastle(*target_piece)) { return true; } // It can only castle if it is adjacent anyway
    }
    
    // Get the difference between the current position and the target position
    // -,0,+  -->  represents left, no movement, right
    int row_difference = target_row - getRow(); 
    // -,0,+  -->  represents down, no movement, up
    int col_difference = target_col - getColumn(); 

    // Same cell OR not a horizontal / vertical line
    bool stays_in_same_position = (row_difference == 0) && (col_difference == 0);
    bool moves_straight = (row_difference == 0) || (col_difference == 0);
    if (stays_in_same_position || !moves_straight) { return false; }

    // Find what direction we should step 
    int increment_row = 0;
    int increment_col = 0;
    if (row_difference > 0) { increment_row = 1; }  // Moving right
    if (row_difference < 0) { increment_row = -1; } // Moving left

    if (col_difference > 0) { increment_col = 1; }  // Moving up
    if (col_difference < 0) { increment_col = -1; } // Moving down
    
    // Iterate from the original space to target space and check if there is any obstructing Chess Piece
    int temp_row = getRow();
    int temp_col = getColumn();

    while (temp_row != target_row || temp_col != target_col) {
        temp_row += increment_row;
        temp_col += increment_col;
        if (board[temp_row][temp_col]) { return false; }
    }

    return true;
}
