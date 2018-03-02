#include "Trail.h"
#include "Game.h"

extern Game* game;
Trail::Trail(qreal xPos, qreal yPos)
{
    setRect(0,0,40,40);
    setPos(xPos,yPos);
    setVisible(false);
}

void Trail::updatePos()
{

    if(collidesWithItem(game->player[1]->rightArea))
    {
        game->player[1]->flipPlayer();
        delete this;
    }
    else
    {
        setPos(x()-2,y());
    }
}
