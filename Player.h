#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
class Player: public QObject, public QGraphicsPixmapItem
{
Q_OBJECT
public:
    //functions
    Player();
    void flipPlayer();
    void keyPressEvent(QKeyEvent* event);

    //variables
    QPixmap run[8];
    int pixmapIndex;
    bool isFlipped;

public slots:
    void runPlayer();
};

#endif // PLAYER_H
