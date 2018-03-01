#include "BackgroundMusic.h"
#include <QDebug>
#include <QThread>
#include <QTimer>

BackgroundMusic::BackgroundMusic()
{
    playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl("qrc:/res/sounds/background.mp3"));
    //playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    musicPlayer = new QMediaPlayer;
    musicPlayer->setMedia(QUrl("qrc:/res/sounds/30sec.mp3"));
}

void BackgroundMusic::run()
{
    //playMusic();

    exec();
}

void BackgroundMusic::exec()
{
    qWarning() << "BackMusic: " << thread()->currentThreadId();
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

void BackgroundMusic::playMusic()
{
    qWarning() << this->thread()->currentThreadId();
    //moveToThread(this);
    musicPlayer->play();
    QTimer* timer;
    //QObject::connect(timer, SIGNAL(timeout()),musicPlayer,SLOT(play()));
    //timer->start(300);
    if(musicPlayer->state() == QMediaPlayer::StoppedState)
    {
        musicPlayer->play();
    }
}

void BackgroundMusic::playSound()
{
    qWarning() << "yo " << this->thread()->currentThreadId();
    QMediaPlayer* soundPlayer = new QMediaPlayer();
    soundPlayer->setMedia(QUrl("qrc:/res/sounds/bullet.wav"));
    soundPlayer->play();
}
