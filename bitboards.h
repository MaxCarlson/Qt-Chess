#ifndef BITBOARDS_H
#define BITBOARDS_H

typedef unsigned long long  U64; // supported by MSC 13.00+ and C99
#define C64(constantU64) constantU64##ULL

#include <string>


class BitBoards
{
public:
    BitBoards();

    void constructBoards();


    //return bitboards of movement in one direction
    U64 northOne(U64 b);
    U64 southOne(U64 b);
    U64 eastOne(U64 b);
    U64 noEaOne (U64 b);
    U64 soEaOne (U64 b);
    U64 westOne (U64 b);
    U64 soWeOne (U64 b);
    U64 noWeOne (U64 b);

    //generate pseudo-legal moves
    std::string generatePsMoves();
    //process psuedo-legal into legal moves

    //process moves into ints


    //pawn movement bitboards
    std::string possiblePW(U64 wpawns, U64 EmptyTiles);

private:

};

#endif // BITBOARDS_H
