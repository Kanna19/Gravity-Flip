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

    // public member variables


private slots:

    // slots to handle key press event

    void handleExitGame();

private:

    // private member variables

    QPushButton* m_exitGame;
};

#endif // GAMEOVERWINDOW_H
