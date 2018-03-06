#include "BackgroundUpdater.h"
#include "Game.h"

extern Game* game;

BackgroundUpdater::BackgroundUpdater()
{
    // Set the Background Image
    brush = QBrush(QImage(":/res/objects/bgrocks.png").scaled(1000,500));
    isChanged = false;
}

void BackgroundUpdater::update()
{
    // Shift the background to the left by xShift pixels
    if(!isChanged && game->xShift == 3)
    {
        brush = QBrush(QImage(":/res/objects/bgrocks2.png").scaled(1000,500));
        isChanged = true;
    }
    brush.setTransform(brush.transform().translate(-game->xShift, 0));
    game->setBackgroundBrush(brush);
}
