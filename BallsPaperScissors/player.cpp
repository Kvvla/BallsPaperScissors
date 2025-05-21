#include "player.h"

player::player() {
    size = 50;

    x=300;
    y=300;
    point=QPoint::QPoint(x, y);

    type=1+rand()%3;
    img=QImage(":/res/"+QString::number(type)+"p.png").scaled(50, 50);

}
bool player::CheckColision(ball *other){
    //Если коснулся сверху
    int x2=other->x;
    int y2=other->y;
    int r=other->size;



    if (y-y2<r && y2<y && x2>x && x2<x+size){
        return true;
        //слева

    } else if ( x-x2<r && x2<x && y2>y && y2<y+size){
        return true;
        //снизу
    } else if (x2>x && x2<x+size && y2-(y+size)<r && y2>y+size){
        return true;

    } else if (y2>y && y2<y+size && x2-(x+size)<r && x2>x+size){
        return true;
    }

    else return false;
}
