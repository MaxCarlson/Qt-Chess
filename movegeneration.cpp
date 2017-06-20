#include "movegeneration.h"
#include <iostream>





//strings for storing pieces while checking value of board for moves
std::string storePiece, storePiece1;


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
    //move moves from a %4 int vector into a string vector containing move info in one slot
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
    storePiece = boardArr[y][x];
    storePiece1 = boardArr[y2][x2];

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
    if(boardArr[y+1][x-1] != " " && whiteOrBlack(boardArr[y+1][x-1], x-1, y+1) == true){
        pushMoves(x, y, x-1, y+1);
    }
    //right take out
    if(boardArr[y+1][x+1] != " " && whiteOrBlack(boardArr[y+1][x+1], x+1, y+1) == true){
        pushMoves(x, y, x+1, y+1);
    }

}

void moveGeneration::rook(int x, int y)
{
    //up
    for(int i = y-1; i >= 0; i--){
        if(boardArr[i][x] != " " && whiteOrBlack(boardArr[i][x], x, i) == true){
            pushMoves(x, y, x, i);
            break;
        } else if(boardArr[i][x] == " "){
            pushMoves(x, y, x, i);
        } else {
            break;
        }
    }
    //down
    for(int i = y+1; i < 8; i++){
        if(boardArr[i][x] != " " && whiteOrBlack(boardArr[i][x], x, i) == true){
            pushMoves(x, y, x, i);
            break;
        } else if(boardArr[i][x] == " "){
            pushMoves(x, y, x, i);
        } else {
            break;
        }
    }
    //left
    for(int i = x-1; i >= 0; i--){
        if(boardArr[y][i] != " " && whiteOrBlack(boardArr[y][i], i, y) == true){
            pushMoves(x, y, i, y);
            break;
        } else if(boardArr[y][i] == " "){
            pushMoves(x, y, i, y);
        } else {
            break;
        }
    }
    //right
    for(int i = x+1; i < 8; i++){
        if(boardArr[y][i] != " " && whiteOrBlack(boardArr[y][i], i, y) == true){
            pushMoves(x, y, i, y);
            break;
        } else if(boardArr[y][i] == " "){
            pushMoves(x, y, i, y);
        } else {
            break;
        }
    }
}

void moveGeneration::knight(int x, int y)
{

}

void moveGeneration::bishop(int x, int y)
{
    //up left
    int tmp = y-1;
    for(int i = x-1; i >= 0; i--){
        if(boardArr[tmp][i] != " " && whiteOrBlack(boardArr[tmp][i], i, tmp) == true){
            pushMoves(x, y, i, tmp);
            break;
        } else if(boardArr[tmp][i] == " "){
            pushMoves(x, y, i, tmp);
        } else {
            break;
        }
        tmp -= 1;
    }

    //up right
    tmp = y-1;
    for(int i = x+1; i < 8; i++){
        if(boardArr[tmp][i] != " " && whiteOrBlack(boardArr[tmp][i], i, tmp) == true){
            pushMoves(x, y, i, tmp);
            break;
        } else if(boardArr[tmp][i] == " "){
            pushMoves(x, y, i, tmp);
        } else {
            break;
        }
        tmp -= 1;
    }

    //down right
    tmp = y + 1;
    for(int i = x+1; i < 8; i++){
        if(boardArr[tmp][i] != " " && whiteOrBlack(boardArr[tmp][i], i, tmp) == true){
            pushMoves(x, y, i, tmp);
            break;
        } else if(boardArr[tmp][i] == " "){
            pushMoves(x, y, i, tmp);
        } else {
            break;
        }
        tmp += 1;
    }

    //down left
    tmp = y + 1;
    for(int i = x-1; i >= 0; i--){
        if(boardArr[tmp][i] != " " && whiteOrBlack(boardArr[tmp][i], i, tmp) == true){
            pushMoves(x, y, i, tmp);
            break;
        } else if(boardArr[tmp][i] == " "){
            pushMoves(x, y, i, tmp);
        } else {
            break;
        }
        tmp += 1;
    }

}

void moveGeneration::queen(int x, int y)
{
    //up
    for(int i = y-1; i >= 0; i--){
        if(boardArr[i][x] != " " && whiteOrBlack(boardArr[i][x], x, i) == true){
            pushMoves(x, y, x, i);
            break;
        } else if (boardArr[i][x] == " "){
            pushMoves(x, y, x, i);
        } else {
            break;
        }
    }

    //down
    for(int i = y+1; i < 8; i++){
        if(boardArr[i][x] != " " && whiteOrBlack(boardArr[i][x], x, i) == true){
            pushMoves(x, y, x, i);
            break;
        } else if (boardArr[i][x] == " "){
            pushMoves(x, y, x, i);
        } else {
            break;
        }
    }

    //left
    for(int i = x-1; i >= 0; i--){
        if(boardArr[y][i] != " " && whiteOrBlack(boardArr[y][i], i, y) == true){
            pushMoves(x, y, i, y);
            break;
        } else if(boardArr[y][i] == " "){
            pushMoves(x, y, i, y);
        } else {
            break;
        }
    }

    //right
    for(int i = x+1; i < 8; i++){
        if(boardArr[y][i] != " " && whiteOrBlack(boardArr[y][i], i, y) == true){
            pushMoves(x, y, i, y);
            break;
        } else if(boardArr[y][i] == " "){
            pushMoves(x, y, i, y);
        } else {
            break;
        }
    }

    //up left
    int tmp = y-1;
    for(int i = x-1; i >= 0; i--){
        if(boardArr[tmp][i] != " " && whiteOrBlack(boardArr[tmp][i], i, tmp) == true){
            pushMoves(x, y, i, tmp);
            break;
        } else if(boardArr[tmp][i] == " "){
            pushMoves(x, y, i, tmp);
        } else {
            break;
        }
        tmp -= 1;
    }

    //up right
    tmp = y-1;
    for(int i = x+1; i < 8; i++){
        if(boardArr[tmp][i] != " " && whiteOrBlack(boardArr[tmp][i], i, tmp) == true){
            pushMoves(x, y, i, tmp);
            break;
        } else if(boardArr[tmp][i] == " "){
            pushMoves(x, y, i, tmp);
        } else {
            break;
        }
        tmp -= 1;
    }

    //down right
    tmp = y + 1;
    for(int i = x+1; i < 8; i++){
        if(boardArr[tmp][i] != " " && whiteOrBlack(boardArr[tmp][i], i, tmp) == true){
            pushMoves(x, y, i, tmp);
            break;
        } else if(boardArr[tmp][i] == " "){
            pushMoves(x, y, i, tmp);
        } else {
            break;
        }
        tmp += 1;
    }

    //down left
    tmp = y + 1;
    for(int i = x-1; i >= 0; i--){
        if(boardArr[tmp][i] != " " && whiteOrBlack(boardArr[tmp][i], i, tmp) == true){
            pushMoves(x, y, i, tmp);
            break;
        } else if(boardArr[tmp][i] == " "){
            pushMoves(x, y, i, tmp);
        } else {
            break;
        }
        tmp += 1;
    }
}

void moveGeneration::king(int x, int y)
{
    // NEED castling and king safety checks

    //up
    if(y > 0 && whiteOrBlack(boardArr[y-1][x], x, y-1) == true){
        pushMoves(x, y, x, y-1);
    }
    // down
    if(y < 7 && whiteOrBlack(boardArr[y+1][x], x, y+1) == true){
        pushMoves(x, y, x, y+1);
    }
    //left
    if(x > 0 && whiteOrBlack(boardArr[y][x-1], x-1, y) == true){
        pushMoves(x, y, x-1, y);
    }
    //right
    if(x < 7 && whiteOrBlack(boardArr[y][x+1], x+1, y) == true){
        pushMoves(x, y, x+1, y);
    }
    //up left
    if(x > 0 && y > 0 && whiteOrBlack(boardArr[y-1][x-1], x-1, y-1) == true){
        pushMoves(x, y, x-1, y-1);
    }
    // up right
    if(x < 7 && y > 0 && whiteOrBlack(boardArr[y-1][x+1], x+1, y-1) == true){
        pushMoves(x, y, x+1, y-1);
    }
    //down right
    if(x < 7 && y < 7 && whiteOrBlack(boardArr[y+1][x+1], x+1, y+1) == true){
        pushMoves(x, y, x+1, y+1);
    }
    //down left
    if(x > 0 && y < 7 && whiteOrBlack(boardArr[y+1][x-1], x-1, y+1) == true){
        pushMoves(x, y, x-1, y+1);
    }

}

void moveGeneration::pushMoves(int x, int y, int x2, int y2){
    possibleMoves.push_back(x);
    possibleMoves.push_back(y);
    possibleMoves.push_back(x2);
    possibleMoves.push_back(y2);
}

bool moveGeneration::whiteOrBlack(std::string tmpPiece, int x, int y)
{
    if(turns%2 == 0){
        for(int i = 0; i < 6; i++){
            if(boardArr[y][x] == whitePieces[i]){
                return false;
            }
        }

        return true;
    } else if (turns % 2 == 1){
        for(int i = 0; i < 6; i++){
            if(boardArr[y][x] == blackPieces[i]){
                return false;
            }
        }
        return true;
    }
}

void moveGeneration::resetPossibleMoves()
{
    possibleMoves.clear();
}

void moveGeneration::returnMove()
{

}






