#ifndef BACKGROUNDMUSIC_H
#define BACKGROUNDMUSIC_H

#include <QMediaPlayer>
#include <QThread>
#include <QObject>

class BackgroundMusic: public QThread
{
Q_OBJECT

public:

    // member functions
    /**
     * \brief Constructor
     * \param idx used to set the song
     */
    BackgroundMusic(int idx);

    /**
     * \brief Executes the exec() function. run is called on starting the thread
     */
    void run();

    /**
     * \brief Runs in a loop and restarts song if finished
     */
    void exec();

private:

    // private member variables

    /**
     * \brief QMediaPlayer object that plays music
     */
    QMediaPlayer* musicPlayer;
};

#endif // BACKGROUNDMUSIC_H
