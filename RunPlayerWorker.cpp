#include "RunPlayerWorker.h"
#include <QDebug>

RunPlayerWorker::RunPlayerWorker()
{

}

void RunPlayerWorker::updatePlayerState
(Player *player, bool isNotCollidingWithTop,
 bool isNotCollidingWithBottom, bool isNotCollidingWithRight, int xShift, int yShift)

{
    // Create new PlayerState variable
    PlayerState state(player);

    // Increase pixmap index
    state.pixmapIndex++;

    // Player running logic
    if(!state.isFlipped)
    {
        // If in air
        if(isNotCollidingWithBottom)
        {
            // Go back if collides with item
            if(!isNotCollidingWithRight)
            {
                state.xPos -= xShift;
                state.yPos += yShift;
            }

            // Else just go down
            else
            {
                state.yPos += yShift;
            }

            state.isInAir = true;
        }

        else
        {
            // Make sound on landing
            if(state.isInAir)
            {
                player->stepSoundPlayer->play();
            }

            // Allow picture to be changed while running
            state.isInAir = false;
            state.isUpdateToPixMapNeeded = true;

            // Go back if collides with items
            if(!isNotCollidingWithRight)
            {
                state.xPos -= xShift;
            }
        }
    }

    else
    {
        // If in air
        if(isNotCollidingWithTop)
        {
            // Go back if collides with item
            if(!isNotCollidingWithRight)
            {
                state.xPos -= xShift;
                state.yPos -= yShift;
            }

            // Else just go up
            else
            {
                state.yPos -= yShift;
            }

            state.isInAir = true;
        }

        else
        {
            // Make sound on landing
            if(state.isInAir)
            {
                player->stepSoundPlayer->play();
            }

            // Allow picture to be changed while running
            state.isInAir = false;
            state.isUpdateToPixMapNeeded = true;

            // Go back if collides with items
            if(!isNotCollidingWithRight)
            {
                state.xPos -= xShift;
            }
        }
    }

    // Send signal to player after state update
    emit doneUpdating(state);
}

void RunPlayerWorker::updateFlipPlayerState(Player *player)
{
    // If in air don't flip
    if(player->isInAir)
    {
        return;
    }

    // Else change isFlipped
    PlayerState state(player);
    state.isFlipped = 1 -state.isFlipped;

    // Send signal to player after state update
    emit doneFlipping(state);
}
