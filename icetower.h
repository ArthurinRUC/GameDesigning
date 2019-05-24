#ifndef ICETOWER_H
#define ICETOWER_H

#include "tower.h"

class IceTower : public Tower
{
public:
    IceTower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/icetower.png"));
    ~IceTower();
};

#endif // ICETOWER_H
