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
    std::string possibleMovesW(U64 whitepieces, U64 wpawns, U64 wrooks, U64 wknights, U64 wbishops, U64 wqueens, U64 wking, U64 bpawns, U64 brooks, U64 bknights, U64 bbishops, U64 bqueens, U64 bking);
    std::string possibleMovesB(U64 blackpieces, U64 wpawns, U64 wrooks, U64 wknights, U64 wbishops, U64 wqueens, U64 wking, U64 bpawns, U64 brooks, U64 bknights, U64 bbishops, U64 bqueens, U64 bking);

//unsafe area checking for b/w
    U64 unsafeForWhite(U64 wpawns, U64 wrooks, U64 wknights, U64 wbishops, U64 wqueens, U64 wking, U64 bpawns, U64 brooks, U64 bknights, U64 bbishops, U64 bqueens, U64 bking);
    U64 unsafeForBlack(U64 wpawns, U64 wrooks, U64 wknights, U64 wbishops, U64 wqueens, U64 wking, U64 bpawns, U64 brooks, U64 bknights, U64 bbishop, U64 bqueens, U64 bking);
    //only unsafe for king -- sliders travel "through" king so other side is unsafe
    U64 kingDangerSquares(U64 wpawns, U64 wrooks, U64 wknights, U64 wbishops, U64 wqueens, U64 bpawns, U64 brooks, U64 bknights, U64 bbishop, U64 bqueens, U64 BOrWKing);
    //pinned piece check at move gen start to pass to pieces so as not to gen invalid moves
    U64 pinnedBB(U64 rooks, U64 bishops, U64 queens, U64 king);
        //helper functions for isolated ray cals
        U64 up(int s);
        U64 down(int s);
        U64 right(int s);
        U64 left(int s);
        U64 upright(int s);
        U64 downright(int s);
        U64 downleft(int s);
        U64 upleft(int s);

//moves
    U64 makeMove(U64 board, std::string move, char type);

    //white moves
    std::string possibleWP(U64 wpawns, U64 EmptyTiles, U64 blackking);
    std::string possibleWR(U64 wrooks, U64 whitepieces, U64 blackking);
    std::string possibleWN(U64 wknights, U64 whitepieces, U64 blackking);
    std::string possibleWB(U64 wbishops, U64 whitepieces, U64 blackking);
    std::string possibleWQ(U64 wqueens, U64 whitepieces, U64 blackking);
    std::string possibleWK(U64 wking, U64 whitepieces);



    //black moves
    std::string possibleBP(U64 bpawns, U64 EmptyTiles, U64 whiteking);
    std::string possibleBR(U64 brooks, U64 blackpieces, U64 whiteking);
    std::string possibleBN(U64 bknights,U64 blackpieces, U64 whiteking);
    std::string possibleBB(U64 bbishop, U64 blackpieces, U64 whiteking);
    std::string possibleBQ(U64 bqueens, U64 blackpieces, U64 whiteking);
    std::string possibleBK(U64 bking, U64 blackpieces);

    //helper method for faster move gen -- finds number of trailing zeros -- Implement in all moves later
    int trailingZeros(U64 i);


//slider moves
    //up + down + left + right without friendly / enemy check
    U64 horizVert(int s);

    //both diagonals
    U64 DAndAntiDMoves(int s);

    //helper function for calculating sliders
    U64 ReverseBits(U64 input);

    //helper funtction to draw out bitboards like chess boards
    void drawBB(U64 board);
private:

};

#endif // BITBOARDS_H
