#ifndef MOVEGENERATION_H
#define MOVEGENERATION_H
#include "externs.h"
#include "ai_logic.h"

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

//test board state
    float testBoardValue(int x, int y, int x2, int y2);

//and return value
    void undo_move(int x, int y, int x2, int y2);

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

//white or black opponent check
    bool whiteOrBlack(std::string tmpPiece, int x, int y);


//function that puts all the needed functions below in the right order to check if a move is safe
    bool safetyCheck(int x, int y, int x2, int y2);

//create bool board to see if move makes king unsafe or not
    void createKingSafteyBoard();

//reset bool boards so another piece move can be calced
    bool resetSafetyBoards();

//check if king is safe against bool boards
    bool isKingSafe();

//mark where is unsafe and figure out who
    void whiteOrBlack(int x, int y, char wb);

//make sure move is sane before trying to put on bool board
    bool sanityCheck(int x, int y);

//move sets for calcing safety boards
    void upDownLeftRightM(int x, int y, char wb);
    void diagonalM(int x, int y, char wb);
    void knightM(int x, int y, char wb);
    void kingM(int x, int y, char wb);
};

#endif // MOVEGENERATION_H
