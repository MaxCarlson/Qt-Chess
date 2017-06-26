#include "bitboards.h"
#include <iostream>

typedef unsigned long long  U64; // supported by MSC 13.00+ and C99
#define C64(constantU64) constantU64##ULL

//totall full bitboard
const C64 universe  = 0xffffffffffffffffULL;

C64 BBWhitePawn;

BitBoards::BitBoards()
{
    for(int i = 0; i < 64; i++){
        if(universe & (1ULL << i)){
            std::cout<< 1;
        } else {
            std::cout << 0;
        }
    }
}
