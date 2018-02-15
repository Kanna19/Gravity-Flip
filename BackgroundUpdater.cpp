#include "BackgroundUpdater.h"
#include "Game.h"
extern Game* game;

BackgroundUpdater::BackgroundUpdater()
{
    brush = QBrush(QImage(":/res/objects/acid2.png"));
}

void BackgroundUpdater::update()
{
    brush.setTransform(brush.transform().translate(-2,0));
    game->setBackgroundBrush(brush);
}
