#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <tile.h>

//create an item array to to represent chess board tiles
Tile * rect[8][8];

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //create a scene
    QGraphicsScene * scene = new QGraphicsScene();


    int boardX = -400, boardY = -400;



    //create qt chess board
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


    //add a view
    QGraphicsView * view = new QGraphicsView(scene);

    // make visiable
    view->show();

    return a.exec();
}
