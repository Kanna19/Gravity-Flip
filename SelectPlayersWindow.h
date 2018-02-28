#ifndef SELECTPLAYERSWINDOW_H
#define SELECTPLAYERSWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QSignalMapper>
#include <vector>

class SelectPlayersWindow: public QMainWindow
{

Q_OBJECT

public:

    SelectPlayersWindow(int cnt, QWidget* parent = 0);
    void display();

private slots:

    void setPlayer1ID(int id);
    void setPlayer2ID(int id);

private:

    void updateDisplay();
    void createNewGame();

    int m_cnt;
    QLabel* m_label;

    QPushButton* m_images[3];
    std::vector <int> m_playerID;

    QSignalMapper* m_mapper;
};

#endif // SELECTPLAYERSWINDOW_H
