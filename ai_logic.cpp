#include "ai_logic.h"

#include <stdlib.h>
#include <time.h>

// ai values for best possible move once computed
int aiX, aiY, aiX1, aiY1;

Ai_Logic::Ai_Logic()
{

}

int Ai_Logic::calculateBestMove()
{
    //generate all possible moves for one turn
    moveGeneration *genMoves = new moveGeneration;
    //generate more readable moves
    genMoves->ugly_moves();
    std::vector<std::string> possible_moves = genMoves->neatMoves;

    //random move
    srand (time(NULL));
    int randomMove = rand() % possible_moves.size() + 1;

    std::string zMove = possible_moves[randomMove];

    aiX = (int)zMove[0]-'0';
    aiY = (int)zMove[1]-'0';
    aiX1 = (int)zMove[2]-'0';
    aiY1 = (int)zMove[3]-'0';

}

float Ai_Logic::evaluateBoard()
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

float Ai_Logic::getPieceValue(std::string piece, int x, int y)
{
    //get value of piece on board
    if(piece == " "){
        return 0;
    }
    float absoluteValue = getAbsoluteValue(piece, x, y);

    //return negative value if piece black, posative if white
    if(piece == "P" || piece == "R" || piece == "N" || piece == "B" || piece == "K" || piece == "Q"){
        return absoluteValue;
    } else {
        return -absoluteValue;
    }
}

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

float Ai_Logic::getAbsoluteValue(std::string piece, int x, int y)
{
    //find which piece it is and return value
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
