#include "tile.h"
#include <QDebug>

extern Tile * rect[8][8];

Tile::Tile(){

}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << "My Tile knows that you clicked on it!";
}

void Tile::display(std::string elem){



}
