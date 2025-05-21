#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    for(int i=0; i<NUM; i++){
        balls.append(new ball(width(), height()));
    }
    connect(&ticktimer, SIGNAL(timeout()), this, SLOT(Tick()));
    ticktimer.start(20);
    connect(&app, SIGNAL(timeout()), this, SLOT(Add()));
    app.start(3000);
    play = new player();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::Add(){
    qDebug()<<"adding";
    int rnd=rand()%4;
    if (rnd==0){

        balls.append(new ball(width(), height(), 50, 50));
    } else if (rnd==1){

        balls.append(new ball(width(), height(), 550, 50));
    } else if (rnd==2){

        balls.append(new ball(width(), height(), 550, 550));
    } else if (rnd==3){

        balls.append(new ball(width(), height(), 50, 550));
    }
    NUM++;
    qDebug()<<"adding is ok?";
}
void Widget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black));
    //painter.setBrush(play->color);
    //painter.drawRect(play->x, play->y, play->size, play->size);
    for (int i=0; i<NUM; i++){

        //painter.setBrush(QBrush(balls[i]->GetColor()));

        painter.drawImage(balls[i]->point.x(),
                          balls[i]->point.y(),
                          balls[i]->img);
    }
    painter.drawImage(play->x+50, play->y+50, play->img);
}
void Widget::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_A:
        play->x-=5;
        if (play->x<0) play->x+=5;
        play->point.setX(play->x);


        break;
    case Qt::Key_W:
        play->y-=5;
        if (play->y<0) play->y+=5;
        play->point.setY(play->y);

        break;
    case Qt::Key_S:
        play->y+=5;
        if (play->y>575) play->y-=5;
        play->point.setY(play->y);

        break;
    case Qt::Key_D:
        play->x+=5;
        if (play->x>575) play->x-=5;
        play->point.setY(play->x);

        break;
    case Qt::Key_Space:
        play->type++;
        if (play->type==4) play->type=1;
        play->img=QImage(":/res/"+QString::number(play->type)+"p.png").scaled(50, 50);
    }


}


void Widget::Tick(){
    int tmpi=-1;
    ball* tmp=nullptr;
    for(int i=0; i<NUM; i++){
        if (play->CheckColision(balls[i])){
            if (play->type!=balls[i]->type){
                if (play->type==2 && balls[i]->type==1){
                    tmpi=i;
                    tmp=balls[i];


                //1-ножницы, 2-камень, 3-бумага
                } else if (play->type==2 && balls[i]->type==3){
                    this->close();
                } else if (play->type==3 && balls[i]->type==1){
                    this->close();
                } else if (play->type==3 && balls[i]->type==2){
                    tmpi=i;
                    tmp=balls[i];
                } else if (play->type==1 && balls[i]->type==2){
                    this->close();
                } else if (play->type==1 && balls[i]->type==3){
                    tmpi=i;
                    tmp=balls[i];
                }
            } else {
                balls[i]->vx=-balls[i]->vx;
                balls[i]->vy=-balls[i]->vy;
            }
        }
        for(int j=0; j<NUM; j++){
            balls[i]->CheckColision(balls[j]);
        }
        balls[i]->move(width(), height());

    }
    if (tmpi!=-1){
        qDebug()<<"Deleting";
        balls.remove(tmpi);
        delete tmp;
        NUM--;
        qDebug()<<"IsItOk";
    }
    this->repaint();

}
