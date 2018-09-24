#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QEvent>
#include <QKeyEvent>
#include<iostream>
#include <fstream>
#include <QString>
#include <QtGui>

#include "Widget.h"

using namespace std;


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->isStarted = true;

    QPushButton *loadButton = new QPushButton(tr("Load"));
    loadButton->setFocusPolicy(Qt::NoFocus);
    connect(loadButton, SIGNAL(clicked()), this, SLOT(load()));

    QPushButton *safeButton = new QPushButton(tr("Safe"));
    safeButton->setFocusPolicy(Qt::NoFocus);
    connect(safeButton, SIGNAL(clicked()), this, SLOT(safe()));

    this->StartLabel = new QLabel(this);
    StartLabel->setText("Start");

    meinSpielfeld = new spielfeld;
    healthPoints = new healthpoints;

    Points = new QLabel(this);

    QGridLayout *gridLayout = new QGridLayout;

    gridLayout->addWidget(healthPoints, 0, 1);
    gridLayout->addWidget(Points, 0, 2);
    gridLayout->addWidget(safeButton, 0, 3);
    gridLayout->addWidget(loadButton, 0, 4);
    gridLayout->addWidget(StartLabel, 0, 5);
    gridLayout->addWidget(meinSpielfeld, 1, 1, 4, 5);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);

    newObjectTimer= new QTimer(this);
    connect(newObjectTimer, SIGNAL(timeout()), this, SLOT(object()));
        newObjectTimer->start(500);

    objectMovementTimer= new QTimer(this);
    connect(objectMovementTimer, SIGNAL(timeout()), this, SLOT(movement()));
    objectMovementTimer->start(25);

}


void Widget::resizeEvent(QPaintEvent *event){

}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){

    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        this->toggleStart();
    }

    if(event->key() == Qt::Key_Left) {
        if(isStarted){
            this->meinSpielfeld->goLeft();
        }
    }
    if(event->key() == Qt::Key_Right)
    {
        if(isStarted){
            this->meinSpielfeld->goRight();

        }
    }
}


void Widget::toggleStart(void) {
    this->isStarted = !this->isStarted;
    if(this->isStarted) {
        this->StartLabel->setText("Start");
        this->newObjectTimer->start(100);
        this->objectMovementTimer->start(25);
    } else {
        this->StartLabel->setText("Pause");
        this->newObjectTimer->stop();
        this->objectMovementTimer->stop();
    }
}

void Widget::start(void)
{
    meinSpielfeld->start();
}

void Widget::stop(void)
{
    meinSpielfeld->stop();
}

void Widget::object(void){

    meinSpielfeld->newObject();
 }

void Widget::movement(void){
if(healthPoints->endgame) {
    qApp->quit();
}
if(meinSpielfeld->hit){
    healthPoints->updatePoints();

    meinSpielfeld->hit=false;
}

    meinSpielfeld->moveObject();
    points();
}

void Widget::points(){
    Points->setText(QString::number(meinSpielfeld->points));
}

void Widget::safe(){
    if(isStarted) {
        toggleStart();
    }
    meinSpielfeld->safeObjectsInFile();
}

void Widget::load(){

   if(isStarted) {
       toggleStart();
   }
   meinSpielfeld->loadObjectsInFile();
   this->points();
}
