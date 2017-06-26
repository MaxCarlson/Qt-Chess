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

    //process moves for each color into a string of moves
    std::string possibleMovesW(U64 empty, U64 wpawns);
    std::string possibleMovesB();

    //white moves
    std::string possiblePW(U64 wpawns, U64 EmptyTiles);
    std::string possibleWB(U64 wbishop, U64 whitepieces, U64 blackking);



    //black moves
    std::string possiblePB(U64 bpawns, U64 EmptyTiles);
    std::string possibleBB(U64 bbishop, U64 blackpiecs, U64 whiteking);


    U64 ReverseBits(U64 input);
    //slider moves
    //up + down + left + right without friendly / enemy check
    U64 horizVert(int s);

    //both diagonals
    U64 DAndAntiDMoves(int s);

    //helper funtction to draw out bitboards like chess boards
    void drawBB(U64 board);
private:

};

#endif // BITBOARDS_H
