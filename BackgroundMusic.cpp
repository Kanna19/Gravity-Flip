#include "BackgroundMusic.h"
#include <QDebug>
#include <QThread>

BackgroundMusic::BackgroundMusic()
{
    playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl("qrc:/res/sounds/background.mp3"));
    //playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    musicPlayer = new QMediaPlayer;
    musicPlayer->setMedia(QUrl("qrc:/res/sounds/background.mp3"));
}

void BackgroundMusic::run()
{
    playMusic();
}

void BackgroundMusic::playMusic()
{
    qWarning() << this->thread()->currentThreadId();
    //moveToThread(this);
    musicPlayer->play();
}

void BackgroundMusic::playSound()
{
    QMediaPlayer* soundPlayer = new QMediaPlayer();
    soundPlayer->setMedia(QUrl("qrc:/res/sounds/bullet.wav"));
    soundPlayer->play();
}
