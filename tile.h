#ifndef TILE_H
#define TILE_H


#include <QLabel>


class Tile : public QLabel
{
public:
    //Fields
    int tileColor, piece, pieceColor, row, col, tileNum;
    std::string pieceName;

    //constructor
    Tile(QWidget* pParent=0, Qt::WindowFlags f=0) : QLabel(pParent, f) {};


    //mouse clicks
    void mousePressEvent(QMouseEvent * event);

    //display pieces on correct tiles
    void display(std::string elem);

    //color tiles
    void tileDisplay();

};

#endif // TILE_H
