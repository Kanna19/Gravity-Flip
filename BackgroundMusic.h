#ifndef BACKGROUNDMUSIC_H
#define BACKGROUNDMUSIC_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QThread>
#include <QObject>

class BackgroundMusic: public QThread
{
Q_OBJECT
public:
    BackgroundMusic();
    void run();
    void exec();

public slots:
    void playMusic();
    void playSound();

private:
    QMediaPlaylist* playlist;
    QMediaPlayer* musicPlayer;
};

#endif // BACKGROUNDMUSIC_H
