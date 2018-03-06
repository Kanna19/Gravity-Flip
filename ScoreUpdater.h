#ifndef SCOREUPDATER_H
#define SCOREUPDATER_H

#include <QTimer>
#include <QGraphicsTextItem>

class ScoreUpdater: public QGraphicsTextItem
{
Q_OBJECT

public:

    // member functions

    ScoreUpdater(QGraphicsItem* parent = 0);
    int getScore();

private slots:

    void updateScore();

private:

    // private member variables

    int m_score;
    int m_stepSize;
};

#endif // SCOREUPDATER_H
