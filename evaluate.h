#ifndef EVALUATE_H
#define EVALUATE_H

#include "externs.h"


class Evaluate
{
public:
    Evaluate();

    float evaluateBoard(float depth, int NumberOfMoves);

    float getAbsoluteValue(std::string piece, int x, int y);

    float getPieceValue(std::string piece, int x, int y);


};

#endif // EVALUATE_H
