#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QMessageBox>
#include <QPaintEvent>
#include <QPainter>
#include "player.h"
#include <QList>
#include "ball.h"
#include <QImage>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    //void on_play_button_clicked();
    //void AddSecond();
    void Tick();
    void Add();
    //void on_exit_button_clicked();

private:
    Ui::Widget *ui;
    int NUM=5;
    QTimer app;
    QList<ball*> balls;
    QTimer ticktimer;
    player* play;
protected:
    void paintEvent(QPaintEvent * event);
    void keyPressEvent(QKeyEvent *event);

};
#endif // WIDGET_H
