#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class MainWindow: public QMainWindow
{
Q_OBJECT

public:

    // member functions
    MainWindow(QWidget *parent = 0);
    void display();

private slots:

    void handleStartGame();
    void handleExitGame();

private:

    // private member variables

    QPushButton* m_startGame;
    QPushButton* m_exitGame;
};

#endif // MAINWINDOW_H
