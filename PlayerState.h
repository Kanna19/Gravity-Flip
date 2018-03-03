#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

class Player;

#include "Player.h"

class PlayerState
{

public:

    PlayerState();
    PlayerState(const PlayerState& state);
    PlayerState(Player* player);

    qreal xPos;
    qreal yPos;

    int pixmapIndex;

    bool isInAir;
    bool isFlipped;

    bool isUpdateToPixMapNeeded;
};

#endif // PLAYERSTATE_H
