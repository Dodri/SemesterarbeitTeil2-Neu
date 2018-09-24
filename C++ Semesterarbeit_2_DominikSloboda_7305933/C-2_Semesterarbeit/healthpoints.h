#include <vector>
#include <QWidget>
#include <QTimer>
#include <QPainter>

using namespace std;



class healthpoints : public QWidget
{

public:
    healthpoints(QWidget *parent = 0);
    ~healthpoints();
    int points;
    void updatePoints();
    bool endgame;

private:

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QPaintEvent *);
};
