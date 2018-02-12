#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
class Player: public QObject, public QGraphicsPixmapItem
{
Q_OBJECT
public:
    Player();
    QPixmap run[8];
    int pixmapIndex;

public slots:
    void runPlayer();
};

#endif // PLAYER_H
