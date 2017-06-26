#include "bitboards.h"

#include <iostream>

//totally full bitboard
const U64 full  = 0xffffffffffffffffULL;
const U64 Totallyempty = 0;

//files to keep pieces from moving left or right off board
extern const U64 notAFile = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080
extern const U64 notHFile = 0xfefefefefefefefe; // ~0x0101010101010101

extern const U64 rank4 = 1095216660480L;
extern const U64 rank5=4278190080L;

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
    {" ", " ", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", " ", " "},
    {"P", "P", "P", "P", "P", "P", "P", "P"},
    {"R", "N", "B", "Q", "K", "B", "N", "R"},
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
    std::string a = possibleWB(BBWhiteBishops, BBWhitePieces, BBBlackKing);

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

std::string BitBoards::possibleMovesW(U64 empty, U64 wpawns)
{
    std::string moveList;
    moveList += possiblePW(wpawns, empty);




}

std::string BitBoards::possiblePW(U64 wpawns, U64 EmptyTiles)
{
    std::string list= "";

    //forward one
    U64 PAWN_MOVES = northOne(wpawns) & EmptyTiles;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            //list+=""+(i/8+1)+(i%8)+(i/8)+(i%8);
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
    PAWN_MOVES = noEaOne(wpawns) & BBBlackPieces;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8-1;
            list+=i/8+1;
            list+=i%8;
            list+=i/8;

        }
    }

    //capture left
    PAWN_MOVES = noWeOne(wpawns) & BBBlackPieces;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8+1;
            list+=i/8+1;
            list+=i%8;
            list+=i/8;

        }
    }



    std::cout << list << std::endl;
}


std::string BitBoards::possiblePB(U64 bpawns, U64 EmptyTiles)
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
    PAWN_MOVES = soEaOne(bpawns) & BBWhitePieces;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8-1;
            list+=i/8-1;
            list+=i%8;
            list+=i/8;

        }
    }

    //capture left
    PAWN_MOVES = soWeOne(bpawns) & BBWhitePieces;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8+1;
            list+=i/8-1;
            list+=i%8;
            list+=i/8;

        }
    }


    std::cout << list << std::endl;
}

std::string BitBoards::possibleWB(U64 wbishop, U64 whitepieces, U64 blackking)
{
    std::string list;
    U64 moves;
    //loop through and find bishops
    for(int i = 0; i < 64; i++){
        if(((wbishop>>i) &1) == 1){
            //map moves that don't collide with friendlys and doesn't illegaly take black king
            moves = DAndAntiDMoves(i) & ~whitepieces & ~blackking;
            drawBB(moves);
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
    std::cout << list;
    return list;

}

std::string BitBoards::possibleBB(U64 bbishop, U64 blackpiecs, U64 whiteking)
{
    std::string list;
    U64 moves;
    //loop through and find bishops
    for(int i = 0; i < 64; i++){
        if(((wbishop>>i) &1) == 1){
            //map moves that don't collide with friendlys and doesn't illegaly take white king
            moves = DAndAntiDMoves(i) & ~blackpieces & ~whiteking;
            drawBB(moves);
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
    std::cout << list;
    return list;
}

U64 BitBoards::horizVert(int s)
{
    //convert slider location to 64 bit binary
    U64 binaryS = 1LL << s;

    //left and right moves
    U64 possibilitiesHorizontal = (FullTiles - 2 * binaryS) ^ ReverseBits(ReverseBits(FullTiles) - 2 * ReverseBits(binaryS));
    //moves up and down
    U64 possibilitiesVertical = ((FullTiles & FileMasks8[s % 8]) - (2 * binaryS)) ^ ReverseBits(ReverseBits(FullTiles & FileMasks8[s % 8]) - (2 * ReverseBits(binaryS)));

    //NOTE need to & against opponent pieces / friendlys. Incomplete mask of moves
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

























