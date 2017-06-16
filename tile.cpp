#include "tile.h"
#include <QDebug>
#include "Pieces.h"


Pieces *isValid = new Pieces();

extern Tile * rect[8][8];
extern QWidget *myWidget;

Tile *click1;


//Tile::Tile(QWidget *pParent, Qt::WindowFlags f){

//}

void Tile::mousePressEvent(QMouseEvent * event){
    qDebug() << "My Tile knows that you clicked on it!";
    moveChecking(this);
}

bool Tile::moveChecking(Tile *temp){
    
    int retValue, tempx, tempy, tempx2, tempy2;
    
    if(temp->piece && (temp->pieceColor==turns)){

        tempx = temp->row;
        tempy = temp->col;

        click1 = new Tile();
        tempx2 = click1->row;
        tempy2 = click1->col;


        isValid->coordinates(tempx, tempy, tempx2, tempy2);

        if(isValid->whichPiece() == true){
            click1 = temp;
        }
        
    }    
    
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
