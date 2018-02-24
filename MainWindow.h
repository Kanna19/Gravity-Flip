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

    void handleSinglePlayer();
    void handleMultiPlayer();
    void handleExitGame();

private:

    // private member variables

    QPushButton* m_singlePlayer;
    QPushButton* m_multiPlayer;
    QPushButton* m_exitGame;
};

#endif // MAINWINDOW_H
