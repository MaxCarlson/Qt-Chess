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

//vector of all possible moves for one side
    std::vector<int> possibleMoves;

//make vector of %4 moves into array of string moves
    void ugly_moves();

//more readable moves
    std::vector<std::string> neatMoves;

private:

//generate moves   
    void blackPawn(int x, int y);
    void whitePawn(int x, int y);
    void rook(int x, int y);
    void knight(int x, int y);
    void bishop(int x, int y);
    void queen(int x, int y);
    void king(int x, int y);

//moves into vector %4
    void pushMoves(int x, int y, int x2, int y2);

};

#endif // MOVEGENERATION_H
