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

    //find board values
    static float evaluateBoard();

    //peice values and abs val for black and white
    static float getPieceValue(std::string piece, int x, int y);
    static float getAbsoluteValue(std::string piece, int x, int y);

private:




};

#endif // AI_LOGIC_H
