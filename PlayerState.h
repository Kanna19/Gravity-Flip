#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

class Player;

#include "Player.h"

class PlayerState
{

public:

    PlayerState();
    PlayerState(const PlayerState& state);
    PlayerState(Player* player, bool topCollision, bool bottomCollision, bool rightCollision);

    qreal xPos;
    qreal yPos;

    int pixmapIndex;

    bool isInAir;
    bool isFlipped;

    bool isNotCollidingWithTop;
    bool isNotCollidingWithBottom;
    bool isNotCollidingWithRight;
};

#endif // PLAYERSTATE_H
