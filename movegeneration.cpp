#include "movegeneration.h"
#include <iostream>









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

void moveGeneration::ugly_moves()
{
    std::string temp, temp1, temp2, temp3, temp4;
    for(int i = 0; i < possibleMoves.size(); i+=4){
        temp = std::to_string(possibleMoves[i]);
        temp1 = std::to_string(possibleMoves[i+1]);
        temp2 = std::to_string(possibleMoves[i+2]);
        temp3 = std::to_string(possibleMoves[i+3]);
        temp4 = temp + temp1 + temp2 + temp3;
        if(temp4.length()==4){
            neatMoves.push_back(temp4);
        }

    }


}

float moveGeneration::testBoardValue(int x, int y, int x2, int y2)
{
    //store two pieces at board before change state
    std::string storePiece = boardArr[y][x], storePiece1 = boardArr[y2][x2];
    boardArr[y][x] = " ";
    boardArr[y2][x2] = storePiece;


}

void moveGeneration::undo_move(int x, int y, int x2, int y2)
{
    boardArr[y][x] = storePiece;
    boardArr[y2][x2] = storePiece1;

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






