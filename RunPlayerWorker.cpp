#include "RunPlayerWorker.h"
#include <QDebug>

RunPlayerWorker::RunPlayerWorker()
{

}

void RunPlayerWorker::updatePlayerState
(Player *player, bool isNotCollidingWithTop,
 bool isNotCollidingWithBottom, bool isNotCollidingWithRight, int xShift, int yShift)

{
    /*
    if(thread()->isInterruptionRequested())
    {
        qWarning() << "dead";
        return;
    }
    */

    // qWarning() << player->x() << ' ' << player->y();
    PlayerState state(player);
    // qWarning() << state.xPos << ' ' << state.yPos;

    state.pixmapIndex++;

    if(!state.isFlipped)
    {
        if(isNotCollidingWithBottom)
        {
            if(!isNotCollidingWithRight)
            {
                state.xPos -= xShift;
                state.yPos += yShift;
            }

            else
            {
                state.yPos += yShift;
            }

            state.isInAir = true;
        }

        else
        {
            if(state.isInAir)
            {
                player->stepSoundPlayer->play();
            }

            state.isInAir = false;
            state.isUpdateToPixMapNeeded = true;

            if(isNotCollidingWithRight)
            {
                ;
            }

            else
            {
                state.xPos -= xShift;
            }
        }
    }

    else
    {
        if(isNotCollidingWithTop)
        {
            if(!isNotCollidingWithRight)
            {
                state.xPos -= xShift;
                state.yPos -= yShift;
            }

            else
            {
                state.yPos -= yShift;
            }

            state.isInAir = true;
        }

        else
        {
            if(state.isInAir)
            {
                player->stepSoundPlayer->play();
            }

            state.isInAir = false;
            state.isUpdateToPixMapNeeded = true;

            if(isNotCollidingWithRight)
            {
                ;
            }

            else
            {
                state.xPos -= xShift;
            }
        }
    }

    emit doneUpdating(state);
}

void RunPlayerWorker::updateFlipPlayerState(Player *player)
{
    //qWarning() << thread()->currentThreadId();

    if(player->isInAir)
    {
        return;
    }

    PlayerState state(player);
    state.isFlipped = 1 -state.isFlipped;

    emit doneFlipping(state);
}
