#ifndef AI_LOGIC_H
#define AI_LOGIC_H

#include <string>

#include "externs.h"
#include "movegeneration.h"



class Ai_Logic
{
public:
    Ai_Logic();

    int calculateBestMove();

    std::vector<std::string> possible_moves;

private:


    //find total board values
    float evaluateBoard();
    //pice values and abs val for black and white
    float getPieceValue(std::string piece, int x, int y);
    float getAbsoluteValue(std::string piece, int x, int y);
};

#endif // AI_LOGIC_H
