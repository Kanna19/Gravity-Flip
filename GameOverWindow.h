#ifndef GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class GameOverWindow: public QMainWindow
{
Q_OBJECT

public:

    // member functions

    GameOverWindow(QWidget *parent = 0);
    void display(int loser);

    static int const EXIT_CODE_REBOOT;

private:

    // private member variables

    QPushButton* m_exitGame;
    QPushButton* m_restartGame;

private slots:

    // slots to handle key press event

    void handleExitGame();
    void handleRestartGame();
};

#endif // GAMEOVERWINDOW_H
