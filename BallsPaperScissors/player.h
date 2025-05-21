#ifndef PLAYER_H
#define PLAYER_H
#include <QPoint>
#include <QColor>
#include <QImage>
#include "ball.h"
class player
{
public:
    player();
    int x;
    int y;
    int size;
    QImage img;
    int type;
    QPoint point;
    bool CheckColision(ball* other);
};

#endif // PLAYER_H
