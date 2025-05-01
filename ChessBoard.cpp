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

        /**
     * @brief Attempts to execute a round of play on the chessboard. A round consists of the 
     * following sequence of actions:
     * 
     * 1) Prompts the user to select a piece by entering two space-separated integers 
     *    or type anything else to undo the last move
     * 2) Records their input, or returns the result of attempting to undo the previous action
     * 3) Prompt the user to select a target square to move the piece 
     *    or type anything else to undo.
     * 4) Records their input, or returns the result of attempting to undo the previous action
     * 5) Attempt to execute the move, using move()
     * 6) If the move is successful, records the action by pushing a Move to past_moves_.
     * 7) If the move OR undo is successful, toggles the `playerOneTurn` boolean member of `ChessBoard`
     * 
     * @return Returns true if the round has been completed successfully, that is:
     *      - If a pieced was succesfully moved.
     *      - Or a move was successfully undone.
     * @post The `past_moves_` stack & `playerOneTurn` members are updated as described above
     */
    bool ChessBoard:: attemptRound(){

        std::string player_in_turn = playerOneTurn? "Player 1": "Player 2";
        Square target_piece;
        Square target_location;

        //Step 1: Select a piece to move
        std::cout << "[" <<player_in_turn << "]" << "Select a piece (Enter two integers: '<row> <col>'), or any other input to undo the last action." <<std::endl;
       
        //Step 2: Record the input
        std::cin>>target_piece.first;
        std::cin>>target_piece.second;

        //Undo on the first input
        if (std::cin.fail()){

            std::cin.clear();
            //Place holder. I need to figure out how to detemrine if the stack is not emty to we can pop in the first place. 
            if(undo()){
                
                std::string player_in_turn = playerOneTurn? "Player 1": "Player 2";
                return 1;
            }

            //No move to undo!
            else{
                return false;
            }
        }

        //Step 3: Place to move to
        std::cout << "[" <<player_in_turn << "]" << "Specify a square to move to (Enter two integers: '<row> <col>'), or any other input to undo the last action." <<std::endl;
        
        //step 4: Record the input
        std::cin>>target_location.first;
        std::cin>>target_location.second;

        //undo on the second input
        if (std::cin.fail()){

            std::cin.clear();
            //Place holder. I need to figure out how to detemrine if the stack is not emty to we can pop in the first place. 
            if(undo()){
                 
                std::string player_in_turn = playerOneTurn? "Player 1": "Player 2";
                return 1;
                
            }

            else{
                return false;
            }
        }


        
        //step 5: Attempt to move
        bool vaild_move = move(target_piece.first, target_piece.second, target_location.first, target_location.second);
        
        //Step 6: If move is successful 
        if (vaild_move){
            
            std::cout<<"Moved ("<<target_piece.first<<", "<<target_piece.second<<") to ("<<target_location.first << ", "<< target_location.second<<")" <<std::endl;

            //we will make a move object
            ChessPiece* piece_ptr = board[target_location.first][target_location.second];
            Move new_move = Move (target_piece, target_location, piece_ptr);
            past_moves_.push(new_move);

            //Step 7: Toogle playerOneTurn 
            playerOneTurn = playerOneTurn? 0:1;
            return 1;
        }

        //Move unsucceful
        else {
            std::cout<<"Unable to move piece at ("<<target_piece.first<<", "<<target_piece.second<<") to ("<<target_location.first << ", "<< target_location.second<<")"<<std::endl ;
            return false;
            
        }


        

        //Debuggin
        // std::cout<<"Testing: <"<< past_moves_.top().getOriginalPosition().first << ", "<<past_moves_.top().getOriginalPosition().second<<"> : <"<< past_moves_.top().getTargetPosition().first<<", "<<past_moves_.top().getTargetPosition().second<<">" <<std::endl;
        // past_moves_.pop();
        // if (past_moves_.empty()){
        //     std::cout<<"The stack is empty";
        // }
    
    }

    /**
         * @brief Reverts the most recent action executed by a player,
         *        if there is a `Move` object in the `past_moves_` stack
         * 
         *        This is done by updating the moved piece to its original
         *        position, and the captured piece (if applicable) to the target
         *        position specified by the `Move` object at the top of the stack
         * 
         * @return True if the action was undone succesfully.
         *         False otherwise (ie. if there are no moves to undo)
         * 
         * @post 1) Reverts the `board` member's pointers to reflect
         *          the board state before the most recent move, if possible. 
         *       2) Updates the row / col members of each involved `ChessPiece` 
         *          (ie. the moved & captured pieces) to match their reverted 
         *          positions on the board
         *       3) The most recent `Move` object is removed from the `past_moves_`
         *          stack 
         */ 
    bool ChessBoard:: undo(){

        if (past_moves_.empty()){
            return false;
        }
        //First, move the piece back to where it was
        Move previous_move = past_moves_.top();

        //Print to confirm the move will be done
        std::cout<<"YES (" << (previous_move).getOriginalPosition().first <<", "<<(previous_move).getOriginalPosition().second << ") to ("
        << (previous_move).getTargetPosition().first << ", " << (previous_move).getTargetPosition().second<<") "<<std::endl;

        //Manually move
        board[previous_move.getOriginalPosition().first][previous_move.getOriginalPosition().second] = board [previous_move.getTargetPosition().first][previous_move.getTargetPosition().second];
        
        //Yes, I made it empty. If there was a captured it will be added later
        board [previous_move.getTargetPosition().first][previous_move.getTargetPosition().second] = nullptr; 
        
        if ( previous_move.getCapturedPiece()){
            board [previous_move.getTargetPosition().first][previous_move.getTargetPosition().second] = previous_move.getCapturedPiece();
        }

        //Always pop
        past_moves_.pop();



        return true;

    }