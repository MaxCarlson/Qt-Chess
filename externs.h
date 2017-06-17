#ifndef EXTERNS_H
#define EXTERNS_H

#include <vector>
#include <string>

//chess board represented
extern std::string boardArr[8][8];

//string of pieces
extern std::string blackPieces[7];
extern std::string whitePieces[7];

//half turns
extern int turns;

//values for computing if a move is valid
extern int tempx, tempy, tempx2, tempy2;

//king safety arrays
extern bool whiteSafe[8][8];
extern bool blackSafe[8][8];

extern int count, numberOfPieceMoved;

// is ai on
extern int aiOn;

//vector holding all ai moves
extern std::vector<int> possibleMoves;

//ai initial x,y and final xy of possible return move
extern int aiX, aiY, aiX1, aiY1;
//ai piece values
// white then black
extern int wPawnV, wRookV, wKnightV, wBishopV, wQueenV, wKingV;

extern int bPawnV, bRookV, bKnightV, bBishopV, bQueenV, bKingV;

#endif // EXTERNS_H
