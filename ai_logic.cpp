#include "ai_logic.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>


//best overall move as calced
std::string bestMove;

//holds board state before any moves or trys
std::string board1[8][8];
//holds state of initial board + 1 move
std::string board2[8][8];






Ai_Logic::Ai_Logic()
{

}

std::string Ai_Logic::miniMaxRoot(int depth, bool isMaximisingPlayer)
{
    //generate all possible moves for one turn // TEST Just create movegen object access move gen from func ugly_moves
    moveGeneration *genMoves = new moveGeneration;

    //Move timer for ai
    clock_t aiMoveTimerStart = clock();

    //Store state of the board before any moves of the Ai turn have been done
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board1[i][j] = boardArr[i][j];
        }
    }

    //generate first possible initial moves
    genMoves->genMoves();

    //Make moves readable
    genMoves->ugly_moves();

    //get vector of possible moves for current turn
    std::vector<std::string> possible_moves = genMoves->neatMoves;
    genMoves->neatMoves.clear();

    // ai temp values for passing to testBoardValues for assessing a board position
    int aiX, aiY, aiX1, aiY1;

    //for moves to compete against
    float bestMoveValue = -9999;

    //best move to return after all calcs
    std::string bestMoveFound;

    //compare moves
    for(int i = 0; i < possible_moves.size(); i++){
        std::string tempMove = possible_moves[i];
        aiX = (int)tempMove[0]-'0';
        aiY = (int)tempMove[1]-'0';
        aiX1 = (int)tempMove[2]-'0';
        aiY1 = (int)tempMove[3]-'0';

        //change board to move in set of first moves
        boardArr[aiY1][aiX1] = boardArr[aiY][aiX];
        boardArr[aiY][aiX] = " ";

        //Store state of board after one of the first moves
        //so it can be un-done at the end of the recursive miniMax function,
        //each time to try a new move from the inital moves (possible_moves)
        for(int k = 0; k < 8; k++){
            for(int j = 0; j < 8; j++){
                board2[k][j] = boardArr[k][j];
            }
        }

        //test it's value and store it and test if white or black,
        float tempValue = miniMax(depth -1, -10000, 10000, ! isMaximisingPlayer);

        //Change board to state it was in before all testing of turn
        undo_move1();

        //if move is better then the best one store it
        if(tempValue >= bestMoveValue){
            bestMoveValue = tempValue;
            bestMoveFound = tempMove;

        }

    }

    clock_t aiEndMoveTImer = clock();

    std::cout << positionCount << std::endl;
    std::cout << (double) (aiEndMoveTImer - aiMoveTimerStart) / CLOCKS_PER_SEC << " seconds" << std::endl;
    possible_moves.clear();
    return bestMoveFound;
    positionCount = 0;
}

float Ai_Logic::miniMax(float depth, float alpha, float beta, bool isMaximisingPlayer)
{
    positionCount ++;
    int whiteMoves = 0;
    if(depth <= 0){
        return -evaluateBoard();
    }

    moveGeneration *newGenMoves = new moveGeneration;

    if(isMaximisingPlayer == true){
        newGenMoves->genMoves();
        newGenMoves->ugly_moves();
    } else{
        turns += 1;
        newGenMoves->genMoves();
        newGenMoves->ugly_moves();
        turns -= 1;
    }


    std::vector<std::string> future_possible_moves = newGenMoves->neatMoves;
    newGenMoves->neatMoves.clear();

    int x, y, x1, y1;

    if(isMaximisingPlayer == true){
        float bestTempMove = -9999;
        for(int i = 0; i < future_possible_moves.size(); i++){
            //change board accoriding to i possible move
            std::string tempMove = future_possible_moves[i];
            x = (int)tempMove[0]-'0';
            y = (int)tempMove[1]-'0';
            x1 = (int)tempMove[2]-'0';
            y1 = (int)tempMove[3]-'0';


            //TEST piece recovery in new undo function
            std::string piece1 = boardArr[y][x], piece2 = boardArr[y1][x1];

            //set board to test move value
            boardArr[y1][x1] = boardArr[y][x];
            boardArr[y][x] = " ";

            //recursively test best move
            bestTempMove = std::max(bestTempMove, miniMax(depth-1, alpha, beta,  ! isMaximisingPlayer));

            //FOR TESTING
            for(int k = 0; k < 8; k++){
                for(int j = 0; j < 8; j++){
                    std::cout << boardArr[k][j];
                }
                std::cout << std::endl;
            }

            //undo board
            //undo_move2();
            undoMove(x, y, x1, y1, piece1, piece2);

            //alpha beta pruning
            alpha = std::max(alpha, bestTempMove);

            if(beta <= alpha){

                future_possible_moves.clear();
                return bestTempMove;
            }

        }


        future_possible_moves.clear();
        return bestTempMove;


    } else {

        float bestTempMove = 9999;
        for(int i = 0; i < future_possible_moves.size(); i++){
            whiteMoves ++;

            //change board accoriding to i possible move
            std::string tempMove = future_possible_moves[i];
            x = (int)tempMove[0]-'0';
            y = (int)tempMove[1]-'0';
            x1 = (int)tempMove[2]-'0';
            y1 = (int)tempMove[3]-'0';

            //TEST piece recovery in new undo function
            std::string piece1 = boardArr[y][x], piece2 = boardArr[y1][x1];

            //set board to test move value
            boardArr[y1][x1] = boardArr[y][x];
            boardArr[y][x] = " ";

            //recursively test best move
            bestTempMove = std::min(bestTempMove, miniMax(depth-1, alpha, beta, ! isMaximisingPlayer));

            //undo board
            //undo_move2();

            undoMove(x, y, x1, y1, piece1, piece2);

            //alpha beta pruning
            beta = std::min(beta, bestTempMove);

            if(beta <= alpha){

                //std::cout << whiteMoves << std::endl;
                future_possible_moves.clear();
                return bestTempMove;
            }

        }

        //std::cout << whiteMoves << std::endl;
        future_possible_moves.clear();
        return bestTempMove;

    }


}

void Ai_Logic::undoMove(int x, int y, int x1, int y1 , std::string piece1, std::string piece2){ //
    boardArr[y][x] = piece1;
    boardArr[y1][x1] = piece2;
}

void Ai_Logic::undo_move1(){
    //for undoing all test moves
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            boardArr[i][j] = board1[i][j];
        }
    }
}

void Ai_Logic::undo_move2(){
    //for undoing only the test moves after the first
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            boardArr[i][j] = board2[i][j];
        }
    }
}

int Ai_Logic::calculateBestMove()
{

    //generate all possible moves for one turn
    moveGeneration *genMoves = new moveGeneration;
    //generate more readable moves
    genMoves->ugly_moves();
    std::vector<std::string> possible_moves = genMoves->neatMoves;

    // ai temp values for passing to testBoardValues for assessing a board position
    int aiX, aiY, aiX1, aiY1;

    //for moves to compete against
    float bestValue = -9999;



    //compare moves
    for(int i = 0; i < possible_moves.size(); i++){
        std::string tempMove = possible_moves[i];
        aiX = (int)tempMove[0]-'0';
        aiY = (int)tempMove[1]-'0';
        aiX1 = (int)tempMove[2]-'0';
        aiY1 = (int)tempMove[3]-'0';

        //change board,
        genMoves->testBoardValue(aiX, aiY, aiX1, aiY1);

        //test it's value and store it and test if white or black,
        float tempValue;
        if(turns%2 == 0){
            tempValue = evaluateBoard();
        }else {
            tempValue = -evaluateBoard();
        }

        //change board back
        genMoves->undo_move(aiX, aiY, aiX1, aiY1);

        //if move is better then the best one store it
        if(tempValue > bestValue){
            bestValue = tempValue;
            bestMove = tempMove;
            //best_moves.push_back(possible_moves[i]);

        }

    }
    //clearing vector for test remove later once one move can be generated TEST
    possible_moves.clear();

}

float Ai_Logic::evaluateBoard()
{
    //finding score of board
    float totalEvaluation = 0;

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
    if(piece == "P" || piece == "R" || piece == "N" || piece == "B" || piece == "Q" || piece == "K"){
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
        return 10 + pawnEvalBlack[y][x];
    } else if (piece =="r"){
        return 50 + rookEvalBlack[y][x];
    }else if (piece =="n"){
        return  30 + knightEval[y][x];
    }else if (piece =="b"){
        return 30 + bishopEvalBlack[y][x];
    }else if (piece =="q"){
        return 90 + evalQueen[y][x];
    }else if (piece =="k"){
        return 900 + kingEvalBlack[y][x];
    //white
    }else if(piece == "P"){
        return 10 + pawnEvalWhite[y][x];
    } else if (piece =="R"){
        return 50 + rookEvalWhite[y][x] ;
    }else if (piece =="N"){
        return  30 + knightEval[y][x];
    }else if (piece =="B"){
        return 30 + bishopEvalWhite[y][x];
    }else if (piece =="Q"){
        return 90 + evalQueen[y][x];
    }else if (piece =="K"){
        return 900 + kingEvalWhite[y][x];
    } else {
        return 0;
    }
}


