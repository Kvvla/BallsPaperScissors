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
    for (QList<ball*>::iterator it = balls.begin(); it != balls.end(); ++it) {
        painter.drawImage((*it)->point.x(),
                          (*it)->point.y(),
                          (*it)->img);
        //balls.Iterator++;
        //std::cout << " " << *it; // оператор * позволяет получить значение элемента, на которое указывает итератор
    }


        //painter.setBrush(QBrush(balls[i]->GetColor()));

        //balls.Iterator();


        //painter.drawImage((balls.Iterator*)->point.x(),
                          //(balls.Iterator*)->point.y(),
                          //(balls.Iterator*)->img);
        //balls.Iterator++;
    //}
    painter.drawImage(play->x, play->y, play->img);
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
    int i=0;
    for (QList<ball*>::iterator it = balls.begin(); it != balls.end(); ++it) {

        if (play->CheckColision(*it)){
            if (play->type != (*it) -> type){
                if (play->type==2 && (*it)->type==1){
                    tmpi=i;
                    tmp=(*it);


                //1-ножницы, 2-камень, 3-бумага
                } else if (play->type==2 && (*it)->type==3){
                    this->close();
                } else if (play->type==3 && (*it)->type==1){
                    this->close();
                } else if (play->type==3 && (*it)->type==2){
                    tmpi=i;
                    tmp=*it;
                } else if (play->type==1 &&(*it)->type==2){
                    this->close();
                } else if (play->type==1 && (*it)->type==3){
                    tmpi=i;
                    tmp=(*it);
                }
            } else {
                (*it)->vx=-(*it)->vx;
                (*it)->vy=-(*it)->vy;
            }
        }
        for(QList<ball*>::iterator ij = balls.begin(); ij != balls.end(); ++ij){
            (*it)->CheckColision(*ij);
        }
        (*it)->move(width(), height());
        i++;
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
