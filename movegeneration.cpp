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
    if(turns % 2 == 0){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(boardArr[i][j] == "P"){
                    whitePawn(j , i);
                }else if(boardArr[i][j] == "R"){
                    rook(j , i);
                } else if(boardArr[i][j] == "N"){
                    knight(j, i);
                }else if(boardArr[i][j] == "B"){
                    bishop(j, i);
                } else if(boardArr[i][j] == "Q"){
                    queen(j, i);
                } else if(boardArr[i][j] == "K"){
                    king(j, i);
                }
            }
        }
    } else if (turns % 2 == 1){
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
    if(boardArr[y+1][x] == " " && y < 7){
        if(safetyCheck(x, y, x, y+1) == true){
            pushMoves(x, y, x, y+1);
        }
    }
    //or two first turn
    if(y == 1 && boardArr[y+1][x] == " " && boardArr[y+2][x] == " "){
        if(safetyCheck(x, y, x, y+2) == true){
             pushMoves(x, y, x, y+2);
        }
    }
    //take out side-wase left
    if(boardArr[y+1][x-1] != " " && whiteOrBlack(boardArr[y+1][x-1], x-1, y+1) == true && x > 0 && y < 7){
        if(safetyCheck(x, y, x-1, y+1) == true){
            pushMoves(x, y, x-1, y+1);
        }
    }
    //right take out
    if(boardArr[y+1][x+1] != " " && whiteOrBlack(boardArr[y+1][x+1], x+1, y+1) == true && x < 7 && y < 7){
        if(safetyCheck(x, y, x+1, y+1) == true){
            pushMoves(x, y, x+1, y+1);
        }
    }

}

void moveGeneration::whitePawn(int x, int y){

}

void moveGeneration::rook(int x, int y)
{
    //up
    for(int i = y-1; i >= 0; i--){
        if(boardArr[i][x] != " " && whiteOrBlack(boardArr[i][x], x, i) == true){
            if(safetyCheck(x, y, x, i) == true){
                pushMoves(x, y, x, i);
                break;
            }

        } else if(boardArr[i][x] == " "){
            if(safetyCheck(x, y, x, i) == true){
                pushMoves(x, y, x, i);
                break;
            }

        } else {
            break;
        }
    }
    //down
    for(int i = y+1; i < 8; i++){
        if(boardArr[i][x] != " " && whiteOrBlack(boardArr[i][x], x, i) == true){
            if(safetyCheck(x, y, x, i) == true){
                pushMoves(x, y, x, i);
                break;
            }

        } else if(boardArr[i][x] == " "){
            if(safetyCheck(x, y, x, i) == true){
                pushMoves(x, y, x, i);
            }

        } else {
            break;
        }
    }
    //left
    for(int i = x-1; i >= 0; i--){
        if(boardArr[y][i] != " " && whiteOrBlack(boardArr[y][i], i, y) == true){
            if(safetyCheck(x, y, i, y) == true){
                pushMoves(x, y, i, y);
                break;
            }

        } else if(boardArr[y][i] == " "){
            if(safetyCheck(x, y, i, y) == true){
                pushMoves(x, y, i, y);
            }
        } else {
            break;
        }
    }
    //right
    for(int i = x+1; i < 8; i++){
        if(boardArr[y][i] != " " && whiteOrBlack(boardArr[y][i], i, y) == true){
            if(safetyCheck(x, y, i, y) == true){
                pushMoves(x, y, i, y);
                break;
            }

        } else if(boardArr[y][i] == " "){
            if(safetyCheck(x, y, i, y) == true){
                pushMoves(x, y, i, y);
            }

        } else {
            break;
        }
    }
}

void moveGeneration::knight(int x, int y)
{
    //clockwise starting at up up right
    //up right
    if(x < 7 && y > 1){
        if(safetyCheck(x, y, x+1, y -2) == true && whiteOrBlack(boardArr[y-2][x+1], x+1, y-2) == true){
            pushMoves(x, y, x+1, y -2);
        }
    }

    if(x < 6 && y > 0){
        if(safetyCheck(x, y, x+2, y - 1) == true && whiteOrBlack(boardArr[y-1][x+2], x+2, y-1) == true){
            pushMoves(x, y, x+2, y - 1);
        }
    }

    //down right
    if(x < 6 && y < 7){
        if(safetyCheck(x, y, x+2, y + 1) == true && whiteOrBlack(boardArr[y+1][x+2], x+2, y+1) == true){
            pushMoves(x, y, x+2, y + 1);
        }
    }

    if(x < 7 && y < 6){
        if(safetyCheck(x, y, x+1, y + 2) == true && whiteOrBlack(boardArr[y+2][x+1], x+1, y+2) == true){
            pushMoves(x, y, x+1, y + 2 );
        }
    }

    //down left
    if(x > 0 && y < 6){
        if(safetyCheck(x, y, x-1, y + 2) == true && whiteOrBlack(boardArr[y+2][x-1], x-1, y+2) == true){
            pushMoves(x, y, x-1, y + 2);
        }
    }

    if(x > 1 && y < 7){
        if(safetyCheck(x, y, x-2, y + 1) == true && whiteOrBlack(boardArr[y+1][x-2], x-2, y+1) == true){
            pushMoves(x, y, x-2, y + 1);
        }
    }

    //up left
    if(x > 1 && y > 0){
        if(safetyCheck(x, y, x-2, y - 1) == true && whiteOrBlack(boardArr[y-1][x-2], x-2, y-1) == true){
            pushMoves(x, y, x-2, y - 1);
        }
    }

    if(x > 0 && y > 1){
        if(safetyCheck(x, y, x-1, y - 2) == true && whiteOrBlack(boardArr[y-2][x-1], x-1, y-2) == true){
            pushMoves(x, y, x-1, y - 2);
        }
    }

}

void moveGeneration::bishop(int x, int y)
{
    //up left
    int tmp = y-1;
    for(int i = x-1; i >= 0; i--){
        if(tmp < 0){
            break;
        }
        if(boardArr[tmp][i] != " " && whiteOrBlack(boardArr[tmp][i], i, tmp) == true && tmp >= 0){
            if(safetyCheck(x, y, i, tmp) == true){
                pushMoves(x, y, i, tmp);
                break;
            }

        } else if(boardArr[tmp][i] == " "){
            if(safetyCheck(x, y, i, tmp) == true){
                pushMoves(x, y, i, tmp);

            }
        } else {
            break;
        }
        tmp -= 1;
    }

    //up right
    tmp = y-1;
    for(int i = x+1; i < 8; i++){
        if(tmp < 0){
            break;
        }
        if(boardArr[tmp][i] != " " && whiteOrBlack(boardArr[tmp][i], i, tmp) == true){
            if(safetyCheck(x, y, i, tmp) == true){
                pushMoves(x, y, i, tmp);
                break;
            }

        } else if(boardArr[tmp][i] == " "){
            if(safetyCheck(x, y, i, tmp) == true){
                pushMoves(x, y, i, tmp);

            }

        } else {
            break;
        }
        tmp -= 1;
    }

    //down right
    tmp = y + 1;
    for(int i = x+1; i < 8; i++){
        if(tmp > 7){
            break;
        }
        if(boardArr[tmp][i] != " " && whiteOrBlack(boardArr[tmp][i], i, tmp) == true){
            if(safetyCheck(x, y, i, tmp) == true){
                pushMoves(x, y, i, tmp);
                break;
            }

        } else if(boardArr[tmp][i] == " "){
            if(safetyCheck(x, y, i, tmp) == true){
                pushMoves(x, y, i, tmp);
            }

        } else {
            break;
        }
        tmp += 1;
    }

    //down left
    tmp = y + 1;
    for(int i = x-1; i >= 0; i--){
        if(tmp > 7){
            break;
        }
        if(boardArr[tmp][i] != " " && whiteOrBlack(boardArr[tmp][i], i, tmp) == true){
            if(safetyCheck(x, y, i, tmp) == true){
                pushMoves(x, y, i, tmp);
                break;
            }

        } else if(boardArr[tmp][i] == " "){
            if(safetyCheck(x, y, i, tmp) == true){
                pushMoves(x, y, i, tmp);

            }

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
            if(safetyCheck(x, y, x, i) == true){
                pushMoves(x, y, x, i);
                break;
            }

        } else if (boardArr[i][x] == " "){
            if(safetyCheck(x, y, x, i) == true){
                pushMoves(x, y, x, i);

            }

        } else {
            break;
        }
    }

    //down
    for(int i = y+1; i < 8; i++){
        if(boardArr[i][x] != " " && whiteOrBlack(boardArr[i][x], x, i) == true){
            if(safetyCheck(x, y, x, i) == true){
                pushMoves(x, y, x, i);
                break;
            }

        } else if (boardArr[i][x] == " "){
            if(safetyCheck(x, y, x, i) == true){
                pushMoves(x, y, x, i);

            }
        } else {
            break;
        }
    }

    //left
    for(int i = x-1; i >= 0; i--){
        if(boardArr[y][i] != " " && whiteOrBlack(boardArr[y][i], i, y) == true){
            if(safetyCheck(x, y, i, y) == true){
                pushMoves(x, y, i, y);
                break;
            }

        } else if(boardArr[y][i] == " "){
            if(safetyCheck(x, y, i, y) == true){
                pushMoves(x, y, i, y);

            }

        } else {
            break;
        }
    }

    //right
    for(int i = x+1; i < 8; i++){
        if(boardArr[y][i] != " " && whiteOrBlack(boardArr[y][i], i, y) == true){
            if(safetyCheck(x, y, i, y) == true){
                pushMoves(x, y, i, y);
                break;
            }
        } else if(boardArr[y][i] == " "){
            if(safetyCheck(x, y, i, y) == true){
                pushMoves(x, y, i, y);

            }
        } else {
            break;
        }
    }

    //up left
    int tmp = y-1;
    for(int i = x-1; i >= 0; i--){
        if(tmp < 0){
            break;
        }
        if(boardArr[tmp][i] != " " && whiteOrBlack(boardArr[tmp][i], i, tmp) == true){
            if(safetyCheck(x, y, i, tmp) == true){
                pushMoves(x, y, i, tmp);
                break;
            }

        } else if(boardArr[tmp][i] == " " ){
            if(safetyCheck(x, y, i, tmp) == true){
                pushMoves(x, y, i, tmp);

            }
        } else {
            break;
        }
        tmp -= 1;
    }

    //up right
    tmp = y-1;
    for(int i = x+1; i < 8; i++){
        if(tmp < 0){
            break;
        }
        if(boardArr[tmp][i] != " " && whiteOrBlack(boardArr[tmp][i], i, tmp) == true){
            if(safetyCheck(x, y, i, tmp) == true){
                pushMoves(x, y, i, tmp);
                break;
            }
        } else if(boardArr[tmp][i] == " "){
            if(safetyCheck(x, y, i, tmp) == true){
                pushMoves(x, y, i, tmp);

            }
        } else {
            break;
        }
        tmp -= 1;
    }

    //down right
    tmp = y + 1;
    for(int i = x+1; i < 8; i++){
        if(tmp > 7){
            break;
        }
        if(boardArr[tmp][i] != " " && whiteOrBlack(boardArr[tmp][i], i, tmp) == true){
            if(safetyCheck(x, y, i, tmp) == true){
                pushMoves(x, y, i, tmp);
                break;
            }
        } else if(boardArr[tmp][i] == " "){
            if(safetyCheck(x, y, i, tmp) == true){
                pushMoves(x, y, i, tmp);

            }
        } else {
            break;
        }
        tmp += 1;
    }

    //down left
    tmp = y + 1;
    for(int i = x-1; i >= 0; i--){
        if(tmp > 7){
            break;
        }
        if(boardArr[tmp][i] != " " && whiteOrBlack(boardArr[tmp][i], i, tmp) == true){
            if(safetyCheck(x, y, i, tmp) == true){
                pushMoves(x, y, i, tmp);
                break;
            }
        } else if(boardArr[tmp][i] == " "){
            if(safetyCheck(x, y, i, tmp) == true){
                pushMoves(x, y, i, tmp);

            }
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
        if(safetyCheck(x, y, x, y-1) == true){
            pushMoves(x, y, x, y-1);
        }

    }
    // down
    if(y < 7 && whiteOrBlack(boardArr[y+1][x], x, y+1) == true){
        if(safetyCheck(x, y, x, y+1) == true){
            pushMoves(x, y, x, y+1);
        }

    }
    //left
    if(x > 0 && whiteOrBlack(boardArr[y][x-1], x-1, y) == true){
        if(safetyCheck(x, y, x-1, y) == true){
            pushMoves(x, y, x-1, y);
        }

    }
    //right
    if(x < 7 && whiteOrBlack(boardArr[y][x+1], x+1, y) == true){
        if(safetyCheck(x, y, x+1, y) == true){
            pushMoves(x, y, x+1, y);
        }

    }
    //up left
    if(x > 0 && y > 0 && whiteOrBlack(boardArr[y-1][x-1], x-1, y-1) == true){
        if(safetyCheck(x, y, x-1, y-1) == true){
            pushMoves(x, y, x-1, y-1);
        }

    }
    // up right
    if(x < 7 && y > 0 && whiteOrBlack(boardArr[y-1][x+1], x+1, y-1) == true){
        if(safetyCheck(x, y, x+1, y-1) == true){
            pushMoves(x, y, x+1, y-1);
        }

    }
    //down right
    if(x < 7 && y < 7 && whiteOrBlack(boardArr[y+1][x+1], x+1, y+1) == true){
        if(safetyCheck(x, y, x+1, y+1) == true){
            pushMoves(x, y, x+1, y+1);
        }

    }
    //down left
    if(x > 0 && y < 7 && whiteOrBlack(boardArr[y+1][x-1], x-1, y+1) == true){
        if(safetyCheck(x, y, x-1, y+1) == true){
            pushMoves(x, y, x-1, y+1);
        }

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

//King safety check functions below this line

bool moveGeneration::safetyCheck(int x, int y, int x2, int y2)
{
    //make bool boards all true
    resetSafetyBoards();
    //move piece on board in order to test safety
    testBoardValue(x, y, x2, y2);
    //mark bool boards with updated piece temp move posititon
    createKingSafteyBoard();

    //if king is safe return true and reset piece so another move can be tested
    if(isKingSafe() == true){
        undo_move(x, y, x2, y2);
        //resetSafetyBoards();
        return true;
    }

    undo_move(x, y, x2, y2);
    //resetSafetyBoards();
    return false;
}

bool moveGeneration::resetSafetyBoards(){
    //setting king safety arrays to all true
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(turns % 2 == 0){
                whiteSafe[i][j] = true;
            } else {
                blackSafe[i][j] = true;
            }
        }
    }

}


bool moveGeneration::isKingSafe(){
    int x = 0, y = 0;
    if(turns % 2 == 0){
        //find king
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(boardArr[i][j] == "K"){
                    x = j;
                    y = i;
                }
            }
        }
        //find if king position is safe
        if(whiteSafe[y][x] == false){
            return false;
        }
        return true;

    } else if (turns % 2 == 1){
        //find king black
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(boardArr[i][j] == "k"){
                    x = j;
                    y = i;
                }
            }
        }
        //find if king position is safe
        if(blackSafe[y][x] == false){
            return false;
        }
        return true;
    }
}


//checking all squares to see where king can move or not
void moveGeneration::createKingSafteyBoard(){

    if(turns % 2 == 0){
        //denoting we're marking whites un-safe areas
        char w = 'w';
        //array loop to mark board of unsafe areas
        for(int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if(boardArr[i][j] == "p"){
                    //pawn sanity checks
                    if(i < 7 && j < 7){
                        whiteSafe[i+1][j+1] = false;
                    }
                    if (i < 7 && j > 0){
                        whiteSafe[i+1][j-1] = false;
                    }
                }else if(boardArr[i][j] == "r"){
                    upDownLeftRightM(j, i, w);
                }else if(boardArr[i][j] == "n"){
                    knightM(j, i, w);
                } else if(boardArr[i][j] == "b"){
                    diagonalM(j, i, w);
                } else if (boardArr[i][j] == "q"){
                    diagonalM(j, i, w);
                    upDownLeftRightM(j, i, w);
                }else if (boardArr[i][j] == "k"){
                    kingM(j, i, w);
                }
            }
        }
    } else if (turns % 2 == 1){
        //denoting we're marking blacks un-safe areas
        char w = 'b';
        //array loop to mark board of unsafe areas
        for(int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if(boardArr[i][j] == "P"){
                    //pawn sanity checks
                    if(i > 0 && j<7){
                        blackSafe[i-1][j+1] = false;
                    }
                    if(i > 0 && j > 0){
                        blackSafe[i-1][j-1] = false;
                    }
                }else if(boardArr[i][j] == "R"){
                    upDownLeftRightM(j, i, w);
                }else if(boardArr[i][j] == "N"){
                    knightM(j, i, w);
                } else if(boardArr[i][j] == "B"){
                    diagonalM(j, i, w);
                } else if (boardArr[i][j] == "Q"){
                    diagonalM(j, i, w);
                    upDownLeftRightM(j, i, w);
                }else if (boardArr[i][j] == "K"){
                    kingM(j, i, w);
                }
            }
        }
    }

}

//mark where is unsafe and figure out who
void moveGeneration::whiteOrBlack(int x, int y, char wb){
    //sanity check
    if(x > 7 || x < 0){
        return;
    } else if (y > 7 || y < 0){
        return;
    }
    if(wb == 'w'){
        whiteSafe[y][x] = false;
    } else if (wb == 'b'){
        blackSafe[y][x] = false;
    }
}

bool moveGeneration::sanityCheck(int x, int y){
    if(x > 7 || x < 0){
        return false;
    }else if(y > 7 || y < 0){
        return false;
    }
    return true;
}

void moveGeneration::upDownLeftRightM(int x, int y, char wb){
    //mark up unsafe
    for(int i = y-1; i > -1; i--){
        //sanity checks
        if(sanityCheck(x, i) == true){
            if(boardArr[i][x] != " "){
                whiteOrBlack(x,i,wb);
                break;
            }
            whiteOrBlack(x,i,wb);
        }

    }
    //mark down
    for(int i = y+1; i < 8; i++){
        if(sanityCheck(x, i) == true){
            if(boardArr[i][x] != " "){
                whiteOrBlack(x,i,wb);
                break;
            }
            whiteOrBlack(x,i,wb);
        }

    }

    //mark right unsafe
    for(int i = x+1; i < 8; i++){
        if(sanityCheck(i, y) == true){
            if(boardArr[y][i] != " "){
                whiteOrBlack(i,y,wb);
                break;
            }
            whiteOrBlack(i,y,wb);
        }

    }

    //mark left
    for(int i = x-1; i > -1; i--){
        if(sanityCheck(i, y) == true){
            if(boardArr[y][i] != " "){
                whiteOrBlack(i,y,wb);
                break;
            }
            whiteOrBlack(i,y,wb);
        }

    }
}
void moveGeneration::diagonalM(int x, int y, char wb){
    int j = y-1;
    //up right safety check
    for(int i = x+1; i < 8; i++){
        //sanity checks
        if(sanityCheck(i, j) == true){
            if(boardArr[j][i] != " "){
                whiteOrBlack(i,j,wb);
                break;
            }
            whiteOrBlack(i,j,wb);
        }
        j --;
    }

    //down right
    j = y+1;
    for(int i = x+1; i < 8; i++){
        if(sanityCheck(i, j) == true){
            if(boardArr[j][i] != " "){
                whiteOrBlack(i,j,wb);
                break;
            }
            whiteOrBlack(i,j,wb);
        }
        j ++;
    }

    //down left
    j = y+1;
    for(int i = x-1; i > -1; i--){
        if(sanityCheck(i, j) == true){
            if(boardArr[j][i] != " "){
                whiteOrBlack(i,j,wb);
                break;
            }
            whiteOrBlack(i,j,wb);
        }
        j ++;
    }

    //up left
    j = y-1;
    for(int i = x-1; i > -1; i--){
        if(sanityCheck(i, j) == true){
            if(boardArr[j][i] != " "){
                whiteOrBlack(i,j,wb);
                break;
            }
            whiteOrBlack(i,j,wb);
        }
        j --;
    }
}

void moveGeneration::knightM(int x, int y, char wb){
    //counter clock-wise all knight jumps
    //Up right
    whiteOrBlack(x-2,y-1,wb);
    whiteOrBlack(x-1,y-2,wb);
    //Down right
    whiteOrBlack(x-2,y+1,wb);
    whiteOrBlack(x-1,y+2,wb);
    //Down left
    whiteOrBlack(x+1,y+2,wb);
    whiteOrBlack(x+2,y+1,wb);
    //Up left
    whiteOrBlack(x+2,y-1,wb);
    whiteOrBlack(x+1,y-2,wb);
}

void moveGeneration::kingM(int x, int y, char wb){
    //clock-wise starting at 12
    //king attack safety marking
    whiteOrBlack(x,y-1,wb);
    whiteOrBlack(x+1,y-1,wb);
    whiteOrBlack(x+1,y,wb);
    whiteOrBlack(x+1,y+1,wb);
    whiteOrBlack(x,y+1,wb);
    whiteOrBlack(x-1,y+1,wb);
    whiteOrBlack(x-1,y,wb);
    whiteOrBlack(x-1,y-1,wb);
}












