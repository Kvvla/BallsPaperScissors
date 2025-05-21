#ifndef BALL_H
#define BALL_H
#include <QColor>
#include <QPoint>
#include <QImage>
class ball {
public:
    ball(int w, int h);
    ball(int w, int h, int x, int y);
    void move(int w, int h);

    void CheckColision(ball* other);
    QPoint point;
    int vx;
    int vy;
    int x;
    int y;
    int type;
    QImage dummy;
    QImage& img;
    QColor color;
    int size;

private:

};

#endif // BALL_H
