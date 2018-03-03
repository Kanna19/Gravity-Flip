#include "StepSound.h"
#include <QEventLoop>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>

extern QWaitCondition soundWait;
extern QMutex mutex;

StepSound::StepSound()
{
    musicPlayer = new QMediaPlayer;
    musicPlayer->setMedia(QUrl("qrc:/res/sounds/bullet.wav"));
}

void StepSound::run()
{
    exec();
}

void StepSound::exec()
{
    while(!thread()->isInterruptionRequested())
    {
        qWarning() << "Starting loop";
        mutex.lock();
        soundWait.wait(&mutex);
        playSound();
        mutex.unlock();
        qWarning() << "Ending Loop";
    }

    qWarning() << "Exiting sound step" ;

}

void StepSound::playSound()
{
    qWarning() << "Sound Step: " << this->thread()->currentThreadId();
    musicPlayer->play();
}
