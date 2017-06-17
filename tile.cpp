#include "tile.h"
#include <QDebug>
#include "Pieces.h"
#include "externs.h"


Pieces *isValid = new Pieces();

extern Tile * rect[8][8];
extern QWidget *myWidget;



Tile *click1;

// NOTE!!!!!
//Castling doesn't move the rook on the GUI only on the array of the board

void Tile::mousePressEvent(QMouseEvent * event){
    //qDebug() << "My Tile knows that you clicked on it!";
    moveChecking(this, ++count);

    //debugging stuff
    for(int i = 0; i < 8; i++){
        for(int j =0; j < 8; j++){
            std::cout << boardArr[i][j] << " " ;
        }
        std::cout << std::endl;
    }
}

bool Tile::moveChecking(Tile *temp, int countC){
    
    
    if(countC==1){
        if(temp->piece && (temp->pieceColor==turns%2)){


            if(temp->pieceName != " "){
                tempx = temp->col;
                tempy = temp->row;
                click1 = new Tile();

                temp->setStyleSheet("QLabel {background-color: green;}");

                click1=temp;
            } else {
                count = 0;
            }
        } else {
            count = 0;
        }

    } else {

        if(temp->tileNum==click1->tileNum){
            click1->tileDisplay();
            count = 0;

        } else {
            //ready coordinates to give to Pieces
            tempx = click1->col;
            tempy = click1->row;
            tempx2 = temp->col;
            tempy2 = temp->row;
            //give coordinates of origin and possible landing
            isValid->coordinates(tempx, tempy, tempx2, tempy2);

            //check if input coordinates are a valid move for piece and player
            if(isValid->whichPiece() == true){
                //replace moved piece with a space and move piece
                //std::string tempPiece = boardArr[tempy2][tempx2];
                //boardArr[tempy2][tempx2] = tempPiece;
                //boardArr[tempy][tempx] = " ";

                //switch Qwidget values on origin and spot piece landed
                click1->piece=0;
                temp->piece=1;

                //give moved piece same attributes
                temp->pieceColor=click1->pieceColor;
                temp->pieceName=click1->pieceName;


                click1->display(click1->pieceName);
                temp->display(click1->pieceName);

                click1->tileDisplay();
                temp->tileDisplay();



                turns++;
                count = 0;

                if(aiOn == 1){
                    aiTurn();
                }


            } else {

                count = 1;
            }

        }

    }
    
}

void Tile::aiTurn(){
    moveGeneration *newMove = new moveGeneration;

}


void Tile::display(std::string elem){

    this->pieceName=elem;

    //white pieces
    if(this->pieceColor == 0 && this->piece == 1){
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
            this->setPixmap(QPixmap(":/Images/queen_white.svg"));
        }
     //black pieces
    } else if (this->piece == 1){
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
            this->setPixmap(QPixmap(":/Images/queen_black.svg"));
        }
    }else {
        this->clear();
    }
}

void Tile::tileDisplay()
{

    if(this->tileColor)
        this->setStyleSheet("QLabel {background-color: rgb(120, 120, 90);}:hover{background-color: rgb(170,85,127);}");
    else
        this->setStyleSheet("QLabel {background-color: rgb(211, 211, 158);}:hover{background-color: rgb(170,95,127);}");
}

