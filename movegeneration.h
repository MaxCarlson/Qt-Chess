#ifndef MOVEGENERATION_H
#define MOVEGENERATION_H
#include "externs.h"

#include <string>



class moveGeneration
{
private:
    blackPawn(int x, int y);
    whitePawn(int x, int y);

    rook(int x, int y);
    knight(int x, int y);
    bishop(int x, int y);
    queen(int x, int y);
    king(int x, int y);


public:
    moveGeneration();
};

#endif // MOVEGENERATION_H
