#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //create a scene
    QGraphicsScene * scene = new QGraphicsScene();


    int boardX = -400, boardY = -400;

    //create an item array to put into the scene
    QGraphicsRectItem * rect[8][8];

    //create qt chess board
    for(int i = 0; i < 8; i++){
        boardX = -400;
        for(int j = 0; j < 8; j++){
            //seed array with rect items
            rect[i][j] = new QGraphicsRectItem();
            rect[i][j]->setRect(boardX,boardY,100,100);

            //add items to the scene
            scene->addItem(rect[i][j]);
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
