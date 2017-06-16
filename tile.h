#ifndef TILE_H
#define TILE_H


#include <QGraphicsRectItem>


class Tile : public QGraphicsRectItem
{
public:
    Tile();

    void mousePressEvent(QGraphicsSceneMouseEvent * event);
};

#endif // TILE_H
