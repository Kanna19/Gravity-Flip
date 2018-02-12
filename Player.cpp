#include "Player.h"

Player::Player()
{
    setPixmap(QPixmap(":res/player/idle1.png").scaled(100,100,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    pixmapIndex = 0;

    isFlipped = false;

    for(int i = 1; i <= 8; i++)
    {
        run[i-1] = QPixmap(":/res/player/run" + QString::number(i) + ".png").scaled(100,100,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }

}

void Player::runPlayer()
{
    if( x() > 900) return ;
    pixmapIndex++;
    if(!isFlipped)
    {
        if(y() <= 250) setPos(x(),y()+20);
        else setPixmap(run[pixmapIndex%8]);;
    }
    else
    {
         if(y() > 50) setPos(x(),y()-20);
         else setPixmap(run[pixmapIndex%8].transformed(QTransform().rotate(180,Qt::XAxis)));
    }

     setPos(x()+10,y());


}

void Player::flipPlayer()
{
    setPixmap(pixmap().transformed(QTransform().rotate(180,Qt::XAxis)));

    //change isFlipped
    isFlipped = (isFlipped+1)%2;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        flipPlayer();
    }
}
