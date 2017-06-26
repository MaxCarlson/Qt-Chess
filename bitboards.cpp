#include "bitboards.h"

#include <iostream>

//totally full bitboard
const U64 full  = 0xffffffffffffffffULL;
const U64 Totallyempty = 0;

//files to keep pieces from moving left or right off board
extern const U64 notAFile = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080
extern const U64 notHFile = 0xfefefefefefefefe; // ~0x0101010101010101

extern const U64 rank4 = C64(0x00000000FF000000);

//board showing where all pieces are
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

    moves += possiblePW(BBWhitePawns, EmptyTiles);
}

std::string BitBoards::possiblePW(U64 wpawns, U64 EmptyTiles)
{
    std::string list= "";
    /*
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
    */
    //forward two
    U64 PAWN_MOVES = (wpawns>>16) &EmptyTiles &(EmptyTiles>>8) &rank4;
    for(int i = 0; i < 64; i++){
        if(((PAWN_MOVES>>i)&1)==1){
            list+=i%8;
            list+=i/8+2;
            list+=i%8;
            list+=i/8;

        }
    }

    std::cout << list << std::endl;
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
    return (b << 9) & notHFile;
}

U64 BitBoards::noWeOne(U64 b)
{
    return (b >> 7) & notHFile;
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
    //BBWhitePawns = soWeOne(BBWhitePawns);

    EmptyTiles = ~(EmptyTiles ^ FullTiles);

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
}





//BitBoards::shiftBits();

