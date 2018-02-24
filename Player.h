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
    void keyPressEvent(QKeyEvent* event);

    // member variables
    int playerIndex;
    QPixmap run[8];
    int pixmapIndex;
    bool isFlipped;
    QGraphicsPolygonItem* topArea;
    QGraphicsPolygonItem* bottomArea;
    QGraphicsPolygonItem* rightArea;

public slots:

    void runPlayer();
};

#endif // PLAYER_H
