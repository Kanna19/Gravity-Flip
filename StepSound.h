#ifndef STEPSOUND_H
#define STEPSOUND_H

#include <QThread>
#include <QMediaPlayer>

class StepSound: public QThread
{
public:

    // member functions

    StepSound();
    void run();
    void exec();

    // member variables

    QMediaPlayer* musicPlayer;

public slots:

    void playSound();
};

#endif // STEPSOUND_H
