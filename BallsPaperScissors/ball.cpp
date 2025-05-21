#include "ball.h"
#include <QDebug>
ball::ball(int w, int h): img(dummy) {

    size = 50;

    color = QColor::fromRgb(rand()%256, rand()%256, rand()%256);
    x=rand()%(w-2*size)+size;
    y=rand()%(h-2*size)+size;
    point=QPoint::QPoint(x, y);
    vx = 1 + rand()%3;
    vy = 1 + rand()%3;
    if (rand()%2==0) vx *= -1;
    if (rand()%2==0) vy *= -1;

    type=rand()%3+1;
    img=QImage::QImage(":/res/"+QString::number(type)+".png").scaled(size, size);
}


ball::ball(int w, int h, int x, int y): img(dummy){
    size = 50;

    color = QColor::fromRgb(rand()%256, rand()%256, rand()%256);
    this->x=x;
    this->y=y;
    point=QPoint::QPoint(x, y);
    vx = 1 + rand()%3;
    vy = 1 + rand()%3;
    if (rand()%2==0) vx *= -1;
    if (rand()%2==0) vy *= -1;
    type=rand()%3+1;
    img=QImage::QImage(":/res/"+QString::number(type)+".png").scaled(size, size);
}

void ball::move(int w, int h) {
    x+=vx;
    y+=vy;

    if (x<0 || x>(w-size)){
        vx=-vx;
        x+=vx;
    }
    if (y<0 || y>(h-size)){
        vy=-vy;
        y+=vy;
    }

    point.setX(x);
    point.setY(y);
}

void ball::CheckColision(ball *other){
    //1-ножницы, 2-камень, 3-бумага
    if (this==other) return;
    if ((other->point.x()-(point.x()))*(other->point.x()-(point.x()))
            +((other->point.y())-point.y())*((other->point.y())-point.y())
            <3000){


        vx=-vx;
        vy=-vy;
        other->vx=-other->vx;
        other->vy=-other->vy;
        if (type!=other->type){
            if (type==2 && other->type==1){
                other->type=2;
                other->img=img;
            } else if(type==2 && other->type==3){
                type=3;
                img=other->img;
            } else if(type==3 && other->type==1){
                type=1;
                img=other->img;
            } else if (type==3 && other->type==2){
                other->type=3;
                other->img=img;
            } else if (type==1 && other->type==2){
                type=2;
                img=other->img;
            } else if (type==1 && other->type==3){
                other->type=1;
                other->img=img;
            }
        }
    }
}


