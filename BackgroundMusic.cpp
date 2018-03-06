#include "BackgroundMusic.h"

BackgroundMusic::BackgroundMusic(int idx = 1)
{
    // Construct new QMediaPlayer
    musicPlayer = new QMediaPlayer;

    // Select soundtrack based on input (idx)
    if(idx == 1)
    {
        musicPlayer->setMedia(QUrl("qrc:/res/sounds/30sec.mp3"));
    }

    else if(idx == 0)
    {
        musicPlayer->setMedia(QUrl("qrc:/res/sounds/sow.mp3"));
    }
}

void BackgroundMusic::run()
{
    // Run exec
    exec();
}

void BackgroundMusic::exec()
{
    // Run event loop till it is interrupted
    while(!thread()->isInterruptionRequested())
    {
        if(musicPlayer->state() == QMediaPlayer::StoppedState)
        {
            musicPlayer->play();
        }
    }

    // Stop music and exit thread
    musicPlayer->stop();
    return;
}
