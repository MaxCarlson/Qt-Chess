#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <tile.h>
#include <externs.h>
#include <iostream>

//create an item array to to represent chess board tiles
Tile * rect[8][8];

// number of half turns
int turns = 0;

int count = 0;

int numberOfPieceMoved = 0;

int tempx, tempy, tempx2, tempy2;



//color piece arrays

std::string blackPieces[7] = {"p", "q", "k", "b", "n", "r", " "};
std::string whitePieces[7] = {"P", "Q", "K", "B", "N", "R", " "};


void chessBoard(QWidget *baseWidget, Tile *rect[8][8]){

    int boardX = 350, boardY = 125, k = 0;
    //seed Qt 64 tile chess board - colored empty tiles
    for(int i = 0; i < 8; i++){
        boardX = 350;
        for(int j = 0; j < 8; j++){
            //seed tile array with tile objects
            rect[i][j] = new Tile(baseWidget);
            rect[i][j]->tileColor=(i+j)%2;
            rect[i][j]->piece=0;
            rect[i][j]->row=i;
            rect[i][j]->col=j;
            rect[i][j]->tileNum=k++;
            rect[i][j]->tileDisplay();
            rect[i][j]->setGeometry(boardX,boardY,64,64);

            boardX += 64;
        }
        boardY += 64;
    }


    //Load all pieces into correct starting spots
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(boardArr[j][i] != " "){
                rect[j][i]->piece=1;
                for(int k = 0; k < 8; k++){
                    if(boardArr[j][i] == whitePieces[k]){
                        rect[j][i]->pieceColor=0;
                        rect[j][i]->display(whitePieces[k]);
                    } else if (boardArr[j][i] == blackPieces[k]){
                        rect[j][i]->pieceColor=1;
                        rect[j][i]->display(blackPieces[k]);
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //create widget + set  intial size
    QWidget *myWidget = new QWidget();
    myWidget->setGeometry(0,0,1370,700);

    //create board
    chessBoard(myWidget, rect);

    //show the board
    myWidget->show();

    return a.exec();
}
