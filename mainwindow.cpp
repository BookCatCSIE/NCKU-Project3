#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTimer>

#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0, 0, 1200, 830)),
    timer(new QTimer),
    timer2(new QTimer),
    timer3(new QTimer),
    timer5(new QTimer),
    timer6(new QTimer)
{
    ui->setupUi(this);
    setWindowTitle("Funny Shooting Game!");
    setStyleSheet("background-color:gray");
    setMinimumSize(1800,850);
    setCentralWidget(ui->graphicsView);

    ui->graphicsView->setScene(scene);
    player = new QGraphicsPixmapItem(QPixmap(":/res/kirito1.png").scaled(120,160));
    scene->addItem(player);
    player->setPos(300, 625);
    timer->start(12);

    boss = new QGraphicsPixmapItem(QPixmap(":/res/boss1.png").scaled(240,240));
    scene->addItem(boss);
    boss->setPos(450, 0);
    timer2->start(1000);
    connect(timer2, SIGNAL(timeout()), this, SLOT(attack()));
    timer5->start(3000);
    connect(timer5, SIGNAL(timeout()), this, SLOT(bossmove()));

    score = new QLCDNumber(this);
    bossHP = new QProgressBar(this);
    playerHP = new QProgressBar(this);

    score -> display(SC1);
    bossHP -> setRange(0,100);
    bossHP -> setValue(HP1);
    playerHP -> setRange(0,100);
    playerHP -> setValue(HP2);

    dock1 = new QDockWidget(tr("Score"),this);
    dock1 -> setFeatures(QDockWidget::NoDockWidgetFeatures);
    //dock widget cannot float move or close
    dock1 -> setMinimumWidth(250);
    dock1 -> setMaximumWidth(250);
    dock1 -> setMinimumHeight(350);
    dock1 -> setMaximumHeight(350);
    dock1 -> setAllowedAreas(Qt::RightDockWidgetArea);
    dock1 -> setWidget(score);
    addDockWidget(Qt::RightDockWidgetArea,dock1);

    dock2 = new QDockWidget(tr("HP of Boss"),this);
    dock2 -> setFeatures(QDockWidget::NoDockWidgetFeatures);
    dock2 -> setMinimumWidth(250);
    dock2 -> setMaximumWidth(250);
    dock2 -> setMinimumHeight(200);
    dock2 -> setAllowedAreas(Qt::RightDockWidgetArea);
    dock2 -> setWidget(bossHP);
    addDockWidget(Qt::RightDockWidgetArea,dock2);

    dock3 = new QDockWidget(tr("HP of player"),this);
    dock3 -> setFeatures(QDockWidget::NoDockWidgetFeatures);
    dock3 -> setMinimumWidth(250);
    dock3 -> setMaximumWidth(250);
    dock3 -> setMinimumHeight(200);
    dock3 -> setAllowedAreas(Qt::RightDockWidgetArea);
    dock3 -> setWidget(playerHP);
    addDockWidget(Qt::RightDockWidgetArea,dock3);

    timer6->start(100);
    connect(timer6, SIGNAL(timeout()), this, SLOT(checkHit()));

    connect(this,SIGNAL(end()),this,SLOT(close()));
    //for end to close window
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        //player->setPos(player->x(), player->y() - 10);
        if(player->y()<=300){player->setPos(player->x(), player->y());}
        else{player->setPos(player->x(), player->y() - 10);}
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        //player->setPos(player->x(), player->y() + 10);
        if(player->y()>=650){player->setPos(player->x(), player->y());}
        else{player->setPos(player->x(), player->y() + 10);}
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        //player->setPos(player->x() - 10, player->y());
        if(player->x()<=-160){player->setPos(player->x(), player->y());}
        else{player->setPos(player->x() - 10, player->y());}
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        //player->setPos(player->x() + 10, player->y());
        if(player->x()>=1200){player->setPos(player->x(), player->y());}
        else{player->setPos(player->x() + 10, player->y());}
        break;
    case Qt::Key_P:  //for limited-times skill (3 times)
        //qDebug()<<limit;
        --limit;
        if(limit>=0){
            sword *g = new sword;
            g->setPixmap(QPixmap(":/res/golden_sword.png").scaled(220, 220));
            g->setPos(player->x() + player->pixmap().width() / 2 - g->pixmap().width() / 2, player->y() - g->pixmap().height());
            g->connect(timer, SIGNAL(timeout()), g, SLOT(golden_fly()));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(g));

            sword *h = new sword;
            h->setPixmap(QPixmap(":/res/golden_sword.png").scaled(200, 200));
            h->setPos(player->x() + player->pixmap().width() / 2 - h->pixmap().width() / 2, player->y() - h->pixmap().height());
            h->connect(timer, SIGNAL(timeout()), h, SLOT(golden_R_fly()));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(h));

            sword *f = new sword;
            f->setPixmap(QPixmap(":/res/golden_sword.png").scaled(200, 200));
            f->setPos(player->x() + player->pixmap().width() / 2 - f->pixmap().width() / 2, player->y() - f->pixmap().height());
            f->connect(timer, SIGNAL(timeout()), f, SLOT(golden_L_fly()));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(f));

        }
        break;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    //e->GraphicsSceneMousePress;
    sword *b = new sword;

    if(qrand() % 5 == 0 || qrand() % 5 == 2) {
        b->setPixmap(QPixmap(":/res/black_sword.png").scaled(40, 160));
    }
    else if(qrand() % 5 == 1 || qrand() % 5 == 3){
        b->setPixmap(QPixmap(":/res/green_sword.png").scaled(40, 160));
    }else{
        b->setPixmap(QPixmap(":/res/two_sword.png").scaled(120, 120));
    }
    b->setPos(player->x() + player->pixmap().width() / 2 - b->pixmap().width() / 2, player->y() - b->pixmap().height());
    b->connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(b));

    //below is what I had tried but failed
    //if(boss->collidesWithItem(b))
    //if(boss->collidesWithPath(b->shape()))
    //if(boss -> contains(QPointF(b->x(),b->y())))
    //if(boss->x() < b->x() && b->x() < boss->x()+boss->pixmap().width())
    //if(b->y() < boss->y()+boss->pixmap().height())
}

void MainWindow::attack(){
    weapon *b= new weapon;
    if(qrand() % 2 == 0) {
        b->setPixmap(QPixmap(":/res/weapon1.png").scaled(40, 168));
    }
    else {
        b->setPixmap(QPixmap(":/res/weapon2.png").scaled(40, 168));
    }
    b->setPos(boss->x() + boss->pixmap().width() / 2 - b->pixmap().width() / 2, boss->y() + b->pixmap().height()+100);

    b->connect(timer3, SIGNAL(timeout()), b, SLOT(bossATK()));
    timer3->start(8);
    scene->addItem(static_cast<QGraphicsPixmapItem*>(b));

    weapon *a = new weapon;
    if(qrand() % 2 == 0) {
        a->setPixmap(QPixmap(":/res/weapon1.png").scaled(40, 168));
    }
    else {
        a->setPixmap(QPixmap(":/res/weapon2.png").scaled(40, 168));
    }
    a->setPos(boss->x() + boss->pixmap().width() / 2 - a->pixmap().width() / 2 +10, boss->y() + a->pixmap().height()+100);

    a->connect(timer3, SIGNAL(timeout()), a, SLOT(bossLeftATK()));
    timer3->start(8);
    scene->addItem(static_cast<QGraphicsPixmapItem*>(a));

    weapon *c = new weapon;
    if(qrand() % 2 == 0) {
        c->setPixmap(QPixmap(":/res/weapon1.png").scaled(40, 168));
    }
    else {
        c->setPixmap(QPixmap(":/res/weapon2.png").scaled(40, 168));
    }
    c->setPos(boss->x() + boss->pixmap().width() / 2 - c->pixmap().width() / 2 -10, boss->y() + c->pixmap().height()+100);

    c->connect(timer3, SIGNAL(timeout()), c, SLOT(bossRightATK()));
    timer3->start(8);
    scene->addItem(static_cast<QGraphicsPixmapItem*>(c));
}

void MainWindow::bossmove(){
    if(qrand() % 6 == 0){
        boss->setPos(0, 0);
    }else if(qrand() % 6 == 1){
        boss->setPos(200, 0);
    }else if(qrand() % 6 == 2){
        boss->setPos(400, 0);
    }else if(qrand() % 6 == 3){
        boss->setPos(600, 0);
    }else if(qrand() % 6 == 4){
        boss->setPos(800, 0);
    }
    else{
        boss->setPos(x(), y());
    }
}

void MainWindow::checkHit(){
    QList<QGraphicsItem*>list = scene->collidingItems(boss);
    foreach(QGraphicsItem* item, list){
        SC1=SC1+10;
        HP1=HP1-3;
        if(HP1==1){HP1=0;}
        score -> display(SC1);
        bossHP -> setValue(HP1);
        scene ->removeItem(item);
        delete(item);
        if(HP1==0 && (QMessageBox::information(this,
           "Congratulation","You Win"))==QMessageBox::Ok){
            emit end();
        }
    }

    QList<QGraphicsItem*>list2 = scene->collidingItems(player);
    foreach(QGraphicsItem* item2, list2){
        SC1=SC1-5;
        HP2=HP2-1;
        if(HP2<0){HP2=0;}
        score -> display(SC1);
        playerHP -> setValue(HP2);
        scene ->removeItem(item2);
        delete(item2);
        if(HP2==0 && (QMessageBox::information(this,
           "Failed","You Lose"))==QMessageBox::Ok){
            emit end();}
    }
}
