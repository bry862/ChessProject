#include "pieces_module.hpp"
#include "ChessBoard.hpp"
/*Notes: 
1. Remember to remove the destructor on ChessPiece hpp. Comment out line 73
2. I implemeted a getter for playerOne turn



*/

int main() {

    ChessBoard board1;

    board1.display();

    int x= 1;

    while (x>0){
        
        bool flag = board1.attemptRound();
        std::cout<<"TEST from MAIN, return was: " <<flag <<std::endl;
        board1.display();
    }

    return 0;
}