#ifndef AI_LOGIC_H
#define AI_LOGIC_H

#include <string>
#include <algorithm>

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

    //root function for recursive move finiding via minimax
    std::string miniMaxRoot(int depth, bool isMaximisingPlayer);

    float miniMax(float depth, float alpha, float beta, bool isMaximisingPlayer);

private:
    void undo_move1();
    void undo_move2();

    //counts number of piece postitions tried
    int positionCount = 0;


};

#endif // AI_LOGIC_H
