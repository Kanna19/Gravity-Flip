#ifndef STEPSOUND_H
#define STEPSOUND_H

#include <QThread>
#include <QMediaPlayer>
class StepSound: public QThread
{
public:
    StepSound();
    void run();
    void exec();

    QMediaPlayer* musicPlayer;

public slots:
    void playSound();
};

#endif // STEPSOUND_H
