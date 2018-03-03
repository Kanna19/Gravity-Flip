#ifndef PLAYER_H
#define PLAYER_H

class PlayerState;

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QPolygonF>
#include <QGraphicsItem>
#include "PlayerState.h"
#include <QMediaPlayer>

class Player: public QObject, public QGraphicsPixmapItem
{
Q_OBJECT

public:

    // member functions

    Player();
    Player(const Player &player);
    Player(int index, QGraphicsItem* parent = 0);
    void flipPlayer();
    bool isNotColliding(QGraphicsPolygonItem* area);
    bool isCaught();
    void killPlayer();

    // member variables

    int playerIndex;
    QPixmap run[8];

    int pixmapIndex;
    bool isFlipped;
    bool isInAir;

    QGraphicsPolygonItem* topArea;
    QGraphicsPolygonItem* bottomArea;
    QGraphicsPolygonItem* rightArea;

    QMediaPlayer* stepSoundPlayer;

public slots:

    void runPlayer();
    void doneProcessing(PlayerState state);
    void doneFlipping(PlayerState state);

signals:

    void requestUpdatePlayerState(Player* player, bool isNotCollidingWithTop,
                                  bool isNotCollidingWithBottom, bool isNotCollidingWithRight);
};

#endif // PLAYER_H
