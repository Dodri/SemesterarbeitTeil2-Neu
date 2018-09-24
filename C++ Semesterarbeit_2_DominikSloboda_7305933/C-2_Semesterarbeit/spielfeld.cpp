#include <QtGui>
#include <QRect>
#include <QPainter>
#include <QSize>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QString>

#include "spielfeld.h"


using namespace std;


spielfeld::spielfeld(QWidget *parent)
    : QWidget(parent)
{
    setPalette(QPalette(QColor(255, 255, 255)));
    setAutoFillBackground(true);
    setMouseTracking(false);

    this->player= new Player;

    QSize size = this->size();
    this->width = size.width();
    this->height = size.height();
    player->x = this->width - 50;
    player->y = this->height - 50;
    player->size=50;
    points = 0;
    hit = false;

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    lastX=100;
    lastY=100;
    increment=0;

}

spielfeld::~spielfeld()
{
}

void spielfeld::resizeEvent(QPaintEvent *event){

    QSize size = this->size();
    this->width = size.width();
    this->height = size.height();
    player->x = ((int) this->width / 2 )- ((int)this->player->size / 2);
    player->y = this->height - 70;

    update();
}

void spielfeld::goLeft(){

    int x = this->player->x -5;

    if(x < 0){
        x = 0;
    }

    this->player->x = x;
    update();
}

void spielfeld::goRight(){

    int x = this->player->x +5;

    if((x + this->player->size) > width){
        x = width - this->player->size;
    }

    this->player->x = x;
    update();
}

void spielfeld::paintEvent(QPaintEvent * )
{
    QPainter painter;

    vector<struct myCircle *>::iterator pos,start;
    start = circles.begin();

    painter.begin( this );

    painter.setBrush(Qt::BDiagPattern);
    painter.drawRect(this->player->x, this->player->y, this->player->size, 50);
    painter.setBrush(Qt::NoBrush);

    for (pos=start; pos!= circles.end(); pos++)
    {
        if((*pos)->y > height) {
            circles.erase(pos);
            points=points+5;
        } else {
            int x = (*pos)->x;
            int y = (*pos)->y;
            int radius = (*pos)->radius;
            if(x > player->x && x <= (player->x + player->size) && (y > player->y && y <= (player->y + player->size))) {
                points = points - 50;
                hit = true;
                circles.erase(pos);
            }
        }
        painter.drawEllipse((*pos)->x,(*pos)->y,(*pos)->radius,(*pos)->radius);

    }
    cout << circles.size() << endl;
    painter.end();
}

void spielfeld::safeObjectsInFile() {
    vector<struct myCircle *>::iterator pos,start;
    start = circles.begin();

    ofstream file;
    file.open("safe.txt");
    file << "points" << " | " << points << endl;
    int playerX = player->x;
    int playerY = player->y;
    file << "player | " << playerX << " | " << playerY << endl;
    for (pos=start; pos!= circles.end(); pos++) {
        int objX = (*pos)->x;
        int objY = (*pos)->y;
        file << "object | " << objX << " | " << objY << endl;
    }
    file.close();
}

void spielfeld::loadObjectsInFile(){
    circles.clear();
    std::ifstream in("safe.txt", std::ifstream::in);

    if(!in) {
      cout << "Spielstand kann nicht geladen werden.";
      return;
    }

    char str[255];

    while(in) {
        in.getline(str, 255);
        stringstream ss(str);
        string toks[3];
        string sep = " | ";
        ss >> toks[0] >> sep >> toks[1] >> sep >> toks[2];

        if(toks[0] == "player"){
            player->x=stoi(toks[1]);
            player->y=stoi(toks[2]);
        }

        else if(toks[0]== "points"){

            points = stoi(toks[1]);

}
        else{
        struct myCircle *object;
                object=new myCircle;

                object->radius=5;
                if(toks[1] == "" || toks[2] == "") {
                    continue;
                }
                object->x = stoi(toks[1]);
                object->y = stoi(toks[2]);

                circles.push_back(object);
        }
}

    in.close();
    update();
}

void spielfeld::newObject()
{

    if(circles.size() > 10) {

        return;
    }

    int x =  0 + ( std::rand() % ( width - 0 + 1 ) );
    struct myCircle *object;
    object=new myCircle;

    object->radius=5;
    object->x = x;
    object->y = 0 - object->radius;

    circles.push_back(object);
    update();
}

void spielfeld::moveObject(void)
{

    vector<struct myCircle *>::iterator pos,start;
    start = circles.begin();

        for (pos=start; pos!= circles.end(); pos++){

            (*pos)->y=(*pos)->y + 5;
            update();
        }
}

