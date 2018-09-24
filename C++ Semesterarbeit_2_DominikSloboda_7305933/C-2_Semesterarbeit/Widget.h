#include <QWidget>
#include <QLabel>

#include "spielfeld.h"
#include "healthpoints.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);


private:
    spielfeld *meinSpielfeld;
    healthpoints *healthPoints;
    QLabel *StartLabel;
    QLabel *Points;
    bool isStarted;
    QTimer *newObjectTimer;
    QTimer *objectMovementTimer;
    void points();


    void toggleStart();

private slots:
    void start(void);
    void stop(void);
    void object(void);
    void movement(void);
    void safe(void);
    void load(void);

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void resizeEvent (QPaintEvent *);


};
