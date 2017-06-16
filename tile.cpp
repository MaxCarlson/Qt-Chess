#include "tile.h"
#include <QDebug>

extern Tile * rect[8][8];
extern QWidget *myWidget;

//Tile::Tile(QWidget *pParent, Qt::WindowFlags f){

//}

void Tile::mousePressEvent(QMouseEvent * event){
    qDebug() << "My Tile knows that you clicked on it!";
}

void Tile::display(std::string elem){

    this->pieceName=elem;

    if(elem == "P"){
        this->setPixmap(QPixmap(":/Images/pawn_white.svg"));
    } else if(elem == "R"){
        this->setPixmap(QPixmap(":/Images/rook_white.svg"));
    } else if(elem == "N"){
        this->setPixmap(QPixmap(":/Images/knight_white.svg"));
    } else if (elem == "B"){
        this->setPixmap(QPixmap(":/Images/bishop_white.svg"));
    }else if (elem == "K"){
        this->setPixmap(QPixmap(":/Images/king_white.svg"));
    } else if(elem == "Q"){
        this->setPixmap(QPixmap(":/Images/bishop_white.svg"));
    }

    //black pieces
    if (elem == "p"){
        this->setPixmap(QPixmap(":/Images/pawn_black.svg"));
    } else if(elem == "r"){
        this->setPixmap(QPixmap(":/Images/rook_black.svg"));
    } else if(elem == "n"){
        this->setPixmap(QPixmap(":/Images/knight_black.svg"));
    } else if (elem == "b"){
        this->setPixmap(QPixmap(":/Images/bishop_black.svg"));
    }else if (elem == "k"){
        this->setPixmap(QPixmap(":/Images/king_black.svg"));
    } else if(elem == "q"){
        this->setPixmap(QPixmap(":/Images/bishop_black.svg"));
    }


}

void Tile::tileDisplay()
{

    if(this->tileColor)
        this->setStyleSheet("QLabel {background-color: rgb(120, 120, 90);}:hover{background-color: rgb(170,85,127);}");
    else
        this->setStyleSheet("QLabel {background-color: rgb(211, 211, 158);}:hover{background-color: rgb(170,95,127);}");
}
