#include "movegeneration.h"

//vector of all possible moves for one side
std::vector<std::string> possibleMoves;

moveGeneration::moveGeneration()
{

    //ai is black ~ possibly replace player moves set too
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(boardArr[i][j] == "p"){
                blackPawn(j , i);
            }else if(boardArr[i][j] == "r"){
                rook(j , i);
            }
        }
    }
}

moveGeneration::blackPawn(int x, int y)
{
    std::string tx = std::to_string(x), ty = std::to_string(y);
    //move forward one or two first turn
    if(y == 1 && boardArr[y+1][x] == " "){
        possibleMoves.push_back(tx+ty+tx+(ty+1));
        int a = (int)tx+ty+tx+(ty+1);
    }

}

moveGeneration::rook(int x, int y)
{

}

moveGeneration::knight(int x, int y)
{

}

moveGeneration::bishop(int x, int y)
{

}

moveGeneration::queen(int x, int y)
{

}

moveGeneration::king(int x, int y)
{

}







