#include "bitboards.h"

#include <iostream>

const U64 FileABB = 0x0101010101010101ULL;
const U64 FileBBB = FileABB << 1;
const U64 FileCBB = FileABB << 2;
const U64 FileDBB = FileABB << 3;
const U64 FileEBB = FileABB << 4;
const U64 FileFBB = FileABB << 5;
const U64 FileGBB = FileABB << 6;
const U64 FileHBB = FileABB << 7;

//totally full bitboard
const U64 full  = 0xffffffffffffffffULL;
const U64 Totallyempty = 0;

//files to keep pieces from moving left or right off board
extern const U64 notAFile = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080
extern const U64 notHFile = 0xfefefefefefefefe; // ~0x0101010101010101

extern const U64 rank4 = 1095216660480L;
extern const U64 rank5=4278190080L;

//board for knight moves that can be shifted
extern const U64 KNIGHT_SPAN=43234889994L;

    //files for keeping knight moves from wrapping
extern const U64 FILE_AB=FileABB + FileBBB;
extern const U64 FILE_GH=FileGBB + FileHBB;

//Bitboard of all king movements that can then be shifted
extern const U64 KING_SPAN=460039L;

//board showing where all pieces are + aren't
extern U64 FullTiles;
extern U64 EmptyTiles;

extern U64 BBWhitePieces;

extern U64 BBWhitePawns;
extern U64 BBWhiteRooks;
extern U64 BBWhiteKnights;
extern U64 BBWhiteBishops;
extern U64 BBWhiteQueens;
extern U64 BBWhiteKing;


extern U64 BBBlackPieces;

extern U64 BBBlackPawns;
extern U64 BBBlackRooks;
extern U64 BBBlackKnights;
extern U64 BBBlackBishops;
extern U64 BBBlackQueens;
extern U64 BBBlackKing;

extern U64 RankMasks8[8] =/*from rank1 to rank8*/
    {
        0xFFL, 0xFF00L, 0xFF0000L, 0xFF000000L, 0xFF00000000L, 0xFF0000000000L, 0xFF000000000000L, 0xFF00000000000000L
    };
extern U64 FileMasks8[8] =/*from fileA to FileH*/
{
    0x101010101010101L, 0x202020202020202L, 0x404040404040404L, 0x808080808080808L,
    0x1010101010101010L, 0x2020202020202020L, 0x4040404040404040L, 0x8080808080808080L
};

extern U64 DiagonalMasks8[15] =/*from top left to bottom right*/
{
0x1L, 0x102L, 0x10204L, 0x1020408L, 0x102040810L, 0x10204081020L, 0x1020408102040L,
0x102040810204080L, 0x204081020408000L, 0x408102040800000L, 0x810204080000000L,
0x1020408000000000L, 0x2040800000000000L, 0x4080000000000000L, 0x8000000000000000L
};

extern U64 AntiDiagonalMasks8[15] =/*from top right to bottom left*/
{
0x80L, 0x8040L, 0x804020L, 0x80402010L, 0x8040201008L, 0x804020100804L, 0x80402010080402L,
0x8040201008040201L, 0x4020100804020100L, 0x2010080402010000L, 0x1008040201000000L,
0x804020100000000L, 0x402010000000000L, 0x201000000000000L, 0x100000000000000L
};



U64 FullTiles;
U64 EmptyTiles;

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

std::string chessBoard [8][8]= {
    {"r", "n", "b", "q", "k", "b", "n", "r"},
    {"p", "p", "p", "p", "p", "p", "p", "p",},
    {" ", " ", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", "K", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", " ", " "},
    {"P", "P", "P", "P", "P", "P", "P", "P"},
    {"R", "N", "B", "Q", " ", "B", "N", "R"},
              };

/*
//Debug code for BB
    for(int i = 0; i < 64; i++){
        if(BBWhitePawn & (1ULL << i)){
            std::cout<< 1;
        } else {
            std::cout << 0;
        }
    }
*/

BitBoards::BitBoards()
{

}

std::string BitBoards::generatePsMoves()
{
    std::string moves;

    //moves += possiblePW(BBWhitePawns, EmptyTiles);
    //moves += possiblePB(BBBlackPawns, EmptyTiles);
    //U64 a = horizVert(20);
    //U64 a = DAndAntiDMoves(20);
   // std::string a = possibleWN(BBWhiteKnights, BBWhitePieces, BBBlackKing);
    //std::string b = possibleBN(BBBlackKnights, BBBlackPieces, BBWhiteKing);
    //std::string d = possibleWK(BBWhiteKing, BBWhitePieces);
    //U64 a = unsafeForBlack(BBWhitePawns, BBWhiteRooks, BBWhiteKnights, BBWhiteBishops, BBWhiteQueens, BBWhiteKing, BBBlackPawns, BBBlackRooks, BBBlackKnights, BBBlackBishops, BBBlackQueens, BBBlackKing);
    //U64 b = unsafeForWhite(BBWhitePawns, BBWhiteRooks, BBWhiteKnights, BBWhiteBishops, BBWhiteQueens, BBWhiteKing, BBBlackPawns, BBBlackRooks, BBBlackKnights, BBBlackBishops, BBBlackQueens, BBBlackKing);
    //std::string f = possibleMovesW(BBWhitePieces, BBWhitePawns, BBWhiteRooks, BBWhiteKnights, BBWhiteBishops, BBWhiteQueens, BBWhiteKing, BBBlackPawns, BBBlackRooks, BBBlackKnights, BBBlackBishops, BBBlackQueens, BBBlackKing);
    //std::string g = possibleMovesB(BBBlackPieces, BBWhitePawns, BBWhiteRooks, BBWhiteKnights, BBWhiteBishops, BBWhiteQueens, BBWhiteKing, BBBlackPawns, BBBlackRooks, BBBlackKnights, BBBlackBishops, BBBlackQueens, BBBlackKing);
    U64 a = pinnedBB(BBBlackRooks, BBBlackBishops, BBBlackQueens, BBWhiteKing);
    int c = 5;

    /*
    for(int i = 0; i < 64; i++){
        if(a & (1ULL << i)){
            std::cout<< 1 <<", ";
        } else {
            std::cout << 0 << ", ";
        }
        if((i+1)%8 == 0){
            std::cout<< std::endl;
        }
    }*/


}

std::string BitBoards::possibleMovesW(U64 whitepieces, U64 wpawns, U64 wrooks, U64 wknights, U64 wbishops, U64 wqueens, U64 wking, U64 bpawns, U64 brooks, U64 bknights, U64 bbishops, U64 bqueens, U64 bking)
{
    FullTiles = wpawns | wrooks | wknights | wbishops | wqueens | wking | bpawns | brooks | bknights | bbishops | bqueens | bking;
    U64 empty =~ FullTiles;
    std::string moveList;
    moveList += possibleWP(wpawns, empty, bking);
    moveList += possibleWR(wrooks, whitepieces, bking);
    moveList += possibleWN(wknights, whitepieces, bking);
    moveList += possibleWB(wbishops, whitepieces, bking);
    moveList += possibleWQ(wqueens, whitepieces, bking);
    moveList += possibleWK(wking, whitepieces);
    //int temp = moveList.length()/4;
    return moveList;
}

std::string BitBoards::possibleMovesB(U64 blackpieces, U64 wpawns, U64 wrooks, U64 wknights, U64 wbishops, U64 wqueens, U64 wking, U64 bpawns, U64 brooks, U64 bknights, U64 bbishops, U64 bqueens, U64 bking)
{
    FullTiles = wpawns | wrooks | wknights | wbishops | wqueens | wking | bpawns | brooks | bknights | bbishops | bqueens | bking;
    U64 empty =~ FullTiles;
    std::string moveList;
    moveList += possibleBP(bpawns, empty, wking);
    moveList += possibleBR(brooks, blackpieces, wking);
    moveList += possibleBN(bknights, blackpieces, wking);
    moveList += possibleBB(bbishops, blackpieces, wking);
    moveList += possibleBQ(bqueens, blackpieces, wking);
    moveList += possibleBK(bking, blackpieces);
    //int temp = moveList.length()/4;
    return moveList;
}

U64 BitBoards::unsafeForWhite(U64 wpawns, U64 wrooks, U64 wknights, U64 wbishops, U64 wqueens, U64 wking, U64 bpawns, U64 brooks, U64 bknights, U64 bbishops, U64 bqueens, U64 bking)
{
    U64 unsafe;
    FullTiles = wpawns | wrooks | wknights | wbishops | wqueens | wking | bpawns | brooks | bknights | bbishops | bqueens | bking;

    //pawn
    unsafe = ((bpawns << 7) &~ FileHBB); //pawn capture right
    unsafe |= ((bpawns << 9) &~ FileABB); // left

    U64 possibles;
    //knights
    U64 i = bknights &~(bknights - 1);

    while (i != 0){
        int iLocation = trailingZeros(i);
        if(iLocation > 18){
            possibles = KNIGHT_SPAN << (iLocation - 18);
        } else {
            possibles = KNIGHT_SPAN >> (18 - iLocation);
        }

        if(iLocation % 8 < 4){
            possibles &= ~ FILE_GH;
        } else {
            possibles &= ~ FILE_AB;
        }
        unsafe |= possibles;
        bknights &= ~i;
        i = bknights &~ (bknights - 1);
    }
    //bishops / queens
    U64 QB = bqueens | bbishops;
    i = QB &~ (QB-1);
    while(i != 0){
        int iLocation = trailingZeros(i);
        possibles = DAndAntiDMoves(iLocation);
        unsafe |= possibles;
        QB &= ~i;
        i = QB &~ (QB-1);
    }

    //rooks / queens
    U64 QR = bqueens | brooks;
    i = QR &~ (QR-1);
    while(i != 0){
        int iLocation = trailingZeros(i);
        possibles = horizVert(iLocation);
        unsafe |= possibles;
        QR &= ~i;
        i = QR &~ (QR-1);
    }

    //king
    int iLocation = trailingZeros(bking);
    if(iLocation > 9){
        possibles = KING_SPAN << (iLocation-9);
    } else {
        possibles = KING_SPAN >> (9 - iLocation);
    }

    if(iLocation % 8 < 4){
        possibles &= ~ FILE_GH;
    } else {
        possibles &= ~ FILE_AB;
    }
    unsafe |= possibles;
    //drawBB(unsafe);

    return unsafe;
}

U64 BitBoards::unsafeForBlack(U64 wpawns, U64 wrooks, U64 wknights, U64 wbishops, U64 wqueens, U64 wking, U64 bpawns, U64 brooks, U64 bknights, U64 bbishop, U64 bqueens, U64 bking)
{
    U64 unsafe;
    FullTiles = wpawns | wrooks | wknights | wbishops | wqueens | wking | bpawns | brooks | bknights | bbishop | bqueens | bking;

    //pawn
    unsafe = ((wpawns << 7) &~ FileABB); //pawn capture right
    unsafe |= ((wpawns << 9) &~ FileHBB); // left

    U64 possibles;
    //knights
    U64 i = wknights &~(wknights - 1);

    while (i != 0){
        int iLocation = trailingZeros(i);
        if(iLocation > 18){
            possibles = KNIGHT_SPAN << (iLocation - 18);
        } else {
            possibles = KNIGHT_SPAN >> (18 - iLocation);
        }

        if(iLocation % 8 < 4){
            possibles &= ~ FILE_GH;
        } else {
            possibles &= ~ FILE_AB;
        }
        unsafe |= possibles;
        wknights &= ~i;
        i = wknights &~ (wknights - 1);
    }
    //bishops / queens
    U64 QB = wqueens | wbishops;
    i = QB &~ (QB-1);
    while(i != 0){
        int iLocation = trailingZeros(i);
        possibles = DAndAntiDMoves(iLocation);
        unsafe |= possibles;
        QB &= ~i;
        i = QB &~ (QB-1);
    }

    //rooks / queens
    U64 QR = wqueens | wrooks;
    i = QR &~ (QR-1);
    while(i != 0){
        int iLocation = trailingZeros(i);
        possibles = horizVert(iLocation);
        unsafe |= possibles;
        QR &= ~i;
        i = QR &~ (QR-1);
    }

    //king
    int iLocation = trailingZeros(wking);
    if(iLocation > 9){
        possibles = KING_SPAN << (iLocation-9);
    } else {
        possibles = KING_SPAN >> (9 - iLocation);
    }

    if(iLocation % 8 < 4){
        possibles &= ~ FILE_GH;
    } else {
        possibles &= ~ FILE_AB;
    }
    unsafe |= possibles;
    //drawBB(unsafe);

    return unsafe;
}

U64 BitBoards::pinnedBB(U64 rooks, U64 bishops, U64 queens, U64 king)
{
    U64 pinned, unsafe, rays, upB, dB, rB, lB;

    //find king
    U64 i = king &~ (king-1);
    int kingLoc = trailingZeros(i);
    //king up ray
    upB = king;
    for(int i = 0; i < 8; i++){
        if((upB >> 8) & FullTiles){
            upB = upB | (upB >> 8);
            break;
        }
        upB = upB | (upB >> 8);
    }
    //king down ray
    dB = king;
    for(int i = 0; i < 8; i++){
        if((dB << 8) & FullTiles){
            dB = dB | (dB << 8);
            break;
        }
        dB = dB | (dB << 8);
    }
    //king right ray
    rB = king;
    for(int i = 0; i < 8; i++){
        if ((rB << 1) & FileHBB){
            rB = rB | (rB << 1);
            break;
        }
        if((rB << 1) & FullTiles){
            rB = rB | (rB << 1);
            break;
        }
        rB = rB | (rB << 1);
    }
    //king ray left
    lB = king;
    for(int i = 0; i < 8; i++){
        if ((lB >> 1) & FileABB){
            lB = lB | (lB >> 1);
            break;
        }
        if((lB >> 1) & FullTiles){
            lB = lB | (lB >> 1);
            break;
        }
        lB = lB | (lB >> 1);
    }
    drawBB(lB);

    //rooks / queens
    U64 QR = queens | rooks;
    i = QR &~ (QR-1);
    while(i != 0){
        int iLocation = trailingZeros(i);
        //calculate up rays



        QR &= ~i;
        i = QR &~ (QR-1);
    }

    //bishops / queens
    U64 QB = queens | bishops;
    i = QB &~ (QB-1);
    while(i != 0){
        int iLocation = trailingZeros(i);

        QB &= ~i;
        i = QB &~ (QB-1);
    }



    drawBB(upB);
    return unsafe;
}

std::string BitBoards::possibleWP(U64 wpawns, U64 EmptyTiles, U64 blackking)
{
    std::string list= "";

    //forward one
    U64 PAWN_MOVES = northOne(wpawns) & EmptyTiles;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8;
            list+=i/8+1;
            list+=i%8;
            list+=i/8;

        }
    }

    //forward two
    PAWN_MOVES = (wpawns>>16) & EmptyTiles &(EmptyTiles>>8) &rank4;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8;
            list+=i/8+2;
            list+=i%8;
            list+=i/8;

        }
    }

    //capture right
    PAWN_MOVES = noEaOne(wpawns) & BBBlackPieces & ~blackking;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8-1;
            list+=i/8+1;
            list+=i%8;
            list+=i/8;

        }
    }

    //capture left
    PAWN_MOVES = noWeOne(wpawns) & BBBlackPieces & ~blackking;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8+1;
            list+=i/8+1;
            list+=i%8;
            list+=i/8;

        }
    }
    return list;
}

std::string BitBoards::possibleBP(U64 bpawns, U64 EmptyTiles, U64 whiteking)
{
    std::string list= "";

    //forward one
    U64 PAWN_MOVES = southOne(bpawns) & EmptyTiles;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            //list+=""+(i/8+1)+(i%8)+(i/8)+(i%8);
            list+=i%8;
            list+=i/8-1;
            list+=i%8;
            list+=i/8;

        }
    }

    //forward two
    PAWN_MOVES = (bpawns<<16) & EmptyTiles &(EmptyTiles<<8) & rank5;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8;
            list+=i/8-2;
            list+=i%8;
            list+=i/8;

        }
    }

    //capture right
    PAWN_MOVES = soEaOne(bpawns) & BBWhitePieces & ~whiteking;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8-1;
            list+=i/8-1;
            list+=i%8;
            list+=i/8;

        }
    }

    //capture left
    PAWN_MOVES = soWeOne(bpawns) & BBWhitePieces & ~whiteking;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8+1;
            list+=i/8-1;
            list+=i%8;
            list+=i/8;

        }
    }
    return list;
}

std::string BitBoards::possibleWR(U64 wrooks, U64 whitepieces, U64 blackking)
{
    std::string list;
    U64 moves;
    //loop through and find bishops
    for(int i = 0; i < 64; i++){
        if(((wrooks>>i) &1) == 1){
            //map moves that don't collide with friendlys and doesn't illegaly take black king
            moves = horizVert(i) & ~whitepieces & ~blackking;
            //drawBB(moves);
            for(int j = 0; j < 64; j++){
                if(((moves>>j) &1) == 1){
                    list+=i%8;
                    list+=i/8;
                    list+=j%8;
                    list+=j/8;
                }
            }
        }
    }
    return list;
}

std::string BitBoards::possibleBR(U64 brooks, U64 blackpieces, U64 whiteking)
{
    std::string list;
    U64 moves;
    //loop through and find bishops
    for(int i = 0; i < 64; i++){
        if(((brooks>>i) &1) == 1){
            //map moves that don't collide with friendlys and doesn't illegaly take black king
            moves = horizVert(i) & ~blackpieces & ~whiteking;
            //drawBB(moves);
            for(int j = 0; j < 64; j++){
                if(((moves>>j) &1) == 1){
                    list+=i%8;
                    list+=i/8;
                    list+=j%8;
                    list+=j/8;
                }
            }
        }
    }
    return list;
}

std::string BitBoards::possibleWB(U64 wbishops, U64 whitepieces, U64 blackking)
{
    std::string list;
    U64 moves;
    //loop through and find bishops
    for(int i = 0; i < 64; i++){
        if(((wbishops>>i) &1) == 1){
            //map moves that don't collide with friendlys and doesn't illegaly take black king
            moves = DAndAntiDMoves(i) & ~whitepieces & ~blackking;
            for(int j = 0; j < 64; j++){
                if(((moves>>j) &1) == 1){
                    list+=i%8;
                    list+=i/8;
                    list+=j%8;
                    list+=j/8;
                }
            }
        }
    }
    return list;

}

std::string BitBoards::possibleBB(U64 bbishop, U64 blackpieces, U64 whiteking)
{
    std::string list;
    U64 moves;
    //loop through and find bishops
    for(int i = 0; i < 64; i++){
        if(((bbishop>>i) &1) == 1){
            //map moves that don't collide with friendlys and doesn't illegaly take white king
            moves = DAndAntiDMoves(i) & ~blackpieces & ~whiteking;
            for(int j = 0; j < 64; j++){
                if(((moves>>j) &1) == 1){
                    list+=i%8;
                    list+=i/8;
                    list+=j%8;
                    list+=j/8;
                }
            }
        }
    }
    return list;
}

std::string BitBoards::possibleWN(U64 wknights, U64 whitepieces, U64 blackking)
{
    std::string list;
    U64 moves;
    //loop through and find bishops
    for(int i = 0; i < 64; i++){
        if(((wknights>>i) &1) == 1){
            //use the knight span board which holds possible knight moves
            //and apply a shift to the knights current pos
            if(i > 18){
                moves = KNIGHT_SPAN<<(i-18);
            } else {
                moves = KNIGHT_SPAN>>(18-i);
            }

            //making sure the moves don't warp around to other side once shifter
            //as well as friendly and illegal king capture check
            if(i % 8 < 4){
                moves &= ~FILE_GH & ~whitepieces & ~blackking;
            } else {
                moves &= ~FILE_AB & ~whitepieces & ~blackking;
            }
            //testing -- draw moves
            //drawBB(moves);
            for(int j = 0; j < 64; j++){
                if(((moves>>j) &1) == 1){
                    list+=i%8;
                    list+=i/8;
                    list+=j%8;
                    list+=j/8;
                }
            }
        }
    }
    return list;
}

std::string BitBoards::possibleBN(U64 bknights, U64 blackpieces, U64 whiteking)
{
    std::string list;
    U64 moves;
    //loop through and find bishops
    for(int i = 0; i < 64; i++){
        if(((bknights>>i) &1) == 1){
            //use the knight span board which holds possible knight moves
            //and apply a shift to the knights current pos
            if(i > 18){
                moves = KNIGHT_SPAN<<(i-18);
            } else {
                moves = KNIGHT_SPAN>>(18-i);
            }

            //making sure the moves don't warp around to other side once shifter
            //as well as friendly and illegal king capture check
            if(i % 8 < 4){
                moves &= ~FILE_GH & ~blackpieces & ~whiteking;
            } else {
                moves &= ~FILE_AB & ~blackpieces & ~whiteking;
            }
            //testing -- draw moves
            //drawBB(moves);
            for(int j = 0; j < 64; j++){
                if(((moves>>j) &1) == 1){
                    list+=i%8;
                    list+=i/8;
                    list+=j%8;
                    list+=j/8;
                }
            }
        }
    }
    return list;
}

std::string BitBoards::possibleWQ(U64 wqueens, U64 whitepieces, U64 blackking)
{
    std::string list;
    U64 moves;
    //loop through and find bishops
    for(int i = 0; i < 64; i++){
        if(((wqueens>>i) &1) == 1){
            //map moves that don't collide with friendlys and doesn't illegaly take black king
            moves = DAndAntiDMoves(i) + horizVert(i) & ~whitepieces & ~blackking;
            //TEST drawing moves
            //drawBB(moves);
            for(int j = 0; j < 64; j++){
                if(((moves>>j) &1) == 1){
                    list+=i%8;
                    list+=i/8;
                    list+=j%8;
                    list+=j/8;
                }
            }
        }
    }
    return list;
}

std::string BitBoards::possibleBQ(U64 bqueens, U64 blackpieces, U64 whiteking)
{
    std::string list;
    U64 moves;
    //loop through and find bishops
    for(int i = 0; i < 64; i++){
        if(((bqueens>>i) &1) == 1){
            //map moves that don't collide with friendlys and doesn't illegaly take white king
            moves = DAndAntiDMoves(i) + horizVert(i) & ~blackpieces & ~whiteking;
            //TEST drawing moves
            //drawBB(moves);
            for(int j = 0; j < 64; j++){
                if(((moves>>j) &1) == 1){
                    list+=i%8;
                    list+=i/8;
                    list+=j%8;
                    list+=j/8;
                }
            }
        }
    }

    return list;
}

std::string BitBoards::possibleWK(U64 wking, U64 whitepieces)
{
    std::string list;
    U64 moves;

    int i = trailingZeros(wking);
    if(i > 9){
        moves = KING_SPAN << (i-9);

    } else {
        moves = KING_SPAN >> (9-i);
    }

    if(i % 8 < 4){
        moves &= ~FILE_GH & ~whitepieces;

    } else {
        moves &= ~FILE_AB & ~whitepieces;
    }
    //drawBB(moves);
    U64 j = moves &~(moves-1);

    while(j != 0){
        int index = trailingZeros(j);

        list += i%8;
        list += i/8;
        list += index%8;
        list += index/8;

        moves &= ~j;
        j = moves &~ (moves-1);
    }

return list;

}

std::string BitBoards::possibleBK(U64 bking, U64 blackpieces)
{
    std::string list;
    U64 moves;

    int i = trailingZeros(bking);
    if(i > 9){
        moves = KING_SPAN << (i-9);

    } else {
        moves = KING_SPAN >> (9-i);
    }

    if(i % 8 < 4){
        moves &= ~FILE_GH & ~blackpieces;

    } else {
        moves &= ~FILE_AB & ~blackpieces;
    }
    //drawBB(moves);
    U64 j = moves &~(moves-1);

    while(j != 0){
        int index = trailingZeros(j);

        list += i%8;
        list += i/8;
        list += index%8;
        list += index/8;

        moves &= ~j;
        j = moves &~ (moves-1);
    }

return list;
}

//implament into other MOVE GEN ASIDE FROM KINGS, MUCH FASTER THAN for 64 loop
int BitBoards::trailingZeros(U64 i)
{
    if (i == 0) return 64;
    U64 x = i;
    U64 y;
    int n = 63;
    y = x << 32; if (y != 0) { n -= 32; x = y; }
    y = x << 16; if (y != 0) { n -= 16; x = y; }
    y = x <<  8; if (y != 0) { n -=  8; x = y; }
    y = x <<  4; if (y != 0) { n -=  4; x = y; }
    y = x <<  2; if (y != 0) { n -=  2; x = y; }
    return (int) ( n - ((x << 1) >> 63));
}

U64 BitBoards::horizVert(int s)
{
    //convert slider location to 64 bit binary
    U64 binaryS = 1LL << s;

    //left and right moves
    U64 possibilitiesHorizontal = (FullTiles - 2 * binaryS) ^ ReverseBits(ReverseBits(FullTiles) - 2 * ReverseBits(binaryS));
    //moves up and down
    U64 possibilitiesVertical = ((FullTiles & FileMasks8[s % 8]) - (2 * binaryS)) ^ ReverseBits(ReverseBits(FullTiles & FileMasks8[s % 8]) - (2 * ReverseBits(binaryS)));

    //NOTE need to & against friendlys. Incomplete mask of moves
    return (possibilitiesHorizontal & RankMasks8[s / 8]) | (possibilitiesVertical & FileMasks8[s % 8]);

}

U64 BitBoards::DAndAntiDMoves(int s)
{
    U64 binaryS = 1LL <<s;

    U64 possibilitiesDiagonal = ((FullTiles & DiagonalMasks8[(s / 8) + (s % 8)]) - (2 * binaryS)) ^ ReverseBits(ReverseBits(FullTiles & DiagonalMasks8[(s / 8) + (s % 8)]) - (2 * ReverseBits(binaryS)));

    U64 possibilitiesAntiDiagonal = ((FullTiles & AntiDiagonalMasks8[(s / 8) + 7 - (s % 8)]) - (2 * binaryS)) ^ ReverseBits(ReverseBits(FullTiles & AntiDiagonalMasks8[(s / 8) + 7 - (s % 8)]) - (2 * ReverseBits(binaryS)));

    return (possibilitiesDiagonal & DiagonalMasks8[(s / 8) + (s % 8)]) | (possibilitiesAntiDiagonal & AntiDiagonalMasks8[(s / 8) + 7 - (s % 8)]);
}

U64 BitBoards::ReverseBits(U64 input)
{
    U64 output = input;
    for (int i = sizeof(input) * 8-1; i; --i)
    {
        output <<= 1;
        input  >>= 1;
        output |=  input & 1;
    }
    return output;
}


U64 BitBoards::northOne(U64 b)
{
    return b >> 8;
}

U64 BitBoards::southOne(U64 b)
{
    return b << 8;
}

U64 BitBoards::eastOne (U64 b)
{
    return (b << 1) & notHFile;
}

U64 BitBoards::noEaOne(U64 b)
{
    return (b >> 7) & notHFile;;
}

U64 BitBoards::soEaOne(U64 b)
{
    return (b << 9) & notHFile;
}

U64 BitBoards::westOne(U64 b)
{
    return (b >> 1) & notAFile;
}

U64 BitBoards::soWeOne(U64 b)
{

    return (b << 7) & notAFile;
}

U64 BitBoards::noWeOne(U64 b)
{
    return (b >> 9) & notAFile;
}


void BitBoards::constructBoards()
{
    //seed bitboards
    for(int i = 0; i < 64; i++){
        if(chessBoard[i/8][i%8] == "P"){
            BBWhitePawns += 1LL<<i;
            BBWhitePieces += 1LL<<i;
            FullTiles += 1LL<<i;
        } else if(chessBoard[i/8][i%8] == "R"){
            BBWhiteRooks += 1LL<<i;
            BBWhitePieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }else if(chessBoard[i/8][i%8] == "N"){
            BBWhiteKnights += 1LL<<i;
            BBWhitePieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }else if(chessBoard[i/8][i%8] == "B"){
            BBWhiteBishops += 1LL<<i;
            BBWhitePieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }else if(chessBoard[i/8][i%8] == "Q"){
            BBWhiteQueens += 1LL<<i;
            BBWhitePieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }else if(chessBoard[i/8][i%8] == "K"){
            BBWhiteKing += 1LL<<i;
            BBWhitePieces += 1LL<<i;
            FullTiles += 1LL<<i;
        } else if(chessBoard[i/8][i%8] == "p"){
            BBBlackPawns += 1LL<<i;
            BBBlackPieces += 1LL<<i;
            FullTiles += 1LL<<i;
        } else if(chessBoard[i/8][i%8] == "r"){
            BBBlackRooks += 1LL<<i;
            BBBlackPieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }else if(chessBoard[i/8][i%8] == "n"){
            BBBlackKnights += 1LL<<i;
            BBBlackPieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }else if(chessBoard[i/8][i%8] == "b"){
            BBBlackBishops += 1LL<<i;
            BBBlackPieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }else if(chessBoard[i/8][i%8] == "q"){
            BBBlackQueens += 1LL<<i;
            BBBlackPieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }else if(chessBoard[i/8][i%8] == "k"){
            BBBlackKing += 1LL<<i;
            BBBlackPieces += 1LL<<i;
            FullTiles += 1LL<<i;
        }

    }

    //mark emtpy tiles with 1's
    EmptyTiles = ~(EmptyTiles ^ FullTiles);

    //testing!!!
    //EmptyTiles = noWeOne(EmptyTiles);

    for(int i = 0; i < 64; i++){
        if(EmptyTiles & (1ULL << i)){
            std::cout<< 1 <<", ";
        } else {
            std::cout << 0 << ", ";
        }
        if((i+1)%8 == 0){
            std::cout<< std::endl;
        }
    }
    std::cout << std::endl;
}

void BitBoards::drawBB(U64 board)
{
    for(int i = 0; i < 64; i++){
        if(board & (1ULL << i)){
            std::cout<< 1 <<", ";
        } else {
            std::cout << 0 << ", ";
        }
        if((i+1)%8 == 0){
            std::cout<< std::endl;
        }
    }
    std::cout<< std::endl;
}

























