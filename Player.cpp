#include "Player.h"

Player::Player()
{
    setPixmap(QPixmap(":res/player/idle1.png").scaled(120,120));
    pixmapIndex = 0;

    for(int i = 1; i <= 8; i++)
    {
        run[i-1] = QPixmap(":/res/player/run" + QString::number(i) + ".png").scaled(120,120);
    }

}

void Player::runPlayer()
{
    if( x() > 680) return ;
    pixmapIndex++;
    setPixmap(run[pixmapIndex%8]);

    setPos(x()+10,y());
}
