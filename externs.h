#ifndef EXTERNS_H
#define EXTERNS_H

#include <vector>
#include <string>

extern std::string boardArr[8][8];

extern std::string blackPieces[7];
extern std::string whitePieces[7];

extern int turns;

extern int tempx, tempy, tempx2, tempy2;

extern bool whiteSafe[8][8];
extern bool blackSafe[8][8];

extern int count, numberOfPieceMoved;

extern int aiOn;

extern std::vector<std::string> possibleMoves;



#endif // EXTERNS_H
