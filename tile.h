#ifndef TILE_H
#define TILE_H


#include <QGraphicsRectItem>


class Tile : public QGraphicsRectItem
{
public:
    //Fields
    int tileColor, piece, pieceColor, row, col, tileNum;
    std::string pieceName;

    //constructor
    Tile();

    //mouse clicks
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

    //display pieces on correct tiles
    void display(std::string elem);

};

#endif // TILE_H
