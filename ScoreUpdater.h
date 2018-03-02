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
    void connectStepIncrementTimer();
    void disconnectStepIncrementTimer();

private slots:

    void updateScore();
    void incrementStepSize();

private:

    // private member variables

    int m_score;
    int m_stepSize;
    QTimer* m_timerForStepSize;

};

#endif // SCOREUPDATER_H
