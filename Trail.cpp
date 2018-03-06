#include "Trail.h"
#include "Game.h"

extern Game* game;

Trail::Trail(qreal xPos, qreal yPos)
{
    // Create a trail for Computer to pickup
    setRect(0, 0, 40, 40);
    setPos(xPos, yPos);

    // Make trail invisible
    setVisible(false);
}

void Trail::updatePos()
{
    // If trial collides with computers right area then flip the computer
    if(collidesWithItem(game->player[1]->rightArea))
    {
        game->player[1]->flipPlayer();
        delete this;
    }

    else
    {
        setPos(x() -game->xShift, y());
    }
}
