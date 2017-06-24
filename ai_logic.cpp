#include "ai_logic.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "evaluate.h"


//best overall move as calced
std::string bestMove;

//holds board state before any moves or trys
std::string board1[8][8];
//holds state of initial board + 1 move
std::string board2[8][8];


Evaluate *eval = new Evaluate;



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
    int numberOfMoves = possible_moves.size();

    //sorting not neccasary on first step?????
    //possible_moves = sortMoves(possible_moves, true);


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
        float tempValue = miniMax(depth -1, -100000, 100000, ! isMaximisingPlayer, numberOfMoves);

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
    positionCount = 0;
    return bestMoveFound;

}

float Ai_Logic::miniMax(float depth, float alpha, float beta, bool isMaximisingPlayer, int numberOfMoves)
{
    positionCount ++;
    int whiteMoves = 0;
    if(depth <= 0){
        return - eval->evaluateBoard(depth, numberOfMoves);
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
    //sort the best six moves into the first six slots of possible moves, improvmes speed by about 30% avg
    future_possible_moves = sortMoves(future_possible_moves, isMaximisingPlayer);

    numberOfMoves = future_possible_moves.size();

    int x, y, x1, y1;

    if(isMaximisingPlayer == true){
        float bestTempMove = -99999;
        for(int i = 0; i < future_possible_moves.size(); i++){
            //change board accoriding to i possible move
            std::string tempMove = future_possible_moves[i];
            x = (int)tempMove[0]-'0';
            y = (int)tempMove[1]-'0';
            x1 = (int)tempMove[2]-'0';
            y1 = (int)tempMove[3]-'0';

            //piece recovery for undo function
            std::string piece1 = boardArr[y][x], piece2 = boardArr[y1][x1];

            //set board to test move value and move piece
            boardArr[y1][x1] = boardArr[y][x];
            boardArr[y][x] = " ";

            //recursively test best move
            bestTempMove = std::max(bestTempMove, miniMax(depth-1, alpha, beta,  ! isMaximisingPlayer, numberOfMoves));

            //undo move by passing it coordinates and pieces moved
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

        float bestTempMove = 99999;
        for(int i = 0; i < future_possible_moves.size(); i++){
            whiteMoves ++;

            //change board accoriding to i possible move
            std::string tempMove = future_possible_moves[i];
            x = (int)tempMove[0]-'0';
            y = (int)tempMove[1]-'0';
            x1 = (int)tempMove[2]-'0';
            y1 = (int)tempMove[3]-'0';

            //piece recovery for undo function
            std::string piece1 = boardArr[y][x], piece2 = boardArr[y1][x1];

            //set board to test move value and move piece
            boardArr[y1][x1] = boardArr[y][x];
            boardArr[y][x] = " ";

            //recursively test best move
            bestTempMove = std::min(bestTempMove, miniMax(depth-1, alpha, beta, ! isMaximisingPlayer, numberOfMoves));

            //undo move by passing it coordinates and pieces moved
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

std::vector<std::string> Ai_Logic::sortMoves(std::vector<std::string> moves, bool isMaximisingPlayer)
{
    //float vector to hold scores
    std::vector<float> score;
    int x, y, x1, y1;

    for(int i = 0; i < moves.size(); i++){
        //change board accoriding to i possible move
        std::string tempMove = moves[i];
        x = (int)tempMove[0]-'0';
        y = (int)tempMove[1]-'0';
        x1 = (int)tempMove[2]-'0';
        y1 = (int)tempMove[3]-'0';

        //piece recovery for undo function
        std::string piece1 = boardArr[y][x], piece2 = boardArr[y1][x1];

        //set board to test move value and move piece
        boardArr[y1][x1] = boardArr[y][x];
        boardArr[y][x] = " ";

        //evaluate board and push it to the float vector
        score.push_back(eval->evaluateBoard(1, 0));

        //undo the move
        undoMove(x, y, x1, y1, piece1, piece2);

    }
    std::vector<std::string> newListA, newListB=moves, returnVec;
    int tmp = moves.size();

    //first few moves only
    for(int i = 0; i <std::min(6, tmp); i++){
        float max;
        int maxLocation=0;
        //set high low score based on what's good for player being analysed
        if(isMaximisingPlayer == false){
            max = -100000;
        } else{
            max = 100000;
        }
        for(int j = 0; j < moves.size(); j++){
            //if score is better than max record it's location and remove it from being searched
            if(score[j] > max && isMaximisingPlayer == false){
                max = score[j];
                maxLocation = j;
                score[j] = -100000;
            } else if (score[j] < max && isMaximisingPlayer == true){
                max = score[j];
                maxLocation = j;
                score[j] = 100000;
            }
        }
        newListA.push_back(moves[maxLocation]);
        newListB.erase(newListB.begin()+maxLocation);
    }
    newListA.insert(newListA.end(), newListB.begin(), newListB.end());

    return newListA;

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





