#ifndef MOVEGENERATION_H
#define MOVEGENERATION_H
#include "externs.h"

#include <string>



class moveGeneration
{
public:
    moveGeneration();
    void returnMove();
    void resetPossibleMoves();

private:

//generate moves
    void blackPawn(int x, int y);
    void whitePawn(int x, int y);
    void rook(int x, int y);
    void knight(int x, int y);
    void bishop(int x, int y);
    void queen(int x, int y);
    void king(int x, int y);

//Move calculations
    int calculateBestMove();

    //find total board values
    float evaluateBoard();
    //pice values and abs val for black and white
    float getPieceValue(std::string piece, int x, int y);
    float getAbsoluteValue((std::string piece, int x, int y);


    //Piece evaluation arrays


//moves into vector %4
    void pushMoves(int x, int y, int x2, int y2);
};

#endif // MOVEGENERATION_H
