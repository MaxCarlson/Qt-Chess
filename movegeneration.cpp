#include "movegeneration.h"

//value spots for pieces
float pawnEvalWhite[8][8] =
{
    {0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
    {5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0},
    {1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0},
    {0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5},
    {0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0},
    {0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5},
    {0.5,  1.0, 1.0,  -2.0, -2.0,  1.0,  1.0,  0.5},
    {0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0}
};

float pawnEvalBlack[8][8] =
{
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0},
    {0.5, 1.0, 1.0,-2.0,-2.0, 1.0, 1.0,0.5},
    {0.5,-0.5,-1.0, 0.0, 0.0,-1.0,-0.5,0.5},
    {0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0,0.0},
    {0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5,0.5},
    {1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0,1.0},
    {5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0,5.0},
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0}

};


float knightEval[8][8] =
{
    {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
    {-4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0},
    {-3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0},
    {-3.0,  0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0},
    {-3.0,  0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0},
    {-3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0},
    {-4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0},
    {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0}
};

float bishopEvalWhite[8][8] = {
    { -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
    { -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
    { -1.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0},
    { -1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0},
    { -1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0},
    { -1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0},
    { -1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0},
    { -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}
};

float bishopEvalBlack[8][8] = {
    {-2.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-2.0},
    {-1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5,-1.0},
    {-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,-1.0},
    {-1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0,-1.0},
    {-1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5,-1.0},
    {-1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0,-1.0},
    {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,-1.0},
    {-2.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-2.0}
};

float rookEvalWhite[8][8] = {
    {  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
    {  0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5},
    { -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    { -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    { -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    { -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    { -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {  0.0,   0.0, 0.0,  0.5,  0.5,  0.0,  0.0,  0.0}
};

float rookEvalBlack[8][8] = {
    { 0.0,0.0,0.0,0.5,0.5,0.0,0.0, 0.0},
    {-0.5,0.0,0.0,0.0,0.0,0.0,0.0,-0.5},
    {-0.5,0.0,0.0,0.0,0.0,0.0,0.0,-0.5},
    {-0.5,0.0,0.0,0.0,0.0,0.0,0.0,-0.5},
    {-0.5,0.0,0.0,0.0,0.0,0.0,0.0,-0.5},
    {-0.5,0.0,0.0,0.0,0.0,0.0,0.0,-0.5},
    { 0.5,1.0,1.0,1.0,1.0,1.0,1.0, 0.5},
    { 0.0,0.0,0.0,0.0,0.0,0.0,0.0, 0.0}
};

float evalQueen[8][8] = {
    { -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
    { -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
    { -1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0},
    { -0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5},
    {  0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5},
    { -1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0},
    { -1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0},
    { -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0}
};

float kingEvalWhite[8][8] = {

    { -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    { -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    { -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    { -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    { -2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
    { -1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
    {  2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0},
    {  2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0}
};

float kingEvalBlack[8][8] = {

    {2.0 , 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0},
    {2.0 , 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0},
    {-1.0,-2.0,-2.0,-2.0,-2.0,-2.0,-2.0,-1.0},
    {-2.0,-3.0,-3.0,-4.0,-4.0,-3.0,-3.0,-2.0},
    {-3.0,-4.0,-4.0,-5.0,-5.0,-4.0,-4.0,-3.0},
    {-3.0,-4.0,-4.0,-5.0,-5.0,-4.0,-4.0,-3.0},
    {-3.0,-4.0,-4.0,-5.0,-5.0,-4.0,-4.0,-3.0},
    {-3.0,-4.0,-4.0,-5.0,-5.0,-4.0,-4.0,-3.0}
};

//vector of all possible moves for one side
std::vector<int> possibleMoves;

// ai values for best possible move once computed
int aiX, aiY, aiX1, aiY1;

//ai piece values white then black
int wPawnV = 10, wRookV = 50, wKnightV = 30, wBishopV = 30, wQueenV = 90, wKingV = 900;
int bPawnV = -10, bRookV = -50, bKnightV = -30, bBishopV = -30, bQueenV = -90, bKingV = -900;

moveGeneration::moveGeneration()
{

    //ai is black ~ possibly replace player moves set too
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(boardArr[i][j] == "p"){
                blackPawn(j , i);
            }else if(boardArr[i][j] == "r"){
                rook(j , i);
            } else if(boardArr[i][j] == "n"){
                knight(j, i);
            }else if(boardArr[i][j] == "b"){
                bishop(j, i);
            } else if(boardArr[i][j] == "q"){
                queen(j, i);
            } else if(boardArr[i][j] == "k"){
                king(j, i);
            }
        }
    }
}



void moveGeneration::blackPawn(int x, int y)
{
    std::string tx = std::to_string(x), ty = std::to_string(y);
    //move forward one
    if(boardArr[y+1][x] == " "){
        pushMoves(x, y, x, y+1);
    }
    //or two first turn
    if(y == 1 && boardArr[y+1][x] == " " && boardArr[y+2][x] == " "){
        pushMoves(x, y, x, y+2);
    }
    //take out side-wase left
    if(boardArr[y+1][x-1] != " "){
        pushMoves(x, y, x-1, y+1);
    }
    //right take out
    if(boardArr[y+1][x+1] != " "){
        pushMoves(x, y, x+1, y+1);
    }

}

void moveGeneration::rook(int x, int y)
{
    //up
    for(int i = y-1; i > 0; i--){
        pushMoves(x, y, x, i);
    }
    //down
    for(int i = y+1; i < 8; i++){
        pushMoves(x, y, x, i);
    }
    //left
    for(int i = x-1; i > 0; i--){
        pushMoves(x, y, i, y);
    }
    //right
    for(int i = x+1; i < 8; i++){
        pushMoves(x, y, i, y);
    }
}

void moveGeneration::knight(int x, int y)
{

}

void moveGeneration::bishop(int x, int y)
{

    //up left
    int tmp = y-1;
    for(int i = x-1; i > 0; i--){
        pushMoves(x, y, i, tmp);
        tmp -= 1;
    }

    //up right
    tmp = y-1;
    for(int i = x+1; i < 8; i++){
        pushMoves(x, y, i, tmp);
        tmp -= 1;
    }

    //down right
    tmp = y + 1;
    for(int i = x+1; i < 8; i++){
        pushMoves(x, y, i, tmp);
        tmp += 1;
    }

    //down left
    tmp = y + 1;
    for(int i = x-1; i > 0; i--){
        pushMoves(x, y, i, tmp);
        tmp += 1;
    }

}

void moveGeneration::queen(int x, int y)
{
    //up
    for(int i = y-1; i > 0; i--){
        pushMoves(x, y, x, i);
    }
    //down
    for(int i = y+1; i < 8; i++){
        pushMoves(x, y, x, i);
    }
    //left
    for(int i = x-1; i > 0; i--){
        pushMoves(x, y, i, y);
    }
    //right
    for(int i = x+1; i < 8; i++){
        pushMoves(x, y, i, y);
    }

    //up left
    int tmp = y-1;
    for(int i = x-1; i > 0; i--){
        pushMoves(x, y, i, tmp);
        tmp -= 1;
    }

    //up right
    tmp = y-1;
    for(int i = x+1; i < 8; i++){
        pushMoves(x, y, i, tmp);
        tmp -= 1;
    }

    //down right
    tmp = y + 1;
    for(int i = x+1; i < 8; i++){
        pushMoves(x, y, i, tmp);
        tmp += 1;
    }

    //down left
    tmp = y + 1;
    for(int i = x-1; i > 0; i--){
        pushMoves(x, y, i, tmp);
        tmp += 1;
    }

}

void moveGeneration::king(int x, int y)
{
    //up
    pushMoves(x, y, x, y-1);
    // down
    pushMoves(x, y, x, y+1);
    //left
    pushMoves(x, y, x-1, y);
    //right
    pushMoves(x, y, x+1, y);
    //up left
    pushMoves(x, y, x-1, y-1);
    // up right
    pushMoves(x, y, x+1, y-1);
    //down right
    pushMoves(x, y, x+1, y+1);
    //down left
    pushMoves(x, y, x-1, y+1);
}

int moveGeneration::calculateBestMove()
{

}

float moveGeneration::evaluateBoard()
{
    //finding score of board
    int totalEvaluation = 0;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            totalEvaluation += getPieceValue(boardArr[i][j], i, j);
        }
    }
    return totalEvaluation;
}




float moveGeneration::getPieceValue(std::string piece, int x, int y)
{

    if(piece == " "){
        return 0;
    }
    float absoluteValue = getAbsoluteValue(piece, x, y);

    if(piece == "P" || piece == "R" || piece == "N" || piece == "B" || piece == "K" || piece == "Q"){
        return absoluteValue;
    } else {
        return -absoluteValue;
    }

}

float moveGeneration::getAbsoluteValue(std::string piece, int x, int y)
{
    //black
    if(piece == "p"){
        return bPawnV + pawnEvalBlack[y][x];
    } else if (piece =="r"){
        return bRookV + rookEvalBlack[y][x];
    }else if (piece =="k"){
        return  bKnightV + knightEval[y][x];
    }else if (piece =="b"){
        return bBishopV + bishopEvalBlack[y][x];
    }else if (piece =="q"){
        return bQueenV + evalQueen[y][x];
    }else if (piece =="k"){
        return bKingV + kingEvalBlack[y][x];
    //white
    }else if(piece == "P"){
        return wPawnV + pawnEvalWhite[y][x];
    } else if (piece =="R"){
        return wRookV + rookEvalWhite[y][x] ;
    }else if (piece =="K"){
        return  wKnightV + knightEval[y][x];
    }else if (piece =="B"){
        return wBishopV + bishopEvalWhite[y][x];
    }else if (piece =="Q"){
        return wQueenV + evalQueen[y][x];
    }else if (piece =="K"){
        return wKingV + kingEvalWhite[y][x];
    }
}



void moveGeneration::pushMoves(int x, int y, int x2, int y2){
    possibleMoves.push_back(x);
    possibleMoves.push_back(y);
    possibleMoves.push_back(x2);
    possibleMoves.push_back(y2);
}

void moveGeneration::resetPossibleMoves()
{
    possibleMoves.clear();
}

void moveGeneration::returnMove()
{

}






