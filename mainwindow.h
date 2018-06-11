#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "sword.h"
#include "weapon.h"
#include <QKeyEvent>
#include<QDockWidget>
#include<QLCDNumber>
#include<QProgressBar>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QGraphicsPixmapItem *player;
    QTimer *timer;  ////for sword move

    QGraphicsPixmapItem *boss;
    QTimer *timer2;  //for weapon appear
    QTimer *timer3;  //for weapon move
    QTimer *timer5;  //for boss move
    int limit = 3;  //for 3 times limited-times skill

    QDockWidget *dock1;
    QDockWidget *dock2;
    QDockWidget *dock3;
    QLCDNumber *score;
    QProgressBar *bossHP;
    QProgressBar *playerHP;
    int SC1=0;
    int HP1=100;
    int HP2=100;

    QTimer *timer6;  //for check collide

Q_SIGNALS:
    void end();

private slots:
    void attack();  //for boss attack
    void bossmove();

    void checkHit();
};

//class boss : public QGraphicsPixmapItem{};
//class player : public QGraphicsPixmapItem{};

#endif // MAINWINDOW_H
