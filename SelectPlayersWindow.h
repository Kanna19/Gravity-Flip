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

    const int m_imageCount;
    std::vector <int> m_playerID;
    std::vector <QPushButton*> m_images;

    QSignalMapper* m_mapper;

};

#endif // SELECTPLAYERSWINDOW_H
