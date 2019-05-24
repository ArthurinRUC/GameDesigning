#ifndef LASERTOWER_H
#define LASERTOWER_H

#include "tower.h"
class LaserTower : public Tower
{
public:
    LaserTower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/lasertower.png"));
    ~LaserTower();
};

#endif // LASERTOWER_H
