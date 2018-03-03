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
}

PlayerState::PlayerState(Player* player)
{
    xPos = player->x();
    yPos = player->y();

    pixmapIndex = player->pixmapIndex;

    isInAir = player->isInAir;
    isFlipped = player->isFlipped;
}
