#ifndef BITBOARDS_H
#define BITBOARDS_H

typedef unsigned long long  U64; // supported by MSC 13.00+ and C99
#define C64(constantU64) constantU64##ULL

class BitBoards
{
public:
    BitBoards();

private:
    //totall full bitboard
    const U64 BBFullBoard  = 0xffffffffffffffffULL;

    U64 BBWhitePieces;

    U64 BBWhitePawns;
    U64 BBWhiteRooks;
    U64 BBWhiteKnights;
    U64 BBWhiteBishops;
    U64 BBWhiteQueens;
    U64 BBWhiteKing;


    U64 BBBlackPieces;

    U64 BBBlackPawns;
    U64 BBBlackRooks;
    U64 BBBlackKnights;
    U64 BBBlackBishops;
    U64 BBBlackQueens;
    U64 BBBlackKing;
};

#endif // BITBOARDS_H
