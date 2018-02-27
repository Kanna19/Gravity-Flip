#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QPolygonF>
#include <QGraphicsItem>

class Player: public QObject, public QGraphicsPixmapItem
{
Q_OBJECT

public:

    // member functions

    Player(int index, QGraphicsItem* parent = 0);
    void flipPlayer();

    // member variables

    int playerIndex;
    QPixmap run[8];
    int pixmapIndex;
    bool isFlipped;
    bool isInAir;
    QGraphicsPolygonItem* topArea;
    QGraphicsPolygonItem* bottomArea;
    QGraphicsPolygonItem* rightArea;

public slots:

    void runPlayer();

signals:
    void makeSound();
};

#endif // PLAYER_H
