#include <QtGui>
#include <QRect>
#include <QPainter>
#include <QSize>

#include "healthpoints.h"

#include <iostream>

using namespace std;


healthpoints::healthpoints(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(false);
    points = 3;
    endgame = false;
}

healthpoints::~healthpoints()
{
}


void healthpoints::paintEvent(QPaintEvent * )
{
    QPainter painter;

    painter.begin( this );

    for(int i = 0; i < points; i++) {

    painter.setBrush(Qt::red);
    painter.drawEllipse(i*20, 0, 15, 15);
    painter.setBrush(Qt::NoBrush);
}
    painter.end();
}


void healthpoints::updatePoints(void)
{
    if(points >= 1){
    points = points - 1;

    update();
}
    else {
        endgame = true;
    }
}

void healthpoints::resizeEvent(QPaintEvent *event){

}


