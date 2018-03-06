#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CustomButton.h"

class MainWindow: public QMainWindow
{
Q_OBJECT

public:

    // member functions

    MainWindow(QWidget *parent = 0);
    void display();

private slots:

    // slots to handle key press events

    void handleSinglePlayer();
    void handleMultiPlayer();
    void handleExitGame();
    void changeColor();

private:

    // private member variables

    CustomButton* m_singlePlayer;
    QPushButton* m_multiPlayer;
    QPushButton* m_exitGame;
};

#endif // MAINWINDOW_H
