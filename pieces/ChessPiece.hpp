/**
 * @class ChessPiece
 * @brief Represents a generic chess piece.
 * 
 * This class serves as the base class for all chess pieces.
 */

#pragma once
#include <iostream>
#include <cctype>
#include <vector>

class ChessPiece {
   protected:
      static const int BOARD_LENGTH = 8; // A constant value representing the number of rows & columns on the chessboard

   private:
      std::string color_;  // An uppercase, alphabetic string representing the color of the chess piece.

      /** Consider an 8x8 grid with the following indexing:
         *  7 | * * * * * * * *
         *  6 | * * * * * * * *
         *  5 | * * * * * * * *
         *  4 | * * * * * * * *
         *  3 | * * * * * * * *
         *  2 | * * * * * * * *
         *  1 | * * * * * * * *
         *  0 | * * * * * * * *
         *    +---------------
         *      0 1 2 3 4 5 6 7
      */


      int row_;               // An integer corresponding to the row position of the chess piece
      int column_;            // An integer corresponding to the column position of the chess piece
      bool movingUp_;         // A boolean representing whether the piece is moving up the board (in reference to the visual above)
      int piece_size_;        // An integer representing the size of the current chess piece
      std::string type_;      // A string representing the type of the current chess piece
      bool has_moved_;

   protected:
      void setSize(const int& size);
      void setType(const std::string& type);

   public:

   // =============== Constructors ===============
   
   /**
    * @brief Default Constructor : All values 
    * Default-initializes all private members.  
    * Booleans are default-initialized to False. 
    * Default color : "BLACK"
    * Default row & columns: -1 (ie. represents that it has not been put on the board yet)
    * Default piece_size: 0
    */
   ChessPiece();

     /**
    * @brief Parameterized constructor.
    * @param : A const reference to the color of the Chess Piece (a string). Set the color "BLACK" if the provided string contains non-alphabetic characters. 
    *     If the string is purely alphabetic, it is converted and stored in uppercase
    * @param : The 0-indexed row position of the Chess Piece (as a const reference to an integer). Default value -1 if not provided, or if the value provided is outside the board's dimensions, [0, BOARD_LENGTH)
    * @param : The 0-indexed column position of the Chess Piece (as a const reference to an integer). Default value -1 if not provided, or if the value provided is outside the board's dimensions, [0, BOARD_LENGTH)
    * @param : A flag indicating whether the Chess Piece is moving up on the board, or not (as a const reference to a boolean). Default value false if not provided.
    * @post : The private members are set to the values of the corresponding parameters. 
    *   If either of row or col are out-of-bounds and set to -1, the other is also set to -1 (regardless of being in-bounds or not).
    *   Default piece_size: 0
    */
   ChessPiece(const std::string& color, const int& row = -1, const int& col = -1, const bool& movingUp = false, const int& size = 0, const std::string& type="NONE");

   // =============== Getters and Setters ===============

   /**
    * @brief Gets the color of the chess piece.
    * @return The value stored in color_
    */
   std::string getColor() const;

   /**
    * @brief Sets the color of the chess piece.
    * @param color A const string reference, representing the color to set the piece to. 
    *     If the string contains non-alphabetic characters, the value is not set (ie. nothing happens)
    *     If the string is alphabetic, then all characters are converted and stored in uppercase
    * @post The color_ member variable is updated to the parameter value in uppercase
    * @return True if the color was set. False otherwise.
    */
   bool setColor(const std::string& color);

   /**
    * @brief Gets the row position of the chess piece.
    * @return The integer value stored in row_
    */
   int getRow() const;

   /**
    * @brief Sets the row position of the chess piece 
    * @param row A const reference to an integer representing the new row of the piece 
    *  If the supplied value is outside the board dimensions [0, BOARD_LENGTH), the ChessPiece is considered to be taken off the board, and its row AND column are set to -1 instead.
    */
   void setRow(const int& row);

   /**
    * @brief Gets the column position of the chess piece.
    * @return The integer value stored in column_
    */
   int getColumn() const;

   /**
    * @brief Sets the column position of the chess piece 
    * @param row A const reference to an integer representing the new column of the piece 
    *  If the supplied value is outside the board dimensions [0, BOARD_LENGTH), the ChessPiece is considered to be taken off the board, and its row AND column are set to -1 instead.
    */
   void setColumn(const int& column);

   /**
    * @brief Gets the value of the flag for if a chess piece is moving up
    * @return The boolean value stored in movingUp_
    */
   bool isMovingUp() const;

   /**
    * @brief Sets the movingUp flag of the chess piece 
    * @param flag A const reference to an boolean representing whether the piece is now moving up or not
    */
   void setMovingUp(const bool& flag);

   /**
    * @brief Displays the chess piece's information in the following format, if it is considered on the board (ie. its row and col are not -1):
    * <COLOR> piece at (row, col) is moving <UP / DOWN>\n
    * 
    * Otherwise an alternative format is used:
    * <COLOR> piece is not on the board\n
    * @note "\n" just means endline in this case. Please use "std::endl," don't hardcode "\n".
    */
   void display() const;

   /**
    * @brief Getter for the piece_size_ data member
    */
   int size() const;


   /**
    * @brief Getter for the type_ data member
    */
   std::string getType() const;
   
   /**
     * @brief Determines whether the ChessPiece can move to the specified target position on the board.
     * @note This function is pure virtual, so its implementation will 
     *       be left to its derived classes
     * 
     * @return True if the ChessPiece can move to the specified position; false otherwise.
     */
   virtual bool canMove(const int& target_row, const int& target_col, const std::vector<std::vector<ChessPiece*>>& board) const = 0;

   /**
    * @brief Determines whether a ChessPiece has moved on the board
    * @return The value stored in the `has_moved_` member
    */
   bool hasMoved() const;

   /**
    * @brief Sets a ChessPiece's `has_moved_` member to true
    */
   void flagMoved();
};