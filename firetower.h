#ifndef FIRETOWER_H
#define FIRETOWER_H

#include "tower.h"

class FireTower : public Tower
{
public:
    FireTower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/firetower.png"));
    ~FireTower();
};

#endif // FIRETOWER_H
