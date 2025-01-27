#include "ChessBoard.hpp"

/**
 * Colors the given text using the specified color code.
 *
 * This function uses ANSI escape sequences to color the input text.
 *
 * @param text The text to be colored.
 * @param color The desired color name.
 * @return The colored text string, or the original text if the color is not found.
 */
std::string BoardColorizer::colorText(const std::string& text, const std::string& color) {
    std::unordered_map<std::string, std::string> COLOR_CODES = {
        {"BLACK", "\033[1;90m"},
        {"RED", "\033[1;31m"},
        {"GREEN", "\033[1;32m"},
        {"YELLOW", "\033[1;33m"},
        {"BLUE", "\033[1;34m"},
        {"MAGENTA", "\033[1;35m"},
        {"CYAN", "\033[1;36m"},
        {"WHITE", "\033[1;37m"}
    };
    
    const std::string& code = COLOR_CODES[color];
    if (code.empty()) { return text; }
    return code + text + "\033[0m";
}

/**
    * Default constructor. 
    * @post The board is setup with the following restrictions:
    * 1) board is initialized to a 8x8 2D vector of ChessPiece pointers
    *      - ChessPiece derived classes are dynamically allocated and constructed as follows:
    *          - Pieces on the BOTTOM half of the board are set to have color "BLACK"
    *          - Pieces on the UPPER half of the board are set to have color "WHITE"
    *          - Their row & col members reflect their position on the board
    *          - All pawns on the BOTTOM half are flagged to be moving up.
    *          - All pawns on the BOTTOM half are flagged to be NOT moving up.
    *          - All other parameters are default initialized (this includes moving_up for non-Pawns!)
    *   
    *      - Pawns (P), Rooks(R), Bishops(B), Kings(K), Queens(Q), and Knights(N) are placed in the following format (ie. the standard setup for chess):
    *          
    *          7 | R N B K Q B N R
    *          6 | P P P P P P P P
    *          5 | * * * * * * * *
    *          4 | * * * * * * * *
    *          3 | * * * * * * * *
    *          2 | * * * * * * * *
    *          1 | P P P P P P P P
    *          0 | R N B K Q B N R
    *              +---------------
    *              0 1 2 3 4 5 6 7
    *      
    *          (With * denoting empty cells)
    * 
    * 2) playerOneTurn is set to true.
    * 3) p1_color is set to "BLACK", and p2_color is set to "WHITE"
    */
ChessBoard::ChessBoard(const std::string& assignedColorP1, const std::string& assignedColorP2)
    : playerOneTurn{true}, p1_color{assignedColorP1}, p2_color{assignedColorP2}, board{std::vector(8, std::vector<ChessPiece*>(8)) } {
        
        // If the colors used are not available, or if we've specified the same color for Player One & Two
        // default to BLACK and WHITE
        bool initializedInvalidColor = !BoardColorizer::ALLOWED_COLORS.count(p1_color) || !BoardColorizer::ALLOWED_COLORS.count(p2_color);
        if (initializedInvalidColor || p1_color == p2_color) {
            p1_color = "BLACK";
            p2_color = "WHITE";
        }

        // Allocate pieces
        auto add_mirrored = [this] (const int& i, const std::string& type) {
            if (type == "PAWN") {
                board[1][i] = new Pawn(p1_color, 1, i, true);
                board[6][i] = new Pawn(p2_color, 6, i);
            } else if (type == "ROOK") {
                board[0][i] = new Rook(p1_color, 0, i);
                board[7][i] = new Rook(p2_color, 7, i);
            } else if (type == "KNIGHT") {
                board[0][i] = new Knight(p1_color, 0, i);
                board[7][i] = new Knight(p2_color, 7, i);            
            } else if (type == "BISHOP") {
                board[0][i] = new Bishop(p1_color, 0, i);
                board[7][i] = new Bishop(p2_color, 7, i);
            } else if (type == "KING") {
                board[0][i] = new King(p1_color, 0, i);
                board[7][i] = new King(p2_color, 7, i);
            } else if (type == "QUEEN") {
                board[0][i] = new Queen(p1_color, 0, i);
                board[7][i] = new Queen(p2_color, 7, i);
            }
        };

        std::vector<std::string> inner_pieces = {"ROOK", "KNIGHT", "BISHOP", "KING", "QUEEN", "BISHOP", "KNIGHT", "ROOK"};
        for (size_t i = 0; i < BOARD_LENGTH; i++) {
            add_mirrored(i, "PAWN");
            add_mirrored(i, inner_pieces[i]);
        }

        // Track all added pieces from the board.
        for (size_t row = 0; row < BOARD_LENGTH; row++) {
            for (size_t col = 0; col < BOARD_LENGTH; col++) {
                if (!board[row][col]) { continue; }
                pieces.push_front(board[row][col]);
            }
        }
    }

/**
 * Constructs a ChessBoard object.
 *
 * This constructor initializes the chessboard with the provided 2D vector of 
 * ChessPiece* pointers. It also tracks all non-null pieces on the board.
 *
 * @param instance The state of the chessboard to copy, represented as a 
 *                 2D vector of ChessPiece* pointers.
 * @param p1Turn   A boolean indicating whether it's Player 1's turn to play.
 */
ChessBoard::ChessBoard(const std::vector<std::vector<ChessPiece*>>& instance, const bool& p1Turn) : playerOneTurn{p1Turn}, p1_color{"BLACK"}, p2_color{"WHITE"}, board{instance} {
    // Track all added pieces from the board.
    for (size_t row = 0; row < BOARD_LENGTH; row++) {
        for (size_t col = 0; col < BOARD_LENGTH; col++) {
            if (!board[row][col]) { continue; }
            pieces.push_front(board[row][col]);
        }
    }
}

/**
 * @brief Gets the ChessPiece (if any) at (row, col) on the board
 * 
 * @param row The row of the cell
 * @param col The column of the cell
 * @return ChessPiece* A pointer to the ChessPiece* at the cell specified by (row, col) on the board
 */
ChessPiece* ChessBoard::getCell(const int& row, const int& col) const {
    return board[row][col];
}

/**
 * @brief Getter for board_ member
 */
std::vector<std::vector<ChessPiece*>> ChessBoard::getBoardState() const {
    return board;
}

/**
 * @brief Destructor. 
 * @post Deallocates all ChessPiece pointers that were ever used on the board.
 */
ChessBoard::~ChessBoard() {
    for (auto& piece_ptr : pieces) {
        if (!piece_ptr) { continue; }
        delete piece_ptr;
        piece_ptr = nullptr;
    }
}

/**
 * @brief Utility display function that prints out colored text
 *        based on the players' colors
 * @pre P1_COLOR & P2_COLOR are exist 
 *      within the BoardColorizer ALLOWED_COLORS vector
 * 
 * @post Display row / column headers & symbols for pieces on the board
 *       where each piece is colored based on the color representing the 
 *       player they belong to
 */
void ChessBoard::display() const {
    // Extract piece symbol logic
    // 1) Nullptr (empty space) -> *
    // 2) Knight -> N; otherwise get first character of type
    auto getPieceSymbol = [this](ChessPiece* piece) {
        if (!piece) { return std::string(1, '*'); }
        
        char symbol = 
        (piece->getType() == "KNIGHT") 
            ? 'N' 
            : piece->getType()[0];
        
        // Give colored text based on piece color
        return BoardColorizer::colorText(std::string(1, symbol), piece->getColor());
    };

    // Print frame & cells
    for (int row = BOARD_LENGTH - 1; row >= 0; row--) {
        std::cout << row << " | ";
        for (size_t col = 0; col < BOARD_LENGTH; col++) {
            std::cout << getPieceSymbol(board[row][col]) << " ";
        }
        std::cout << std::endl;
    }

    // Pad left with spaces, add horizontal line
    std::cout << std::string(4, ' ') << std::string(15, '-') << std::endl;
    std::cout << std::string(4, ' ');
    
    // Label columns
    for (size_t col = 0; col < BOARD_LENGTH; col++) { std::cout << col << " "; }
    std::cout << std::endl;
}

/**
* @brief Moves the piece at (row,col) to (new_row, new_col), if possible
* 
* @return True if the move was successfullcol executed. 
* 
*      A move is possible if:
*      1) (row,col) is a valid space on the board ( ie. within [0, BOARD_LENGTH) )
*      2) There exists a piece at (row,col)
*      3) The color of the piece equals the color of the current player whose turn it is
*      4) The piece "can move" to the target location (new_row, new_col) 
*           and (if applicable) the piece being captured is not of type "KING"
* 
*      Otherwise the move is invalid and nothing occurs / false is returned.
* 
* @post If the move is possible, it is executed
*      - board is updated to reflect the move
*      - The moved piece's row and col members are updated to reflect the move
*      If a pawn is moved from its start position, its double_jumpable_ flag is set to false.. 
*/
bool ChessBoard::move(const int& row, const int& col, const int& new_row, const int& new_col) {
    if (row < 0 || col < 0 || row >= BOARD_LENGTH || col >= BOARD_LENGTH) { return false; }
    ChessPiece* movingPiece = board[row][col];
    const std::string& colorInPlay = (playerOneTurn) ? p1_color : p2_color;
    // If there is no piece to move or it is of the opposite color, terminate
    if (!movingPiece) { return false; }
    if (movingPiece->getColor() != colorInPlay) { return false; }

    // If we can't move, terminate
    if (!movingPiece->canMove(new_row, new_col, board)) { return false; }

    // Store captured piece
    ChessPiece* captured_piece = board[new_row][new_col];

    // Cannot capture a King in chess
    if (captured_piece && captured_piece->getType() == "KING") { return false; }
    
    // Update moved piece
    board[new_row][new_col] = movingPiece;

    // Valid logic unless for castle, but for simplicity's sake, we'll leave that out for now.
    board[row][col] = nullptr;

    movingPiece->setRow(new_row);
    movingPiece->setColumn(new_col);
    movingPiece->flagMoved();
    
    return true;
}