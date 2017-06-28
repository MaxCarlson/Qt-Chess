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

    //generate pseudo-legal moves -- GOING TO DELETE LATER as current is tester function
    std::string generatePsMoves();


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
        //helper functions for isolated ray calcs
        U64 up(U64 piece);
        U64 down(U64 piece);
        U64 right(U64 piece);
        U64 left(U64 piece);
        U64 upright(U64 piece);
        U64 downright(U64 piece);
        U64 downleft(U64 piece);
        U64 upleft(U64 piece);
        //our pieces and enemy pieces -- for finding moves for pinned pieces along pin ray
    std::string pinnedMoves(U64 pinned, U64 opawns, U64 orooks, U64 obishops, U64 oqueens, U64 oking, U64 erooks, U64 ebishops, U64 equeens, U64 ourPieces, bool isWhite);
        //pinned pieces movements
        std::string pinnedPawnCaptures(U64 opawns, U64 enemyPieces, U64 mrays, bool isWhite);
        std::string pinnedBishopMoves(U64 obishops, U64 ourPieces, U64 mrays);

//moves
    U64 makeMove(U64 board, std::string move, char type);

    //pawn moves
    std::string possibleWP(U64 wpawns, U64 EmptyTiles, U64 blackking);
    std::string possibleBP(U64 bpawns, U64 EmptyTiles, U64 whiteking);
    //other piece moves

    std::string possibleR(U64 wOrBrooks, U64 wOrBpieces, U64 oppositeking);
    std::string possibleB(U64 wOrBbishops, U64 wOrBpieces, U64 oppositeking);
    std::string possibleN(U64 wOrBknights, U64 wOrBpieces, U64 oppositeking);
    std::string possibleQ(U64 wOrBqueens, U64 wOrBpieces, U64 oppositeking);
    std::string possibleK(U64 wOrBking, U64 wOrBpieces, U64 kingSafeLessKing);


//slider move functions
    //up + down + left + right without friendly / enemy check
    U64 horizVert(int s);

    //both diagonals
    U64 DAndAntiDMoves(int s);

    //helper function for calculating sliders
    U64 ReverseBits(U64 input);

    //helper method for faster move gen -- finds number of trailing zeros -- Implement in all moves later
    int trailingZeros(U64 i);

    //helper funtction to draw out bitboards like chess boards
    void drawBB(U64 board);
private:

};

#endif // BITBOARDS_H
