#include "PlayerState.h"

PlayerState::PlayerState(const Player *player, bool topCollision,
                         bool bottomCollision, bool rightCollision)
{
    xPos = player->x();
    yPos = player->y();

    pixmapIndex = player->pixmapIndex;

    isInAir = player->isInAir;
    isFlipped = player->isFlipped;

    isNotCollidingWithTop = topCollision;
    isNotCollidingWithBottom = bottomCollision;
    isNotCollidingWithRight = rightCollision;
}
