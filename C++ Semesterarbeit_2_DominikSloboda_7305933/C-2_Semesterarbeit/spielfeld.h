#include <vector>
#include <QWidget>
#include <QTimer>
#include <QPainter>

using namespace std;

class spielfeld : public QWidget
{
public:
    spielfeld(QWidget *parent = 0);
    ~spielfeld();

    struct Player *player;

    enum drawType { square, circle };

    void start(void) { timer->start(1); increment=1; }
    void stop(void) { timer->stop(); increment=0; }
    void goLeft(void);
    void goRight(void);
    void newObject(void);
    void moveObject(void);
    void safeObjectsInFile();
    void loadObjectsInFile();
    int points;
    bool hit;



private:
    QTimer *timer;
    QTimer *timerNewObject;
    int lastX;
    int lastY;
    int increment;
    int width;
    int height;

    int verschiebung = 0;
    vector<struct myCircle *> circles;

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent (QPaintEvent *);

};

struct Player {

    int x, y, size;

};


struct myCircle
{
    int x, y;
    int radius;
    int phase;
    int verschiebung_;
};
