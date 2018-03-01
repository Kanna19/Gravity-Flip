#ifndef BACKGROUNDMUSIC_H
#define BACKGROUNDMUSIC_H

#include <QMediaPlayer>
#include <QThread>
#include <QObject>

class BackgroundMusic: public QThread
{
Q_OBJECT

public:

    BackgroundMusic();
    void run();
    void exec();

private:

    QMediaPlaylist* playlist;
    QMediaPlayer* musicPlayer;
};

#endif // BACKGROUNDMUSIC_H
