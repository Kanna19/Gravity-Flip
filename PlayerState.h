#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

class Player;

#include "Player.h"

class PlayerState
{

public:

    PlayerState(const Player* player, bool topCollision, bool bottomCollision, bool rightCollision);

    qreal xPos;
    qreal yPos;

    int pixmapIndex;

    bool isInAir;
    bool isFlipped;
    QImage displayImage;

    bool isNotCollidingWithTop;
    bool isNotCollidingWithBottom;
    bool isNotCollidingWithRight;
};

#endif // PLAYERSTATE_H
