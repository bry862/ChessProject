#include "Pawn.hpp"

/**
 * @brief Default Constructor. All boolean values are default initialized to false.
 * @note Remember to default construct the base-class as well
 * @post Sets the piece_size_ member to 1. Sets the type to "PAWN"
 */
Pawn::Pawn() : ChessPiece() { setSize(1); setType("PAWN"); }

/**
* @brief Parameterized constructor.
* @param : A const reference to the color of the Pawn (a string). Set the color "BLACK" if the provided string contains non-alphabetic characters. 
*     If the string is purely alphabetic, it is converted and stored in uppercase
* @param : The 0-indexed row position of the Pawn (as a const reference to an integer). Default value -1 if not provided, or if the value provided is outside the board's dimensions, [0, BOARD_LENGTH)
* @param : The 0-indexed column position of the Pawn (as a const reference to an integer). Default value -1 if not provided, or if the value provided is outside the board's dimensions, [0, BOARD_LENGTH)
* @param : A flag indicating whether the Pawn is moving up on the board, or not (as a const reference to a boolean). Default value false if not provided.
* @post : The private members are set to the values of the corresponding parameters. 
*   If either of row or col are out-of-bounds and set to -1, the other is also set to -1 (regardless of being in-bounds or not).
*   The piece_size_ member is set to 1
*   The type member is set to "PAWN"
*/
Pawn::Pawn(const std::string& color, const int& row, const int& col, const bool& movingUp) :
    ChessPiece(color, row, col, movingUp, 1, "PAWN") {}

/**
 * @brief Determines whether a Pawn can perform a adouble jump or not.
 * @return The value stored in has_moved_
 */
bool Pawn::canDoubleJump() const {
    return !hasMoved();
}

/**
 * @brief Determines if this pawn can be promoted to another piece
 *     A pawn can be promoted if its row has reached the farthest row it can move up (or down) to. This is determined by the board size and the Piece's movingUp_ member.
 *
 *     EXAMPLE: If a pawn is movingUp and the board has 8 rows, then it can promoted only if it is in the 7th row (0-indexed)
 * @return True if this pawn can be promoted. False otherwise.
 */
bool Pawn::canPromote() const {
    return (isMovingUp() && getRow() == BOARD_LENGTH - 1) || 
        (!isMovingUp() && getRow() == 0);
}

// Either two forward, or diagonal to capture piece
bool Pawn::canMove(const int& target_row, const int& target_col, const std::vector<std::vector<ChessPiece*>>& board) const {
    // Not on the board 
    if (getRow() == -1 || getColumn() == -1) { return false; } 

    // Out of bounds target
    if (target_row < 0 || target_row >= BOARD_LENGTH || target_col < 0 || target_col >= BOARD_LENGTH) { return false; };

    ChessPiece* target_piece = board[target_row][target_col];
    if (target_piece && target_piece->getColor() == getColor()) { return false; }


    int direction = isMovingUp() ? 1 : -1;
    bool can_move_straight = 
        (!target_piece && getColumn() == target_col) && // Is moving straight (and there is noe obstructing piece)
        ((getRow() + direction == target_row) || (canDoubleJump() && getRow() + direction * 2 == target_row)); // Is moving by 1 or 2 rows (depending on the canDoubleJump flag)


    bool can_capture_diagonal =
        (target_piece && std::abs(getColumn() - target_col) == 1) && // Moving along some diagonal
        (getRow() + direction == target_row); // Moving along a diagonal they are facing


    return can_move_straight || can_capture_diagonal;
}