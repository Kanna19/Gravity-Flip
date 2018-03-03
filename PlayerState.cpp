#include "PlayerState.h"

PlayerState::PlayerState()
{
}

PlayerState::PlayerState(const PlayerState &state)
{
    xPos = state.xPos;
    yPos = state.yPos;

    pixmapIndex = state.pixmapIndex;

    isInAir = state.isInAir;
    isFlipped = state.isFlipped;

    isNotCollidingWithTop = state.isNotCollidingWithTop;
    isNotCollidingWithRight = state.isNotCollidingWithRight;
    isNotCollidingWithBottom = state.isNotCollidingWithBottom;
}

PlayerState::PlayerState(Player* player, bool topCollision,
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
