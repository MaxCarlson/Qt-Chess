#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <tile.h>
#include <externs.h>
#include <iostream>

//create an item array to to represent chess board tiles
Tile * rect[8][8];

//array of chess board
std::string boardArr [8][8]= {
    {"r", "n", "b", "q", "k", "b", "n", "r"},
    {"p", "p", "p", "p", "p", "p", "p", "p",},
    {" ", " ", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", " ", " "},
    {"P", "P", "P", "P", "P", "P", "P", "P"},
    {"R", "N", "B", "Q", "K", "B", "N", "R"},
              };

void chessBoard(QGraphicsScene *scene){

    int boardX = -400, boardY = -400;
    //seed Qt 64 tile chess board - blank tiles
    for(int i = 0; i < 8; i++){
        boardX = -400;
        for(int j = 0; j < 8; j++){
            //seed array with rect items
            rect[i][j] = new Tile();
            rect[i][j]->setRect(boardX,boardY,100,100);

            //add items to the scene
            scene->addItem(rect[i][j]);

            //make rect (tile) focusable
            rect[i][j]->setFlag(QGraphicsItem::ItemIsFocusable);

            boardX += 100;
        }
        boardY += 100;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //create a scene
    QGraphicsScene * scene = new QGraphicsScene();

    //create board
    chessBoard(scene);

    //add a view
    QGraphicsView * view = new QGraphicsView(scene);

    // make visiable
    view->show();

    return a.exec();
}
