#include "BackgroundUpdater.h"
#include "Game.h"

extern Game* game;

BackgroundUpdater::BackgroundUpdater()
{
    // Set the Background Image
    brush = QBrush(QImage(":/res/objects/acid2.png"));
}

void BackgroundUpdater::update()
{
    // Shift the background to the left by 2 pixels
    brush.setTransform(brush.transform().translate(-2, 0));
    game->setBackgroundBrush(brush);
}
