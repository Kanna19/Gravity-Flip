#include "BackgroundMusic.h"
#include <QDebug>
#include <QThread>

BackgroundMusic::BackgroundMusic()
{
    musicPlayer = new QMediaPlayer;
    musicPlayer->setMedia(QUrl("qrc:/res/sounds/30sec.mp3"));
}

void BackgroundMusic::run()
{
    // run exec
    exec();
}

void BackgroundMusic::exec()
{
    qWarning() << "BackMusic: " << thread()->currentThreadId();
    //run event loop till interrupted
    while(!thread()->isInterruptionRequested())
    {
        if(musicPlayer->state() == QMediaPlayer::StoppedState)
        {
            //qWarning() << this->thread()->currentThreadId();
            musicPlayer->play();
        }
    }

    qWarning() << "Stopping thread";
    musicPlayer->stop();
    return;
}
