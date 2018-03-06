#include "BackgroundUpdater.h"
#include "Game.h"

extern Game* game;

BackgroundUpdater::BackgroundUpdater()
{
    // Set the Background Image
    brush = QBrush(QImage(":/res/objects/bgrocks.png").scaled(1000,500));

    // Background image not yet changed
    isChanged = false;
}

void BackgroundUpdater::update()
{
    // Change background when game speed increases
    if(!isChanged && game->xShift == 3)
    {
        brush = QBrush(QImage(":/res/objects/bgrocks2.png").scaled(1000,500));
        isChanged = true;
    }

    // Shift the background to the left by xShift pixels
    brush.setTransform(brush.transform().translate(-game->xShift, 0));
    game->setBackgroundBrush(brush);
}
