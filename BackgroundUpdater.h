#ifndef BACKGROUNDUPDATER_H
#define BACKGROUNDUPDATER_H

#include <QObject>
#include <QBrush>

class BackgroundUpdater: public QObject
{
Q_OBJECT

public:

    // member functions

    BackgroundUpdater();

    // member variables

    QBrush brush;

public slots:

    void update();
};

#endif // BACKGROUNDUPDATER_H
