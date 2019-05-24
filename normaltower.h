#ifndef NORMALTOWER_H
#define NORMALTOWER_H

#include "tower.h"

class NormalTower: public Tower
{
public:
    NormalTower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/normaltower.png"));
    ~NormalTower();

};

#endif // NORMALTOWER_H
